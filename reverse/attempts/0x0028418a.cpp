// ??1Rva0028418A@@UAE@XZ
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR draft. ??1Rva0028418A@@UAE@XZ retail 0x0028418A (262 bytes), also
// pinned as ??1TerrainLogic@@UAE@XZ (vtable 0x00BFB2C8; the derived W3D
// destructor 0x00062AF7 tail-calls it). Bases Snapshot (+0x00)
// SubsystemInterface (+0x04) and two roots at +0x10/+0x14 whose final
// vtables fold to 0x00BC6F34; body: TerrainLogic::reset 0x00283567 then the
// owned +0x584 object (direct dtor 0x00283081 plus operator delete) then the
// members +0x578 buffer +0x56C tree +0x64 list +0x5C..+0x50 holders +0x4C
// name +0x30 buffer (EH states 0x0C..0x03 all match).
// Remaining diff: cl keeps this+4 in ebx across the body (and spills the
// owned pointer) where retail rematerialises lea ecx,[esi+4] and keeps the
// owned pointer in ebx; one frame slot more.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *block);
void __cdecl operator delete(void *block);

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void reset();

private:
	char m_pad04[0x0C - 0x04];
};

class Base0C_80FD
{
public:
	virtual ~Base0C_80FD() {}
};

class Rva0028418ABase10 : public Base0C_80FD
{
public:
	virtual ~Rva0028418ABase10() {}
};

// A second root whose vtable folds with Base0C_80FD's in retail (0x00BC6F34).
class Rva0056B188Second
{
public:
	virtual ~Rva0056B188Second() {}
};

class Rva0028418ABase14 : public Rva0056B188Second
{
public:
	virtual ~Rva0028418ABase14() {}
};

// The +0x30 and +0x578 buffers (freed through the CRT-routed free 0x00030830).
struct Rva0028418ABuffer
{
	~Rva0028418ABuffer()
	{
		if (m_data)
			Rva00030830GameFree(m_data);
	}

	void *m_data;
};

class Rva002833E7Holder
{
public:
	~Rva002833E7Holder();

private:
	void *m_ptr;
};

class Rva00283426
{
public:
	void rva00283426();

private:
	void *m_head;
};

struct Rva0028418AList
{
	~Rva0028418AList() { reinterpret_cast<Rva00283426 *>(this)->rva00283426(); }

	void *m_head;
};

class Rva0027F4CB
{
public:
	~Rva0027F4CB();

private:
	char m_data[0x0C];
};

class Rva00283081
{
public:
	virtual ~Rva00283081();

	// The owner frees it with a direct destructor call and the global
	// operator delete.
	static void destroy(Rva00283081 *p)
	{
		p->Rva00283081::~Rva00283081();
		::operator delete(p);
	}
};

// TerrainLogic's reset (rowed 0x00283567) overrides SubsystemInterface's, so
// a direct call from the full object adjusts this to the +0x04 base.
class TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
	virtual void reset();
};

class Rva0028418A : public Snapshot, public SubsystemInterface, public Rva0028418ABase10, public Rva0028418ABase14
{
public:
	virtual ~Rva0028418A();

private:
	char m_pad18[0x30 - 0x18];
	Rva0028418ABuffer m_buffer30; // +0x30
	char m_pad34[0x4C - 0x34];
	AsciiString m_name4C; // +0x4C
	Rva002833E7Holder m_holder50; // +0x50
	Rva002833E7Holder m_holder54; // +0x54
	Rva002833E7Holder m_holder58; // +0x58
	Rva002833E7Holder m_holder5C; // +0x5C
	char m_pad60[0x64 - 0x60];
	Rva0028418AList m_list64; // +0x64
	char m_pad68[0x56C - 0x68];
	Rva0027F4CB m_tree56C; // +0x56C
	Rva0028418ABuffer m_buffer578; // +0x578
	char m_pad57C[0x584 - 0x57C];
	Rva00283081 *m_584; // +0x584
};

Rva0028418A::~Rva0028418A()
{
	reinterpret_cast<TerrainLogic *>(this)->TerrainLogic::reset();
	Rva00283081 *&slot = m_584;
	Rva00283081 *owned = slot;
	if (owned)
	{
		owned->Rva00283081::~Rva00283081();
		::operator delete(owned);
		slot = 0;
	}
}
