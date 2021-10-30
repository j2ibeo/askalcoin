// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Askalcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef ASKALCOIN_UTIL_FEES_H
#define ASKALCOIN_UTIL_FEES_H

#include <string>

enum class FeeEstimateMode;
enum class FeeReason;

bool FeeModeFromString(const std::string& mode_string, FeeEstimateMode& fee_estimate_mode);
std::string StringForFeeReason(FeeReason reason);
std::string FeeModes(const std::string& delimiter);
const std::string InvalidEstimateModeErrorMessage();

#endif // ASKALCOIN_UTIL_FEES_H