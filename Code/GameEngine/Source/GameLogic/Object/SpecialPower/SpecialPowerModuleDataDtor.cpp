// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /Ireference/shims/moduledata
// ??1SpecialPowerModuleData@@UAE@XZ @0x0049334F 115B. Common SpecialPower ModuleData
// intermediate base (0x7C bytes, ctor pinned at 0x004930A0): destroys strings
// at +0x6C/+0x18 via 0x00036410, filters at +0x3C/+0x38/+0x24 via 0x00360D26,
// releases ref at +0x14 via 0x00050ED3, restores Snapshot vtable 0x00BBB554.
// EH cleanup at 0x0078CD5B destroys the +0x10 pair through 0x004C9F38;
// the reference is the pair's second member, as in the constructor's view.
// Called by 27 derived dtors including PlayerUpgrade 0x004C7DD4. Layout from
// ctor 0x004930A0 and DominateEnemy/LevelGrant dtor precedents.

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

#include "ascii_string.h"
#include "Common/Snapshot.h"

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class RefHolder14
{
public:
	~RefHolder14() { if (m_ptr) m_ptr->Release_Ref(); }

private:
	OpaqueRefCounted *m_ptr;
};

class Rva004CEE6EMember
{
public:
	Rva004CEE6EMember();

private:
	int m_first;
	RefHolder14 m_ref14;
};

class __declspec(novtable) SpecialPowerModuleData : public Snapshot
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad04[12];
	Rva004CEE6EMember m_pair10;
	AsciiString m_str18;
	unsigned char m_pad1C[8];
	Rva00360D26Member m_filter24;
	unsigned char m_pad28[16];
	Rva00360D26Member m_filter38;
	Rva00360D26Member m_filter3C;
	unsigned char m_pad40[44];
	AsciiString m_str6C;
	unsigned char m_pad70[12];
};

SpecialPowerModuleData::~SpecialPowerModuleData()
{
}
