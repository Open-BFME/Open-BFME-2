// ??0AutoAbilityBehaviorModuleData@@QAE@XZ
// partial score=0.9 date=2026-09-21
// cl: /O1 /GX /DNDEBUG /MD /arch:SSE
// stlport
#include <bitset>
#include <string.h>
namespace _STL { template<> bitset<128> &bitset<128>::reset(); }
class Rva003623E5Member {
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	unsigned char m_data[4];
};
class AutoAbilityQueryEntry {
public:
	AutoAbilityQueryEntry();
	~AutoAbilityQueryEntry();
private:
	int m_state;
	Rva003623E5Member m_filter;
};
AutoAbilityQueryEntry::AutoAbilityQueryEntry() { m_state |= -1; }
AutoAbilityQueryEntry::~AutoAbilityQueryEntry() {}
class UpdateModuleData {
public:
	UpdateModuleData() {}
};
class AsciiString {
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
private:
	void *m_data;
};
struct ForbiddenHolder {
	ForbiddenHolder();
	unsigned long m_bits[4];
};
class AutoAbilityBehaviorModuleData : public UpdateModuleData {
public:
	AutoAbilityBehaviorModuleData();
private:
	const void *m_vtable;
	unsigned int m_unused04;
	float m_maxScanRange;
	float m_minScanRange;
	float m_workingRadius;
	float m_idleTimeSeconds;
	AsciiString m_specialAbility;
	ForbiddenHolder m_forbidden;
	AutoAbilityQueryEntry m_query[6];
	unsigned char m_startsActive;
	unsigned char m_baseMaxRange;
	unsigned char m_adjustMelee;
	unsigned char m_allowSelf;
};
AutoAbilityBehaviorModuleData::AutoAbilityBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C41568))
	, m_maxScanRange(0.0f)
	, m_minScanRange(0.0f)
	, m_workingRadius(0.0f)
	, m_idleTimeSeconds(0.0f)
	, m_specialAbility()
	, m_forbidden()
{
	m_startsActive = 0;
	m_baseMaxRange = 0;
	m_adjustMelee = 0;
	m_allowSelf = 1;
	memset(&m_forbidden, 0, 0x10);
}
