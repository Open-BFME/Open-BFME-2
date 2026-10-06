// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Virtual name getters with the shape of the rowed
// LookupTablePostEffect::rva00111BE9 (28 bytes: construct the returned
// AsciiString from one literal through the rowed const-char constructor
// 0x00037BA0; `this` unused, ret 4). Each copy differs only in its literal,
// read from retail. The owning classes and slots are not recovered, so each
// keeps its address.

#include "ascii_string.h"

// ?rva00300489@Rva00300489@@UBE?AVAsciiString@@XZ @0x00300489 28B: "Maps"
class Rva00300489
{
public:
	virtual AsciiString rva00300489() const;
};

AsciiString Rva00300489::rva00300489() const
{
	return AsciiString("Maps");
}

// ?rva003004A5@Rva003004A5@@UBE?AVAsciiString@@XZ @0x003004A5 28B: "map"
class Rva003004A5
{
public:
	virtual AsciiString rva003004A5() const;
};

AsciiString Rva003004A5::rva003004A5() const
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

// ?rva005C44C3@Rva005C44C3@@UBE?AVAsciiString@@XZ @0x005C44C3 28B: "IncreaseCommandPoints"
class Rva005C44C3
{
public:
	virtual AsciiString rva005C44C3() const;
};

AsciiString Rva005C44C3::rva005C44C3() const
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
