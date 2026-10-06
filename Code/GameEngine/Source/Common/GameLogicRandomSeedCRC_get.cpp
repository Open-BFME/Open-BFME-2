// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetGameLogicRandomSeedCRC@@YAIXZ @ 0x00233F70 (17B). Trial port from
// Open-BFME-1 Code/GameEngine/Source/Common/System/random_value.cpp
// (GetGameLogicRandomSeedCRC), calling BFMEComputeCRC instead of CRC_Memory:
// retail hashes the 6-word logic seed with the rotate-add packet hash.
// Dedicated TU; the seed array is TU-local here and patched to retail's
// data address.
typedef unsigned int UnsignedInt;

static UnsignedInt theGameLogicSeed[6];

UnsignedInt BFMEComputeCRC(const unsigned char *data, UnsignedInt length, UnsignedInt crc);

// ?GetGameLogicRandomSeedCRC@@YAIXZ
UnsignedInt GetGameLogicRandomSeedCRC(void)
{
	return BFMEComputeCRC((const unsigned char *)theGameLogicSeed, sizeof(theGameLogicSeed), 0);
}
