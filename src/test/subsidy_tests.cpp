// Copyright (c) 2014-2020 The Dash Core developers
// Copyright (c) 2020-2023 The Raptoreum developers
// Copyright (c) 2025 The HashmonkeyCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <validation.h>

#include <test/test_hashmonkeycoin.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(subsidy_tests, TestingSetup
)

BOOST_AUTO_TEST_CASE(block_subsidy_test)
        {
                const auto chainParams = CreateChainParams(CBaseChainParams::MAIN);

                uint32_t nPrevBits;
                int32_t nPrevHeight;
                CAmount nSubsidy;

                // details for block 1000 (subsidy returned will be for block 1001)
                nPrevBits = 0x1c4a47c4;
                nPrevHeight = 1000;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 50000000000ULL);

                // details for block 210240 (subsidy returned will be for block 210241) - first halving
                nPrevBits = 0x1c4a47c4;
                nPrevHeight = 210240;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 25000000000ULL);

                // details for block 420480 (subsidy returned will be for block 420481) - second halving
                nPrevBits = 0x1c29ec00;
                nPrevHeight = 420480;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 12500000000ULL);

                // details for block 630720 (subsidy returned will be for block 630721) - third halving
                nPrevBits = 0x1c29ec00;
                nPrevHeight = 630720;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 6250000000ULL);

                // details for block 840960 (subsidy returned will be for block 840961) - fourth halving
                nPrevBits = 0x1c08ba34;
                nPrevHeight = 840960;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 3125000000ULL);

                // details for block 1051200 (subsidy returned will be for block 1051201) - fifth halving
                nPrevBits = 0x1b10cf42;
                nPrevHeight = 1051200;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 1562500000ULL);

                // details for block 1261440 (subsidy returned will be for block 1261441) - sixth halving
                nPrevBits = 0x1b11548e;
                nPrevHeight = 1261440;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 781250000ULL);

                // details for block 13455360 (subsidy returned will be for block 13455361) - after 64 halvings (no more rewards)
                nPrevBits = 0x1b10d50b;
                nPrevHeight = 13455360;
                nSubsidy = GetBlockSubsidy(nPrevBits, nPrevHeight, chainParams->GetConsensus(), false);
                BOOST_CHECK_EQUAL(nSubsidy, 0ULL);
        }

BOOST_AUTO_TEST_SUITE_END()
