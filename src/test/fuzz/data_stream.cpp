// Copyright (c) 2020 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <addrman.h>
#include <net.h>
#include <test/fuzz/FuzzedDataProvider.h>
#include <test/fuzz/fuzz.h>
#include <test/fuzz/util.h>

#include <cstdint>
#include <vector>

void initialize_data_stream_addr_man()
{
    InitializeFuzzingContext();
}

FUZZ_TARGET_INIT(data_stream_addr_man, initialize_data_stream_addr_man)
{
    FuzzedDataProvider fuzzed_data_provider{buffer.data(), buffer.size()};
    CDataStream data_stream = ConsumeDataStream(fuzzed_data_provider);
    CAddrMan addr_man;
    CAddrDB::Read(addr_man, data_stream);
}
