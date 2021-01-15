// Copyright (c) 2016-2020 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CALIFORNIUM_WALLET_WALLETTOOL_H
#define CALIFORNIUM_WALLET_WALLETTOOL_H

#include <wallet/wallet.h>

namespace WalletTool {

void WalletShowInfo(CWallet* wallet_instance);
bool ExecuteWalletToolFunc(const ArgsManager& args, const std::string& command, const std::string& file);

} // namespace WalletTool

#endif // CALIFORNIUM_WALLET_WALLETTOOL_H
