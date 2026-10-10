// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /Ireference/shims/moduledata
// stlport
//
// Opaque virtual destructors reached from scalar deleting dtors (pins at
// 0x000AB09C, 0x000AB141, 0x000B9866). Each tears down one member, then the
// base dtor stores its vtable. No derived vptr store (novtable).
// The first two names are the existing address-derived pins (owner types
// unrecovered). The third is EventParameter: its vftable 0x007C9CD0 holds
// ?xfer@EventParameter (row 0x003318F7) in slot 3 and a getter returning the
// "EventParameter" literal (stored right after the table) in slot 2.
//
// ??1Rva00AAD26@@UAE@XZ @0x000AAD26 54B: POD vector buffer at +0x08 freed
//   inline (0x00030830); base vtable 0x00BC93DC.
// ??1Rva00AB15D@@UAE@XZ @0x000AB15D 54B: same at +0x0C; base vtable 0x00BC93DC.
// ??1EventParameter@@UAE@XZ @0x000B6971 48B: string at +0x10 (0x00036410);
//   base is Snapshot (0x00BBB554).
extern "C" const void *const vtbl_00BC93DC[];  // ??_7Rva000A8EF6@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC93DC=??_7Rva000A8EF6@@6B@")

#include <vector>
#include "Common/Snapshot.h"

class Rva000BC93DCBase
{
public:
	virtual ~Rva000BC93DCBase();
};

// ?Rva000BC93DCBase::~Rva000BC93DCBase present-unmatched
inline Rva000BC93DCBase::~Rva000BC93DCBase()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BC93DC));
}

#include "ascii_string.h"

class __declspec(novtable) Rva00AAD26 : public Rva000BC93DCBase
{
public:
	virtual ~Rva00AAD26();

private:
	int m_04;
	_STL::vector<int> m_vector08;	// +0x08
};

Rva00AAD26::~Rva00AAD26()
{
}

class __declspec(novtable) Rva000AB0D4 : public Rva00AAD26
{
public:
	virtual ~Rva000AB0D4();
};

Rva000AB0D4::~Rva000AB0D4()
{
}

class __declspec(novtable) Rva00AB15D : public Rva000BC93DCBase
{
public:
	virtual ~Rva00AB15D();

private:
	int m_04[2];
	_STL::vector<int> m_vector0C;	// +0x0C
};

Rva00AB15D::~Rva00AB15D()
{
}

class __declspec(novtable) EventParameter : public Snapshot
{
public:
	virtual ~EventParameter();

private:
	int m_04[3];
	AsciiString m_string10;	// +0x10
};

EventParameter::~EventParameter()
{
}
