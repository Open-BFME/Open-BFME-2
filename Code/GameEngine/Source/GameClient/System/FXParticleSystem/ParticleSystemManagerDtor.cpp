// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /DBFME_SNAPSHOT_NAME_SLOT
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
#include "Common/Snapshot.h"

void __cdecl free(void *block);
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

struct DX8ThreadLockScope
{
	DX8ThreadLockScope() { BFME_DX8_Thread_Lock(); }
	~DX8ThreadLockScope() { BFME_DX8_Thread_Assert(); }
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;

private:
	char m_pad04[0x0C - 0x04];
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	~RefCountPtr(void)
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

class Rva001F81EC
{
public:
	~Rva001F81EC() { rva001F81EC(); }
	void rva001F81EC();

private:
	void *m_node;
};

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};

class Rva001F9D98Handle
{
public:
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

class Rva001F8D70Map
{
public:
	~Rva001F8D70Map();

private:
	void *m_unused00;
	void *m_buckets[3];
	unsigned int m_numElements;
};

class Rva001F9D98Buffer
{
public:
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

class Rva000411084
{
public:
	void *next();

	Rva001F9D98Node *m_cur;
	void *m_table;
};

class Rva000427195
{
public:
	void *first(Rva000411084 *it);
};

class Rva001F58D4
{
public:
	void rva001F58D4();
};

class Rva001F9D98 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva001F9D98();
	virtual void init();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	char m_pad10[0x4C - 0x10];
	Rva001F81EC m_list;                 // +0x4C
	char m_pad50[0x68 - 0x50];
	Rva001F9D98Handle m_handle;         // +0x68
	int m_74;                           // +0x74
	IUnknownView *m_device78;           // +0x78
	RefCountClass *m_ref7C;             // +0x7C
	RefCountPtr<RefCountClass> m_ref80; // +0x80
	bool m_84;                          // +0x84
	Rva001F8D70Map m_systems;           // +0x88
	Rva001F9D98Buffer m_buffer;         // +0x9C
};

Rva001F9D98::~Rva001F9D98()
{
	reinterpret_cast<Rva001F58D4 *>(this)->rva001F58D4();

	Rva000411084 it;
	reinterpret_cast<Rva000427195 *>(&m_systems)->first(&it);
	for (; it.m_cur != 0; it.next())
		::delete it.m_cur->m_value;

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
