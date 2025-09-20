// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2014-2021 The Dash Core developers
// Copyright (c) 2020-2023 The Raptoreum developers
// Copyright (c) 2024 The HashmonkeyCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CRYPTO_ECC_H
#define BITCOIN_CRYPTO_ECC_H

#include <string>

/** ECC (Elliptic Curve Cryptography) functions */
void ECC_Start();
void ECC_Stop();
bool ECC_InitSanityCheck();

#endif // BITCOIN_CRYPTO_ECC_H
