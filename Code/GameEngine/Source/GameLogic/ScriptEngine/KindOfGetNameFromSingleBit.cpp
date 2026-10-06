// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// KindOfMaskType::getNameFromSingleBit, retail 0x00306218, 26 bytes.
//
// Ported from the exact BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/ScriptEngine/Parameter_WriteParameter_Thunk.cpp,
// getNameFromSingleBit at 0x0010C5B0, 26 bytes). BFME1 covers 181 named bits
// (bound 0xB5, table at 0x012AA068); BFME2 grew the mask to 218 entries
// (bound 0xDA, table at 0x00DBBE18), so only the array size changes here.
// The bound comes from the array's own size, keeping the unsigned `jae`
// comparison retail uses rather than a signed literal.

class KindOfMaskType
{
public:
	static const char *getNameFromSingleBit(int bitIndex);
};

// 218 named bits; only the bound is proven, the contents are not read here.
extern const char *TheKindOfBitNames[0xDA]; ///< retail [0x00DBBE18]

// ?getNameFromSingleBit@KindOfMaskType@@SAPBDH@Z
const char *KindOfMaskType::getNameFromSingleBit(int bitIndex)
{
	if (bitIndex < 0 || bitIndex >= sizeof(TheKindOfBitNames) / sizeof(TheKindOfBitNames[0]))
		return 0;
	return TheKindOfBitNames[bitIndex];
}
