// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Californium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef CALIFORNIUM_UTIL_FEES_H
#define CALIFORNIUM_UTIL_FEES_H

#include <string>

enum class FeeEstimateMode;
enum class FeeReason;

bool FeeModeFromString(const std::string& mode_string, FeeEstimateMode& fee_estimate_mode);
std::string StringForFeeReason(FeeReason reason);
std::string FeeModes(const std::string& delimiter);
const std::string InvalidEstimateModeErrorMessage();

#endif // CALIFORNIUM_UTIL_FEES_H
