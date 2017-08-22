// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
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

class CMainParams : public CChainParams {
public:
    CMainParams() {
        pchMessageStart[0] = 0x1c;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0x5d;
        pchMessageStart[3] = 0xc7;
        vAlertPubKey = ParseHex("0400d42494baf668e11b6aa1c67ccb4453e14e91ce12e690cffe0b8cb5a778771d2e171e57a340e88f174ed0c242169b82fc2a14f2f33f660003aea7b9b8262dfb");
        vchSyncCheckpointPubKey = ParseHex("0488f8e1b9303774ed55dea1dbcb9b3a33760e095cacd41b1ae7391cf0c8223c343522a02776866a26055a0d9811fb1affe93cc63f9ab19709730428d7c6629481");
        nDefaultPort = 25178;
        nRPCPort = 25180;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 12);
        bnProofOfStakeLimit= CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "From Romania with love.";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1502755772, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1502755772;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 4342;

        hashGenesisBlock = genesis.GetHash();
		static uint256 hashGenesisBlockSupposed = uint256("0x00034443fcf8737ee859f0eb6ee371e3968df93f77a1de442a2ce6a743dd831d");
        
        assert(hashGenesisBlock == hashGenesisBlockSupposed);
        assert(genesis.hashMerkleRoot == uint256("0x311c0a6d490ee4c5ca617a88c95b90850e40f47322e7f863e00f9ff56fcdeeaf"));
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 60);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 158);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x50;
        pchMessageStart[1] = 0x61;
        pchMessageStart[2] = 0x79;
        pchMessageStart[3] = 0x17;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 12);
        vAlertPubKey = ParseHex("04181d3dba0e35ebf3296e61f2767574372033f354609cea967393bb51237095eba4639979b5114741094b401842a7ad9479e4299090d8c21c1c473af89d4d6fa1");
        nDefaultPort = 27899;
        nRPCPort = 27891;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 20687;

        hashGenesisBlock = genesis.GetHash(); 
		static uint256 hashGenesisBlockSupposed = uint256("0x000798d39546db7c959b5dbadaff007027c51101a478b2a9be63628df90d7ce5");
        
        assert(hashGenesisBlock == hashGenesisBlockSupposed);

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1502755772;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 22213;
        strDataDir = "regtest";
		
		static uint256 hashGenesisBlockSupposed = uint256("0x431557094a99f9b01a3f933d63b036348b8db23575316abcd9a99e44ade10393");
        
		// If genesis block hash does not match, then generate new genesis hash.
        if ((true) and (hashGenesisBlock != hashGenesisBlockSupposed)) {
            LogPrintf("Searching for genesis block...\n");
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            uint256 hashTarget = (~uint256(0) >> 1);
            while(true) {
                uint256 thash = genesis.GetHash();
                if (thash <= hashTarget)
                break;
                if ((genesis.nNonce & 0xFFF) == 0) {
                    LogPrintf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0) {
                    LogPrintf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            LogPrintf("genesis.nTime = %u \n", genesis.nTime);
            LogPrintf("genesis.nNonce = %u \n", genesis.nNonce);
            LogPrintf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
            LogPrintf("genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());
		}

        assert(hashGenesisBlock == hashGenesisBlockSupposed);

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
