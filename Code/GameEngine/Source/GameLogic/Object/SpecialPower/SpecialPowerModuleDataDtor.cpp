// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1SpecialPowerModuleData@@UAE@XZ at retail 0x00548948 (60B). Base lineage
// proven by the two vtable installs (own 0xC6A520 then Snapshot 0xBBB554) and
// by ten callers including three tail-jmp derived dtors in
// Rva00548948Derived.cpp. BFME1 donor
// SpecialPowerModuleDataDestructorThunk.cpp has an empty body; retail frees
// the +4 vector buffer via _free at 0x30830. Member layout follows the
// matched copy ctor (vector<ScienceType> at +4). /EHs (not /EHsc) forces the
// single-state EH frame around the lone free; /EHsc stays frameless.
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class SpecialPowerModuleData : public Snapshot
{
public:
	virtual ~SpecialPowerModuleData();

private:
	_STL::vector<ScienceType> m_sciences; // +4
	void *m_unused10; // +0x10
	void *m_unused14; // +0x14
};

SpecialPowerModuleData::~SpecialPowerModuleData()
{
}
