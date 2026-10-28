// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Virtual name getters with the shape of the rowed
// LookupTablePostEffect::rva00111BE9 (28 bytes: construct the returned
// AsciiString from one literal through the rowed const-char constructor
// 0x00037BA0; `this` unused, ret 4). Each copy differs only in its literal,
// read from retail. The owning classes and slots are not recovered, so each
// keeps its address.

#include "ascii_string.h"

// ?getMapDir@Rva00300489@@UBE?AVAsciiString@@XZ @0x00300489 28B: "Maps"
class Rva00300489
{
public:
	virtual AsciiString getMapDir() const;
};

AsciiString Rva00300489::getMapDir() const
{
	return AsciiString("Maps");
}

// ?getMapExtension@MapCache@@QBE?AVAsciiString@@XZ @0x003004A5 28B: "map".
// MapCache::getMapExtension (ZH MapUtil.cpp returns AsciiString("map")); the
// GameInfo map-path builder 0x00621350 calls this address by that name.
class MapCache
{
public:
	AsciiString getMapExtension() const;
};

AsciiString MapCache::getMapExtension() const
{
	return AsciiString("map");
}

// ?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ @0x004BD9CB 28B: ""
class Rva004BD9CB
{
public:
	virtual AsciiString rva004BD9CB() const;
};

AsciiString Rva004BD9CB::rva004BD9CB() const
{
	return AsciiString("");
}

// ?getName@Rva005C44C3@@UBE?AVAsciiString@@XZ @0x005C44C3 28B: "IncreaseCommandPoints"
class Rva005C44C3
{
public:
	virtual AsciiString getName() const;
};

AsciiString Rva005C44C3::getName() const
{
	return AsciiString("IncreaseCommandPoints");
}

// ?rva005C4720@Rva005C4720@@UBE?AVAsciiString@@XZ @0x005C4720 28B: "StrengthenArmy"
class Rva005C4720
{
public:
	virtual AsciiString rva005C4720() const;
};

AsciiString Rva005C4720::rva005C4720() const
{
	return AsciiString("StrengthenArmy");
}

// ?rva005C4A1D@Rva005C4A1D@@UBE?AVAsciiString@@XZ @0x005C4A1D 28B: "UpgradeTroops"
class Rva005C4A1D
{
public:
	virtual AsciiString rva005C4A1D() const;
};

AsciiString Rva005C4A1D::rva005C4A1D() const
{
	return AsciiString("UpgradeTroops");
}
