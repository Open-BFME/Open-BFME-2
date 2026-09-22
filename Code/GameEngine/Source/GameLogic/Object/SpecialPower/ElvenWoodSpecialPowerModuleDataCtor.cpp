// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ, retail 0x004C3DA9, 75 bytes.
// Elven-wood data: the own table at 0x00C5D018 carries ElvenGroveObject at
// +0x88, ElvenNumObjects at +0x8C, ElvenWoodRadius at +0x90 (10.0f),
// ElvenWoodFX at +0x94 and ElvenWoodOCL at +0x98, matching every store
// below; the ModuleData factory at 0x251CB4 news 0x9C and the pool key at
// 0x4C3943 proves the class. Shape follows RousingSpeechUpdateModuleDataCtor
// (opaque 0x7C virtual base through the 0x4930A0 pin, derived vtable,
// BfmeE16 vector member through the 0x211E58 fold, /arch:SSE float).
// Retail runs base-call, vtable, vector-call, zeros and the 10.0f radius,
// which the init-list transcription reproduces: the vector element type is
// unproven, so the TU keeps the BfmeE16 stand-in (fold-equivalent and
// byte-correct, BattlePlanUpdate precedent) and the row carries the identity.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

protected:
	unsigned char m_pad[0x7C - 4];
};

Rva004930A0::~Rva004930A0()
{
}

class ElvenWoodSpecialPowerModuleData : public Rva004930A0
{
public:
	ElvenWoodSpecialPowerModuleData();
	virtual ~ElvenWoodSpecialPowerModuleData();

private:
	_STL::vector<BfmeE16> m_elves; // +0x7C, element unproven
	int m_elvenGroveObject; // +0x88
	int m_elvenNumObjects; // +0x8C
	float m_elvenWoodRadius; // +0x90
	int m_elvenWoodFX; // +0x94
	int m_elvenWoodOCL; // +0x98
};

ElvenWoodSpecialPowerModuleData::~ElvenWoodSpecialPowerModuleData()
{
}

// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ @0x4C3DA9
ElvenWoodSpecialPowerModuleData::ElvenWoodSpecialPowerModuleData()
	: Rva004930A0()
	, m_elvenGroveObject(0)
	, m_elvenNumObjects(0)
	, m_elvenWoodRadius(10.0f)
	, m_elvenWoodFX(0)
	, m_elvenWoodOCL(0)
{
}
