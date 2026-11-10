// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ??0Rva005646BC@@QAE@IAAUSrc005646BC@@@Z, retail 0x005646BC, 135 bytes.
// Copy-from-template ctor twin of the 0x0056413D shape: base Rva003ADEBF via
// rowed uint ctor 0x005640EC, subobject defaults at +0x10/+0x14/+0x18/+0x1c,
// final vtables Rva003AE2CF_v0 / s_slot3E4first / Rva003AE2CF_v10, float via
// rowed GameClientRandomVariable::getValue 0x002341A1, FX via just-landed
// TerrainCollisionModuleInfo::getEventFX 0x0056468E, bytes from +0x1d/+0x34, flag at +0x20.
// Evidence: calls 0x0056468E at 0x00564719; caller at 0x003ACB36.

#include "ascii_string.h"

class FXList
{
};

#include "../../../../Include/GameClient/GameClientRandomVariable.h"
#include "../../../../Include/GameClient/TerrainCollisionModuleInfo.h"

struct Src005646BC
{
	char m_pad0[0x1d];
	bool m_1d;
	char m_pad1e[2];
	FXParticleSystem::TerrainCollisionModuleInfo m_info;
};

extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7V3Vt01111D90@@6B@")[];

class Rva003ADEBF
{
public:
	Rva003ADEBF(unsigned int a);
	// The ctor's unwind funclet 0x00799DC0 destroys this base through the
	// 24-byte two-table restore at 0x003A583E (V3InlineTemplateDtor.cpp):
	// +8 null-guarded to 0x00C1C780, then +0 to 0x00C1B320.
	~Rva003ADEBF()
	{
		unsigned char *b08 = this ? (unsigned char *)this + 8 : 0;
		*(volatile unsigned int *)b08 = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
		*(volatile unsigned int *)this = ((unsigned int)__identifier("??_7V3Vt01111D90@@6B@"));
	}
public:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
	bool m_flagC;
};

// Rva003AE2CF_v0: matched references place it at VA 0xc1d3a0 (retail .rdata value 60).
extern "C" char Rva003AE2CF_v0 = 60;
extern "C" char s_slot3E4first;
// Rva003AE2CF_v10: matched references place it at VA 0xc1d390 (retail .rdata value -117).
extern "C" char Rva003AE2CF_v10 = -117;
// The copy constructor at 0x003AE315 emits this particle-info table.
extern "C" const void *const __identifier("??_7Rva003AE315@@6B@")[];

struct Rva005646BCSub
{
	Rva005646BCSub() : m_10((void *)__identifier("??_7Rva003AE315@@6B@")), m_14(0.0f), m_18(0), m_1c(false) {}
	// Unwind funclet 0x00799DC8 destroys this subobject (at +0x10) through the
	// folded Snapshot destructor 0x0049B47C: restore the Snapshot table.
	~Rva005646BCSub() { ((Snapshot *)this)->Snapshot::~Snapshot(); }
	void *m_10;
	float m_14;
	const FXList *m_18;
	bool m_1c;
};

class Rva005646BC : public Rva003ADEBF, public Rva005646BCSub
{
public:
	Rva005646BC(unsigned int a, struct Src005646BC &src);
	~Rva005646BC();
private:
	bool m_20;
};

Rva005646BC::Rva005646BC(unsigned int a, struct Src005646BC &src)
	: Rva003ADEBF(a), Rva005646BCSub()
{
	*(void **)this = (void *)&Rva003AE2CF_v0;
	*(void **)((char *)this + 8) = (void *)&s_slot3E4first;
	m_10 = (void *)&Rva003AE2CF_v10;
	float randomValue = src.m_info.m_08.getValue();
	m_14 = randomValue;
	m_18 = src.m_info.getEventFX();
	m_1c = src.m_info.m_14;
	m_flagC = src.m_1d;
	m_20 = true;
}
// _s_slot3E4first: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
