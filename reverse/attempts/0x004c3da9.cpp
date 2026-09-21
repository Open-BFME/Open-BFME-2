// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ
// partial score=0.6 date=2026-09-21
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHs-c- /Oi /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ, retail 0x004C3DA9 (75 bytes).
// Frameless SpecialPower-side ModuleData for the elven wood: runs the pinned
// SpecialPower base ctor (0x4930A0, Devastate's Rva004930A0 shared base),
// installs the explicit vtable 0xC5CF38, builds the +0x7C vector slot in the
// body and zeroes the Elven fields matching the rowed base-call proc's table
// 0x0085D018 (ElvenGroveObject at +0x88, ElvenNumObjects at +0x8C,
// ElvenWoodRadius at +0x90 from the 10.0f global at 0xBC2428, ElvenWoodFX at
// +0x94, ElvenWoodOCL at +0x98). The vector goes through body placement-new
// (same one-byte stack allocator temporary as the PropagandaTower members)
// so the init stays EH-neutral and the body keeps retail order; a real
// vector member would auto-construct in the init phase ahead of the vtable
// and arm EH. Flat classes throughout (no declared dtors anywhere) keep the
// body frameless. The ElvenWoodSpecialPower pool key at 0x4C3943 sits in the
// same cluster; the ModuleData factory at 0x251CB4 (news 0x9C) is the only
// raw caller. Supersedes the 0x4C3DA9 ctor pin (row proves the body).

#include <new>
#include <vector>

struct BfmeE16 { float x, y, z, w; };

extern float g_elvenWoodRadiusDefault;

class Rva004930A0
{
public:
	Rva004930A0();

private:
	unsigned char m_pad[0x7C];
};

class ElvenWoodSpecialPowerModuleData : public Rva004930A0
{
public:
	ElvenWoodSpecialPowerModuleData();

private:
	unsigned char m_vecSlot[12]; // +0x7C (vector<BfmeE16> via placement)
	int m_grove; // +0x88
	int m_num; // +0x8C
	float m_radius; // +0x90
	void *m_fx; // +0x94
	void *m_ocl; // +0x98
};

// ??0ElvenWoodSpecialPowerModuleData@@QAE@XZ @0x4C3DA9
ElvenWoodSpecialPowerModuleData::ElvenWoodSpecialPowerModuleData()
	: Rva004930A0()
{
	*(unsigned int *)this = 0x00C5CF38;
	_STL::vector<BfmeE16> *vec = (_STL::vector<BfmeE16> *)m_vecSlot;
	__assume(vec != 0);
	new (vec) _STL::vector<BfmeE16>();
	m_grove = 0;
	m_num = 0;
	m_fx = 0;
	m_ocl = 0;
	m_radius = g_elvenWoodRadiusDefault;
}
