// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /Ireference/shims/moduledata /DBFME_SNAPSHOT_NAME_SLOT
//
// ??1Rva001F9D98@@UAE@XZ retail 0x001F9D98..0x001F9EA7 (271 bytes EH).
// The destructor of FXParticleSystem::ParticleSystemManager: the class whose
// primary vtable 0x00BE18C8 (deleting dtor 0x001FA779) has init 0x001F3FEA
// (WorldBuilder 0x00B15BE0 FXParticleSystem::ParticleSystemManager::init) and
// whose Snapshot vtable 0x00BE18B8 at +0x0C has xfer 0x001F9105 (WorldBuilder
// 0x00B17890 ParticleSystemManager::DoXfer); the constructor is 0x001FA69F.
// The address-derived class name is kept to match the rowed deleting dtor.
// Target evidence: the rowed reset 0x001F58D4 runs; every system in the
// +0x88 ID map (iterated with the pinned first 0x00427195 and rowed next
// 0x00411084; value at node +8) is destroyed through a global delete; under
// the DX8 thread lock (rowed 0x0011F520 / 0x00120F50) the +0x78 COM object
// is released (slot 2) and cleared and the +0x7C reference released and
// cleared. Members then die in reverse: the +0x9C buffer (free) the +0x88
// map (0x001F8D70) the +0x80 reference the +0x68 handle (0x0004CBC0) and
// the +0x4C list (0x001F81EC); the Snapshot base is inline and the
// SubsystemInterface base dtor 0x001B4E74 is rowed.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "Common/Snapshot.h"

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

struct DX8ThreadLockScope
{
	DX8ThreadLockScope() { BFME_DX8_Thread_Lock(); }
	~DX8ThreadLockScope() { BFME_DX8_Thread_Assert(); }
};

#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "../../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

template <class T>
class Rva0007B724RefCountPtr
{
public:
	Rva0007B724RefCountPtr(void) : Referent(0) {}
	~Rva0007B724RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}

private:
	T *Referent;
};

struct IUnknownView
{
	virtual long __stdcall QueryInterface(void *, void **) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

// Empty allocator tag for the folded STLport list/vector base ctors.
struct Rva001FA69FAlloc
{
	Rva001FA69FAlloc() {}
};

// The +0x4C list's base: its out-of-line ctor is the ICF-folded
// _List_base ctor 0x00280A8D, reached by a qualified call to its rowed
// Coord3D instantiation.
struct Coord3D;
namespace _STL
{
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc> class _List_base
	{
	public:
		_List_base(const _Alloc &alloc);
	};
}
typedef _STL::_List_base<Coord3D, _STL::allocator<Coord3D> > Rva00280A8DListBase;

class Rva001F81ECBase
{
public:
	__declspec(dllimport) __forceinline Rva001F81ECBase(const Rva001FA69FAlloc &alloc)
	{
		((Rva00280A8DListBase *)this)->Rva00280A8DListBase::_List_base(
			*(const _STL::allocator<Coord3D> *)&alloc);
	}

protected:
	void *m_node;
};

class Rva001F81EC : public Rva001F81ECBase
{
public:
	Rva001F81EC(const Rva001FA69FAlloc &alloc = Rva001FA69FAlloc()) : Rva001F81ECBase(alloc) {}
	~Rva001F81EC() { rva001F81EC(); }
	void rva001F81EC();
};

#include "../../../../Include/Common/RvaSmartPtr12.h"

class Rva001F9D98Handle
{
public:
	Rva001F9D98Handle() : m_p(0), m_04(0), m_08(0) {}
	// RvaSmartPtr12(void *) (SmartPtrCopyCtor.cpp): attach when non-null,
	// else clear the two link words.
	explicit Rva001F9D98Handle(void *ptr)
	{
		m_p = ptr;
		if (m_p != 0)
			reinterpret_cast<RvaSmartPtr12 *>(this)->attach();
		else
		{
			m_08 = 0;
			m_04 = 0;
		}
	}
	Rva001F9D98Handle &operator=(const Rva001F9D98Handle &that)
	{
		reinterpret_cast<RvaSmartPtr12 *>(this)->operator=(
			*reinterpret_cast<const RvaSmartPtr12 *>(&that));
		return *this;
	}
	~Rva001F9D98Handle()
	{
		if (m_p)
			reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
	}

private:
	void *m_p;
	void *m_04;
	void *m_08;
};

class Rva001FA440 { public: Rva001FA440(); };
class Rva001F8D70Map
{
public:
	// Construction is the rowed ??0Rva001FA440, reached by a qualified call.
	__declspec(dllimport) __forceinline Rva001F8D70Map() { ((Rva001FA440 *)this)->Rva001FA440::Rva001FA440(); }
	~Rva001F8D70Map();

private:
	void *m_unused00;
	void *m_buckets[3];
	unsigned int m_numElements;
};

// The 12-byte vector ctor 0x001F81BF, reached by a qualified call to its
// rowed GPU particle storage twin.
class Rva003B0412 { public: Rva003B0412() throw(); };
class Rva001F9D98Buffer
{
public:
	__declspec(dllimport) __forceinline Rva001F9D98Buffer() throw() { ((Rva003B0412 *)this)->Rva003B0412::Rva003B0412(); }
	~Rva001F9D98Buffer()
	{
		if (m_data)
			free(m_data);
	}

private:
	void *m_data;
};

class Rva001F9D98System
{
public:
	virtual ~Rva001F9D98System();
};

struct Rva001F9D98Node
{
	Rva001F9D98Node *m_next;
	int m_key;
	Rva001F9D98System *m_value;
};

#include "../../../../Include/GameClient/Rva000411084.h"

#include "../../../../Include/GameLogic/Rva000427195.h"

class Rva001F58D4
{
public:
	void rva001F58D4();
};

class Rva001F9D98 : public SubsystemInterface, public Snapshot
{
public:
	Rva001F9D98();
	virtual ~Rva001F9D98();
	virtual void init() = 0;

protected:
	virtual void loadPostProcess() = 0;
	virtual const char *GetSnapshotName() const = 0;
	virtual void xfer(Xfer *xfer) = 0;

private:
	int m_10[7];                        // +0x10
	int m_2C[7];                        // +0x2C
	int m_48;                           // +0x48
	Rva001F81EC m_list;                 // +0x4C
	int m_50;                           // +0x50
	int m_54;                           // +0x54
	int m_58;                           // +0x58
	int m_5C;                           // +0x5C
	float m_60;                         // +0x60
	int m_64;                           // +0x64
	Rva001F9D98Handle m_handle;         // +0x68
	int m_74;                           // +0x74
	IUnknownView *m_device78;           // +0x78
	RefCountClass *m_ref7C;             // +0x7C
	Rva0007B724RefCountPtr<RefCountClass> m_ref80; // +0x80
	bool m_84;                          // +0x84
	Rva001F8D70Map m_systems;           // +0x88
	Rva001F9D98Buffer m_buffer;         // +0x9C
};

Rva001F9D98::~Rva001F9D98()
{
	reinterpret_cast<Rva001F58D4 *>(this)->rva001F58D4();

	Rva000411084 it;
	reinterpret_cast<Rva000427195 *>(&m_systems)->first(&it);
	for (; it.m_current != 0; it.next())
		::delete static_cast<Rva001F9D98Node *>(it.m_current)->m_value;

	{
		DX8ThreadLockScope lock;
		if (m_device78)
			m_device78->Release();
		m_device78 = 0;
		if (m_ref7C)
		{
			m_ref7C->Release_Ref();
			m_ref7C = 0;
		}
	}
}

// ??0Rva001F9D98@@QAE@XZ retail 0x001FA69F..0x001FA779 (218 bytes EH): the
// constructor. Bases SubsystemInterface (rowed 0x001B4E63) and inline
// Snapshot, then the members in order: +0x4C list (folded _List_base ctor
// 0x00280A8D), +0x68 handle, +0x80 reference, +0x84 flag, +0x88 ID map
// (0x001FA440) and +0x9C buffer (folded 12-byte vector ctor 0x001F81BF).
// The body zeroes the scalars and both seven-slot arrays, resets the handle
// from an empty temporary (rowed assignment 0x0004CC3D, unlink 0x0004CBC0)
// and clears +0x74/+0x78/+0x7C.
Rva001F9D98::Rva001F9D98() : m_84(false)
{
	m_48 = 0;
	m_5C = 0;
	m_64 = 0;
	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_60 = 0.0f;
	for (int i = 0; i < 7; i++)
	{
		m_10[i] = 0;
		m_2C[i] = 0;
	}
	m_handle = Rva001F9D98Handle(0);
	m_74 = 0;
	m_device78 = 0;
	m_ref7C = 0;
}
