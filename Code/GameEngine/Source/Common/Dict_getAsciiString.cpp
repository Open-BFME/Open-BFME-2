// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?known@Dict@@QBE_NW4NameKeyType@@W4DataType@1@@Z
// retail 0x002A9880, 21 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Dict_getAsciiString.cpp (reference/open-bfme-1
// @ 6d943426). Compiled /Os the donor body is byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text). Only the placed body
// is defined here; the donor's other definition (getAsciiString) is omitted,
// and with it the AsciiString/StringBase view that body alone needed.
//
// Retail's known() is a thin wrapper: it delegates to getType and compares the
// result against the type argument, so the emission is getType's call plus the
// compare and the equal/unequal tail. Nothing about the value's type enters it.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
enum NameKeyType { NAMEKEY_INVALID = 0 };

class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING,
		DICT_UNICODESTRING
	};

	DataType getType(int key) const;
	bool known(NameKeyType key, DataType type) const;
};

bool Dict::known(NameKeyType key, DataType type) const
{
	return getType(key) == type;
}
