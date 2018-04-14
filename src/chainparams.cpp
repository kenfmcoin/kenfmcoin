// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The KenFMcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "25.06.2017, Me, Myself and Media 35 - Kafkaeske Zeiten"; // KenFMcoin: 25.06.2017, Me, Myself and Media 35 - Kafkaeske Zeiten
    const CScript genesisOutputScript = CScript() << ParseHex("04e5b975429d7b9ac85b0a9322186dee39257aa21bda96b63cee0c855b1a74ff816f96642e6f69635cec9b52d52535c80814f4ebf08ad6b97ac45384315ff5726b") << OP_CHECKSIG; // KenFMcoin: 04e5b975429d7b9ac85b0a9322186dee39257aa21bda96b63cee0c855b1a74ff816f96642e6f69635cec9b52d52535c80814f4ebf08ad6b97ac45384315ff5726b
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000; // KenFMcoin: 210000 is a dummy variable here
        consensus.BIP34Height = 1;                  // KenFMcoin: 1
        consensus.BIP34Hash = uint256S("0x0b02e963517307e93c113bd83851a2018420c3d7a35b155a886020d7e7b41852"); // KenFMcoin: 0x0b02e963517307e93c113bd83851a2018420c3d7a35b155a886020d7e7b41852
        consensus.BIP65Height = 3; // KenFMcoin: 3
        consensus.BIP66Height = 2; // KenFMcoin: 2
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // KenFMcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // KenFMcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // KenFMcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // KenFMcoin: 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // KenFMcoin: nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1498713060; // KenFMcoin: Thursday, 29. June 2017 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1530249060; // KenFMcoin: Friday, 29. June 2018 05:11:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530249060; // KenFMcoin: Friday, 29. June 2018 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1561785060; // KenFMcoin: Saturday, 29. June 2019 05:11:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000000000fc16d8c5"); // KenFMcoin: 0x00000000000000000000000000000000000000000000000000000000fc16d8c5

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x91db06f8e894b589429a923a7a09b8724a9e86f332703237297f61b3ca0f4a87"); // KenFMcoin: 0x91db06f8e894b589429a923a7a09b8724a9e86f332703237297f61b3ca0f4a87 at height 4032

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd9; // KenFMcoin: 0xd9
        pchMessageStart[1] = 0xb4; // KenFMcoin: 0xb4
        pchMessageStart[2] = 0xbe; // KenFMcoin: 0xbe
        pchMessageStart[3] = 0xfc; // KenFMcoin: 0xfc
        nDefaultPort = 1966; // KenFMcoin: 1966
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1498602345, 10418, 0x1e0ffff0, 1, 50 * COIN); // KenFMcoin: 1498602345, 10418, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6")); // KenFMcoin: 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
        assert(genesis.hashMerkleRoot == uint256S("0xb325015a361786f020a99f495ead156a0092ac17c266d49d88a9be8c096188f3")); // KenFMcoin: 0xb325015a361786f020a99f495ead156a0092ac17c266d49d88a9be8c096188f3

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("dnsseed1.kenfmcoin.org", true); // KenFMcoin: dnsseed1.kenfmcoin.org
        vSeeds.emplace_back("dnsseed2.kenfmcoin.org", false);// KenFMcoin: dnsseed2.kenfmcoin.org

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,45); // KenFMcoin: 45 (K)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,92); // KenFMcoin: 92
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,173); // KenFMcoin: 173
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // KenFMcoin: 0x04, 0x88, 0xB2, 0x1E (xpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // KenFMcoin: 0x04, 0x88, 0xAD, 0xE4 (xpriv)

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6")}, // KenFMcoin: 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
                {     1, uint256S("0x0b02e963517307e93c113bd83851a2018420c3d7a35b155a886020d7e7b41852")}, // KenFMcoin: 0x0b02e963517307e93c113bd83851a2018420c3d7a35b155a886020d7e7b41852
                {   275, uint256S("0x43dda78d7cbef30529957c7a372da72d03f9ca697945960b7f8081f7f3601686")}, // KenFMcoin: 0x43dda78d7cbef30529957c7a372da72d03f9ca697945960b7f8081f7f3601686
                {  4032, uint256S("0x91db06f8e894b589429a923a7a09b8724a9e86f332703237297f61b3ca0f4a87")}, // KenFMcoin: 0x91db06f8e894b589429a923a7a09b8724a9e86f332703237297f61b3ca0f4a87
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 0x91db06f8e894b589429a923a7a09b8724a9e86f332703237297f61b3ca0f4a87 (height 4032). // KenFMcoin: 0x91db06f8e894b589429a923a7a09b8724a9e86f332703237297f61b3ca0f4a87
            1501655492, // * UNIX timestamp of last known number of transactions                                  // KenFMcoin: 1501655492
                  4117, // * total number of transactions between genesis and that timestamp                      // KenFMcoin: 4117
                        //   (the tx=... number in the SetBestChain debug.log lines)
                     1  // * estimated number of transactions per second after that timestamp                     // KenFMcoin: 1
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000; // KenFMcoin: 210000 is a dummy variable here
        consensus.BIP34Height = 0; // KenFMcoin: 0
        consensus.BIP34Hash = uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6"); // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
        consensus.BIP65Height = 999999; // KenFMcoin TODO: Update
        consensus.BIP66Height = 888888; // KenFMcoin TODO: Update
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // KenFMcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // KenFMcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // KenFMcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // KenFMcoin: 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // KenFMcoin: nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1498713060; // KenFMcoin: Thursday, 29. June 2017 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1530249060; // KenFMcoin: Friday, 29. June 2018 05:11:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530249060; // KenFMcoin: Friday, 29. June 2018 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1561785060; // KenFMcoin: Saturday, 29. June 2019 05:11:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // KenFMcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6"); // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6

        pchMessageStart[0] = 0x11; // KenFMcoin: 0x11
        pchMessageStart[1] = 0x0b; // KenFMcoin: 0x0b
        pchMessageStart[2] = 0x09; // KenFMcoin: 0x09
        pchMessageStart[3] = 0x03; // KenFMcoin: 0x03
        nDefaultPort = 11966; // KenFMcoin: 11966
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1498602345, 10418, 0x1e0ffff0, 1, 50 * COIN); // KenFMcoin TODO: Update, for now 1498602345, 10418, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6")); // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
        assert(genesis.hashMerkleRoot == uint256S("0xb325015a361786f020a99f495ead156a0092ac17c266d49d88a9be8c096188f3")); // KenFMcoin TODO: Update, for now 0xb325015a361786f020a99f495ead156a0092ac17c266d49d88a9be8c096188f3

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-dnsseed1.kenfmcoin.org", true); // KenFMcoin: testnet-dnsseed1.kenfmcoin.org
        vSeeds.emplace_back("testnet-dnsseed2.kenfmcoin.org", false);// KenFMcoin: testnet-dnsseed2.kenfmcoin.org

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // KenFMcoin: 111 (m or n)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // KenFMcoin: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // KenFMcoin: 239
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // KenFMcoin: 0x04, 0x35, 0x87, 0xCF (tpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // KenFMcoin: 0x04, 0x35, 0x83, 0x94 (tpriv)

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6")}, // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
            }
        };

        chainTxData = ChainTxData{
            // KenFMcoin TODO: Update, for now data as of block 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6 (height 0)
            1498602345,
            1,
            1
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150; // KenFMcoin: 150 is a dummy variable here
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // KenFMcoin TODO: Update, for now BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // KenFMcoin TODO: Update, for now BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // KenFMcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // KenFMcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // KenFMcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // KenFMcoin: 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // KenFMcoin: Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // KenFMcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6"); // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6 at height 0

        pchMessageStart[0] = 0xbf; // KenFMcoin: 0xbf
        pchMessageStart[1] = 0xfa; // KenFMcoin: 0xfa
        pchMessageStart[2] = 0xb5; // KenFMcoin: 0xb5
        pchMessageStart[3] = 0x03; // KenFMcoin: 0x03
        nDefaultPort = 21966; // KenFMcoin: 21966
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1498602345, 10418, 0x1e0ffff0, 1, 50 * COIN); // KenFMcoin TODO: Update, for now 1498602345, 10418, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6")); // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
        assert(genesis.hashMerkleRoot == uint256S("0xb325015a361786f020a99f495ead156a0092ac17c266d49d88a9be8c096188f3")); // KenFMcoin TODO: Update, for now 0xb325015a361786f020a99f495ead156a0092ac17c266d49d88a9be8c096188f3

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6")}, // KenFMcoin TODO: Update, for now 0xe0302c11cb6af39ed6262a22ffa1eb2ea902d1b6b8a7905b39a4e0c0480f45c6
            }
        };

        chainTxData = ChainTxData{
            1498602345, // KenFMcoin TODO: Update, for now 1498602345
            1, // KenFMcoin TODO: Update, for now 1
            1 // KenFMcoin TODO: Update, for now 1
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // KenFMcoin: 111 (m or n)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // KenFMcoin: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // KenFMcoin: 239
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // KenFMcoin: 0x04, 0x35, 0x87, 0xCF (tpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // KenFMcoin: 0x04, 0x35, 0x83, 0x94 (tpriv)
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
