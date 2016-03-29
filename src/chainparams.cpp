// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Bagcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//#define CREATE_GENESIS

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
		
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x00000e8ea678fa1b38f72ad0e48fc77ef63a59f7dd13b18bbb620d6953ef6632"))
        (  2, uint256("0x00000f20a61e6cf4ff6d2d87514e3fc9e4434c386a2cbc3aeb0b51fc22cdde9b"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        0, // * UNIX timestamp of last checkpoint block
        0,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        0        // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x00000e5abc726afabc6ea9c685215c9203f0ff4d9b67272fd7cb74cff57cb835"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        0,
        0,
        0
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x7f1ed8d44534cd9d73af887575a76c774071adb87aaa7722d4cf17081616f6e5"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x08;
        pchMessageStart[1] = 0x66;
        pchMessageStart[2] = 0x66;
        pchMessageStart[3] = 0x67;
        vAlertPubKey = ParseHex("0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e");
        nDefaultPort = 8887;
        //nRPCPort = 6832;
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // Bagcoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 100000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bagcoin: 1 minutes
        nTargetSpacing = 1 * 60; // Bagcoin: 1 minutes

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=00000e8ea678fa1b38f72ad0e48fc77ef63a59f7dd13b18bbb620d6953ef6632, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af, nTime=1455170132, nBits=1e0ffff0, nNonce=103076854, vtx=1)
			  CTransaction(hash=42677e4bfa, ver=1, vin.size=1, vout.size=1, nLockTime=0)
				CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01042131204d61722032303136203842616f62692041544d7320636f6d6520746f20434e)
				CTxOut(nValue=50.00000000, scriptPubKey=0467180d30cce4738f65395f5d9e67)

			  vMerkleTree:  42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af

			TEST CBlock(hash=00000e5abc726afabc6ea9c685215c9203f0ff4d9b67272fd7cb74cff57cb835, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af, nTime=1455170132, nBits=1e0ffff0, nNonce=202859758, vtx=1)
			  CTransaction(hash=42677e4bfa, ver=1, vin.size=1, vout.size=1, nLockTime=0)
				CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01042131204d61722032303136203842616f62692041544d7320636f6d6520746f20434e)
				CTxOut(nValue=50.00000000, scriptPubKey=0467180d30cce4738f65395f5d9e67)

			  vMerkleTree:  42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af

			REGTESTNET: CBlock(hash=7f1ed8d44534cd9d73af887575a76c774071adb87aaa7722d4cf17081616f6e5, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af, nTime=1417713337, nBits=207fffff, nNonce=1096447, vtx=1)
			  CTransaction(hash=42677e4bfa, ver=1, vin.size=1, vout.size=1, nLockTime=0)
				CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01042131204d61722032303136203842616f62692041544d7320636f6d6520746f20434e)
				CTxOut(nValue=50.00000000, scriptPubKey=0467180d30cce4738f65395f5d9e67)

			  vMerkleTree:  42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af
         */
        const char* pszTimestamp = "1 Mar 2016 8Baobi ATMs come to CN";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        //txNew.vout[0].nValue = 450000000 * COIN;
		txNew.vout[0].nValue = 50 * COIN;
		
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e") << OP_CHECKSIG;
		
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        //genesis.nTime    = 1456804800;  //2016/3/1 12:0:0
		genesis.nTime    = 1455170132;  //2016/2/11 13:55:32
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 103076854;

#ifdef CREATE_GENESIS
        // create genesis block begin -----------------------------
        static bool bCalcGenesis = true;
        if (bCalcGenesis) {
            bCalcGenesis = false;

            bool fNegative;
            bool fOverflow;
            uint256 bnTarget;
            bnTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow);

            uint256 bestHash = genesis.GetHash();
            while (bestHash > bnTarget) {
                if (genesis.nNonce++ == 0)
                    genesis.nTime++;

                bestHash = genesis.GetHash();
            }
            printf("%s\n", genesis.ToString().c_str());
        }
        // create genesis block end  
#else
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000e8ea678fa1b38f72ad0e48fc77ef63a59f7dd13b18bbb620d6953ef6632"));
        assert(genesis.hashMerkleRoot == uint256("0x42677e4bfa0d587c0462314c67a29191924fae10a3814a40dcd23614e0b013af"));
#endif

        vSeeds.push_back(CDNSSeedData("seed.bagcoin.org", "seed.bagcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed1.bagcoin.org", "seed1.bagcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed2.bagcoin.org", "seed2.bagcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3.bagcoin.org", "seed3.bagcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed4.bagcoin.org", "seed4.bagcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed5.bagcoin.org", "seed5.bagcoin.org"));
		
		base58Prefixes[PUBKEY_ADDRESS] = list_of(18);
		base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
		base58Prefixes[SECRET_KEY] =     list_of(128);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005);

        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e";
        strMasternodePaymentsPubKey = "0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e";
        strDarksendPoolDummyAddress = "8XxRWJEgPyFL8GTc2uDRbV27528KAZHVy1";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x7c;
        pchMessageStart[2] = 0x7f;
        pchMessageStart[3] = 0x73;
        vAlertPubKey = ParseHex("0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e");
        nDefaultPort = 18887;
        //nRPCPort = 16832;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Bagcoin: 1 minutes
        nTargetSpacing = 1 * 60; // Bagcoin: 1 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        //genesis.nTime    = 1456804800;  //2016/3/1 12:0:0
		genesis.nTime    = 1455170132;  //2016/2/11 13:55:32
        genesis.nNonce = 202859758;

#ifdef CREATE_GENESIS
        // create genesis block begin -----------------------------
        static bool bCalcGenesis = true;
        if (bCalcGenesis) {
            bCalcGenesis = false;

            bool fNegative;
            bool fOverflow;
            uint256 bnTarget;
            bnTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow);

            uint256 bestHash = genesis.GetHash();
            while (bestHash > bnTarget) {
                if (genesis.nNonce++ == 0)
                    genesis.nTime++;

                bestHash = genesis.GetHash();
            }
            printf("TEST %s\n", genesis.ToString().c_str());
        }
        // create genesis block end
#else
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000e5abc726afabc6ea9c685215c9203f0ff4d9b67272fd7cb74cff57cb835"));
#endif

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(85);                    // Testnet bagcoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(19);                    // Testnet bagcoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = list_of(239);                    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0); // Testnet bagcoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37); // Testnet bagcoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet bagcoin BIP44 coin type is '5' (All coin's testnet default)

       // convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e";
        strMasternodePaymentsPubKey = "0467180d30cce4738f65395f5d9e679e08fb14d717ec47d9465db8f9baa743dccddfb07463b49764b3596a5b428bb0b1d2d506d2ac26d968d04b3c6ee48aad080e";
        strDarksendPoolDummyAddress = "uYhuceXHnst99Wvh6hxjgcvSMcNYb2nYdZ";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x51;
        pchMessageStart[1] = 0x4c;
        pchMessageStart[2] = 0x4f;
        pchMessageStart[3] = 0x44;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 1 * 60; // Bagcoin: 1 minutes
        nTargetSpacing = 1 * 60; // Bagcoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1417713337;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1096447;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 28887;
#ifdef CREATE_GENESIS
        printf("REGTESTNET: %s\n", genesis.ToString().c_str());
#else
        assert(hashGenesisBlock == uint256("0x7f1ed8d44534cd9d73af887575a76c774071adb87aaa7722d4cf17081616f6e5"));
#endif

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 38887;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
