// Three constant-field constructors from the R3 scalar-field family.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/R3ScalarFieldConstructors3.cpp); trimmed to
// the three T1 bodies the sweep places. Identity is not recovered: names are
// addresses and offsets.

class Rva0013A8B0
{
public:
	Rva0013A8B0();
	int m_00, m_04, m_08, m_0C, m_10;
	char m_pad14[8];
	int m_1C, m_20;
	char m_pad24[4];
	int m_28;
	char m_pad2C[0x3C - 0x2C];
	int m_3C;
	char m_pad40[4];
	int m_44;
};
Rva0013A8B0::Rva0013A8B0()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_1C = 0;
	m_20 = 0;
	m_28 = 0;
	m_3C = 0;
	m_44 = 0;
}

class Rva0040C1F0
{
public:
	Rva0040C1F0();
	int m_00, m_04, m_08;
	char m_0C, m_0D;
	int m_10, m_14, m_18, m_1C, m_20, m_24;
};
Rva0040C1F0::Rva0040C1F0()
{
	m_00 = 4;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_0D = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
}

class Rva00704980
{
public:
	Rva00704980();
	int m_00, m_04, m_08, m_0C, m_10, m_14, m_18;
	char m_1C, m_1D, m_1E, m_1F;
};
Rva00704980::Rva00704980()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_1D = 0;
	m_1E = 0;
	m_1F = 0;
}

// Lead: AssistanceRequestData's zero initializer in Open-BFME-1
// 9cbfb551fe20dae985f91f2319d8997287b6a705 GameLogic/Object/Weapon.cpp.
// Native 2C95CC..2C95DE is a complete thiscall leaf between two independently
// bounded Ghidra functions, returning this after clearing +0/+4 and float+8.
// The original class, constructor/reset purpose and first two field types
// remain unknown; the method spelling claims only the native operation/ABI.
class Rva002C95CCFields
{
public:
    Rva002C95CCFields *initialize();
    unsigned int m_00;
    unsigned int m_04;
    float m_08;
};
Rva002C95CCFields *Rva002C95CCFields::initialize()
{
    m_00 = 0;
    m_04 = 0;
    m_08 = 0.0f;
    return this;
}

// Current BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 WaterRenderObjConstructor.cpp
// Boxed<float> constructor is a source guide, not proof of this target's class
// or constructor role. Native30F2AB..30F2BA stores a single stack float at+0,
// returns this, and RET4; aligned from known30F14C/351, whose final JMP at
//30F2A9 stays inside its own teardown, then next independent store starts30F2BA.
// The neutral initialize method preserves only the observed operation/ABI.
class Rva0030F2ABFields
{
public:
    Rva0030F2ABFields *initialize(float value);
    float m_value;
};
Rva0030F2ABFields *Rva0030F2ABFields::initialize(float value)
{
    m_value=value;
    return this;
}
