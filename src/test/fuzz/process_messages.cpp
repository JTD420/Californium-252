// Copyright (c) 2020 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <consensus/consensus.h>
#include <net.h>
#include <net_processing.h>
#include <protocol.h>
#include <test/fuzz/FuzzedDataProvider.h>
#include <test/fuzz/fuzz.h>
#include <test/fuzz/util.h>
#include <test/util/mining.h>
#include <test/util/net.h>
#include <test/util/setup_common.h>
#include <test/util/validation.h>
#include <util/memory.h>
#include <validation.h>
#include <validationinterface.h>

const TestingSetup* g_setup;

void initialize_process_messages()
{
    static TestingSetup setup{
        CBaseChainParams::REGTEST,
        {
            "-nodebuglogfile",
        },
    };
    g_setup = &setup;

    for (int i = 0; i < 2 * COINBASE_MATURITY; i++) {
        MineBlock(g_setup->m_node, CScript() << OP_TRUE);
    }
    SyncWithValidationInterfaceQueue();
}

FUZZ_TARGET_INIT(process_messages, initialize_process_messages)
{
    FuzzedDataProvider fuzzed_data_provider(buffer.data(), buffer.size());

    ConnmanTestMsg& connman = *(ConnmanTestMsg*)g_setup->m_node.connman.get();
    TestChainState& chainstate = *(TestChainState*)&g_setup->m_node.chainman->ActiveChainstate();
    chainstate.ResetIbd();
    std::vector<CNode*> peers;
    bool jump_out_of_ibd{false};

    const auto num_peers_to_add = fuzzed_data_provider.ConsumeIntegralInRange(1, 3);
    for (int i = 0; i < num_peers_to_add; ++i) {
        peers.push_back(ConsumeNodeAsUniquePtr(fuzzed_data_provider, i).release());
        CNode& p2p_node = *peers.back();
        FillNode(fuzzed_data_provider, p2p_node);

        p2p_node.fSuccessfullyConnected = true;
        p2p_node.fPauseSend = false;
        g_setup->m_node.peerman->InitializeNode(&p2p_node);

        connman.AddTestNode(p2p_node);
    }

    while (fuzzed_data_provider.ConsumeBool()) {
        if (!jump_out_of_ibd) jump_out_of_ibd = fuzzed_data_provider.ConsumeBool();
        if (jump_out_of_ibd && chainstate.IsInitialBlockDownload()) chainstate.JumpOutOfIbd();
        const std::string random_message_type{fuzzed_data_provider.ConsumeBytesAsString(CMessageHeader::COMMAND_SIZE).c_str()};

        CSerializedNetMsg net_msg;
        net_msg.m_type = random_message_type;
        net_msg.data = ConsumeRandomLengthByteVector(fuzzed_data_provider);

        CNode& random_node = *peers.at(fuzzed_data_provider.ConsumeIntegralInRange<int>(0, peers.size() - 1));

        (void)connman.ReceiveMsgFrom(random_node, net_msg);
        random_node.fPauseSend = false;

        try {
            connman.ProcessMessagesOnce(random_node);
        } catch (const std::ios_base::failure&) {
        }
        {
            LOCK(random_node.cs_sendProcessing);
            g_setup->m_node.peerman->SendMessages(&random_node);
        }
    }
    SyncWithValidationInterfaceQueue();
    LOCK2(::cs_main, g_cs_orphans); // See init.cpp for rationale for implicit locking order requirement
    g_setup->m_node.connman->StopNodes();
}
