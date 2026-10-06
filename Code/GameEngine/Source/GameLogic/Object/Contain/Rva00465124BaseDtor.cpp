// cl: /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1OpenContainModuleData@@UAE@XZ, retail 0x00257481, 134 bytes.
// Target evidence: the base ctor 0x00465124 installs vtable 0x00C43658, whose
// slot 0 is the scalar deleting dtor 0x00465221 calling this body. The
// TransportContainModuleData dtor 0x004684F1 and CaveContainModuleData's dtor
// 0x0025770F (a 5-byte jmp) reach it at the base-dtor position. Teardown
// order: +0x88 AsciiString vector (0x0002CC70), +0x4C (0x00256461), +0x48
// (0x002572D7), +0x44 and +0x40 filter members (0x00360D26), then inline
// null-checked Release_Ref (0x00050ED3) on the pointers at +0x3C and +0x38,
// then the Snapshot vtable 0x00BBB554 store. Member
// types other than the pinned callees are unrecovered; the owner class keeps
// its address-derived name (donor-free).

#include "Common/Snapshot.h"

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva00257481RefHolder
{
	~Rva00257481RefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	OpaqueRefCounted *m_ptr;
};

class Rva003623E5Member
{
public:
	~Rva003623E5Member();

private:
	int m_x;
};

class Rva003623E5Filter
{
public:
	~Rva003623E5Filter();

private:
	int m_x;
};

class Rva002572D7Member
{
public:
	~Rva002572D7Member();

private:
	int m_x;
};

class Rva00256461Member
{
public:
	~Rva00256461Member();

private:
	int m_x;
};

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

class __declspec(novtable) OpenContainModuleData : public Snapshot
{
public:
	virtual ~OpenContainModuleData();

private:
	unsigned char m_pad04[0x38 - 4];
	Rva00257481RefHolder m_ref38;		// +0x38
	Rva00257481RefHolder m_ref3C;		// +0x3C
	Rva003623E5Member m_filter40;		// +0x40
	Rva003623E5Filter m_filter44;		// +0x44
	Rva002572D7Member m_member48;		// +0x48
	Rva00256461Member m_member4C;		// +0x4C
	unsigned char m_pad50[0x88 - 0x50];
	RvaVecAscii m_vector88;			// +0x88
	unsigned char m_pad94[0x98 - 0x94];
};

OpenContainModuleData::~OpenContainModuleData()
{
}
