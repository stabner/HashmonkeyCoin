// Copyright (c) 2014-2020 The Dash Core developers
// Copyright (c) 2020-2023 The Raptoreum developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <validation.h>

#include <test/test_raptoreum.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(subsidy_tests, TestingSetup
)

BOOST_AUTO_TEST_CASE(block_subsidy_test)
        {
                const auto chainParams = CreateChainParams(CBaseChainParams::MAIN);

                uint32_t nPrevBits = 0x1c4a47c4; // Dummy bits for testing
                int32_t nPrevHeight;
                CAmount nSubsidy;

                // Test initial reward (500 HMNY)
                nPrevHeight = 0;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 500 * COIN);

                // Test reward before first halving (block 209999)
                nPrevHeight = 209999;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 500 * COIN);

                // Test first halving (block 210000) - reward should be 250 HMNY
                nPrevHeight = 210000;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 250 * COIN);

                // Test second halving (block 420000) - reward should be 125 HMNY
                nPrevHeight = 420000;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 125 * COIN);

                // Test third halving (block 630000) - reward should be 62.5 HMNY
                nPrevHeight = 630000;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 62 * COIN); // Integer division: 125/2 = 62

                // Test fourth halving (block 840000) - reward should be 31.25 HMNY
                nPrevHeight = 840000;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 31 * COIN); // Integer division: 62/2 = 31

                // Test after many halvings (block 2100000) - should be minimum 1 satoshi
                nPrevHeight = 2100000;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 1); // Minimum reward
        }

BOOST_AUTO_TEST_SUITE_END()
