// ??0CallHelpOnDamageModuleData@@QAE@XZ
// finish candidate from reverse/attempts/0x004bb3a7.cpp (score=0.93)
// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// CallHelpOnDamageModuleData default constructor @0x4BB3A7 (116B). INI tables
// 0x00C6BB18 and 0x00C59F70 name the members (DamageTypes +8, CallRadius +C,
// CallDelay +10, MoveToAttacker +14, ValidObjects +18). Retail unwind map:
// state 0 destroys the polymorphic base, state 1 the filter at +0x18 through
// the pinned Rva003623E5Filter dtor 0x360D26, so the filter is a real member
// (its ctor 0x3623E5 and applyFilter 0x362120 are pinned under that class)
// and the shared fixed storage 0x009FEFA4 is copied by value.
//
// The +8 damage mask is a plain 4-byte member listed FIRST in the ctor's
// initializer list, not a second base: a second base puts the mask init in a
// separate EH region and cl then refuses to hoist the 100.0f constant load
// above the `or [esi+8],-1` (retail loads xmm0 first). With m_mask a member in
// the same region the scheduler hoists the load and the body is exact. The
// symbol is the ctor call in the byte-true CallHelpOnDamage data factory.
extern const int g_009BA4E4;
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	~BfmeFixedStorage0004543D() {}
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_009FEFA4;
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);
private:
	int m_x;
};
class UpdateModuleData
{
public:
	UpdateModuleData() {}
	virtual ~UpdateModuleData();
private:
	int m_gap04;
};
class CallHelpOnDamageModuleData : public UpdateModuleData
{
public:
	CallHelpOnDamageModuleData();
	virtual ~CallHelpOnDamageModuleData();
private:
	unsigned int m_mask;			// +8
	float m_callRadius;			// +0xC
	int m_callDelay;			// +0x10
	bool m_moveToAttacker;			// +0x14
	Rva003623E5Filter m_validObjects;	// +0x18
};
// ??0CallHelpOnDamageModuleData@@QAE@XZ @0x004BB3A7
CallHelpOnDamageModuleData::CallHelpOnDamageModuleData() :
	m_mask(0xFFFFFFFF),
	m_callRadius(100.0f),
	m_callDelay(4 * g_009BA4E4),
	m_moveToAttacker(false)
{
	m_validObjects.applyFilter(g_009FEFA4);
}
