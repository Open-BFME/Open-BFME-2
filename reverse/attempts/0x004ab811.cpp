// ??0LargeGroupAudioUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.95 date=2026-09-23
??0LargeGroupAudioUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.95 date=2026-09-23 banks V5-shape (take-addr initials + explicit 5-group + floats-first + plain local + late call); SOLE WALL lea-ecx-plus30 above group (retail below group); refuted plain/direct/barrier/plain-dupes(merge); see memory.md 2026-09-23 ~14:30Z
// cl: /O1 /DNDEBUG /MD /arch:SSE
// stlport
#include <bitset>
namespace _STL { template<> bitset<128> &bitset<128>::reset(); }
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Thing;
class ModuleData;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};
class CondStore
{
public:
	void init();
};
class LargeGroupAudioUpdate : public UpdateModule
{
public:
	LargeGroupAudioUpdate(Thing *thing, const ModuleData *moduleData);
private:
	const void *m_secondary20;
	const void *m_secondary24;
	float m_28;
	float m_2C;
	CondStore m_cond;
	unsigned char m_pad31[0x7C - 0x31];
	unsigned long m_7C[4];
	bool m_8C;
	bool m_8D;
	int m_90;
};
LargeGroupAudioUpdate::LargeGroupAudioUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	int *slot20 = (int *)&m_secondary20;
	*slot20 = (int)0x00C6FFFC;
	int *slot24 = (int *)&m_secondary24;
	*slot24 = (int)0x00BFB698;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_secondary20 = &s_secondary20;
	m_secondary24 = &s_secondary24;
	m_28 = 0.0f;
	m_2C = 0.0f;
	CondStore *condSlot = &m_cond;
	condSlot->init();
	((_STL::bitset<128> *)m_7C)->reset();
	m_90 |= -1;
	m_8C = false;
	m_8D = false;
}
