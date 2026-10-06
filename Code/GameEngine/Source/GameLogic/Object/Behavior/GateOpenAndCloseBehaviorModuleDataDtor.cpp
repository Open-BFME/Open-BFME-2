// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1GateOpenAndCloseBehaviorModuleData@@UAE@XZ, retail 0x00498D46, 145 bytes.
// Target evidence: the pinned ctor 0x00498E2E installs vtable 0x00C501B0,
// whose slot 0 is the scalar deleting dtor 0x00498DD7 calling this body;
// GateProxyBehaviorModuleData's dtor 0x00254045 is a 5-byte jmp here.
// Layout from the ctor's zeroing and member ctors: AsciiString at +0x14,
// four ref-counted pointers +0x1C..+0x28 (inline null-checked Release_Ref
// 0x00050ED3 here), AsciiString vectors at +0x2C and +0x38 (0x0002CC70).
// Teardown ends with the Snapshot vtable 0x00BBB554 store. Member types beyond
// the pinned callees are unrecovered.

#include "ascii_string.h"

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct Rva00498D46RefHolder
{
	~Rva00498D46RefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	OpaqueRefCounted *m_ptr;
};

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

class GateOpenAndCloseBehaviorModuleData : public Snapshot
{
public:
	virtual ~GateOpenAndCloseBehaviorModuleData();

private:
	unsigned char m_pad04[0x14 - 4];
	AsciiString m_string14;			// +0x14
	unsigned char m_pad18[4];
	Rva00498D46RefHolder m_ref1C;		// +0x1C
	Rva00498D46RefHolder m_ref20;		// +0x20
	Rva00498D46RefHolder m_ref24;		// +0x24
	Rva00498D46RefHolder m_ref28;		// +0x28
	RvaVecAscii m_vector2C;			// +0x2C
	RvaVecAscii m_vector38;			// +0x38
};

GateOpenAndCloseBehaviorModuleData::~GateOpenAndCloseBehaviorModuleData()
{
}
