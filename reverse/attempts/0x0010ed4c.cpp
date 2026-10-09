// ??0Gen0002857E@@QAE@PAVRva000A7E9E@@ABVAsciiString@@@Z
// partial score=0.88135593220339 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?handle@Gen0002857E@@QAEXXZ at 0x0010ECBD (39B).
// Mutex-guarded increment of the counter at +0x34 via MilesMutexGuard over owner mutex at +0x50.
// Evidence: BFME1 donor game/GameEngine/Source/Common/Gen0002857EHandle.cpp; retail pushes 0 and [eax+0x50] into ctor 0x0004120E and calls dtor 0x0004122F; LINK BONUS caller in Rva00690FF0Handle.cpp.

#include "ascii_string.h"
#include "Common/Rva00041004Lock.h"
#include <string.h>
class __declspec(novtable) Rva0040F9D : public Rva0040EDB {
public:
 Rva0040F9D(int,int,const char*,void*);
 virtual ~Rva0040F9D() {}
};
class MilesMutexGuard
{
public:
	MilesMutexGuard(void *m, int x);
	~MilesMutexGuard();
private:
	void *m_mutex;
	bool m_flag;
};

class Gen0002857E;

// Retail 0x10ED1F passes the owner at entry+4 and the complete entry pointer
// to the verified manager helper at 0xA8127. Both owner views put the mutex
// at +0x50; the helper's entry view reads +0x30/+0x38/+0x44.
struct Rva000A80A8Item;

class Rva000A7E9E
{
public:
	char m_pad[0x50];
	void *m_mutex;
	void rva000A8127(Rva000A80A8Item *entry);
};

class Gen0002857E
{
public:
	Gen0002857E(Rva000A7E9E *,const AsciiString &);
	void handle();
	void release();
private:
	AsciiString m_name;
	Rva000A7E9E *m_owner;
	unsigned int m_waveInfo[9];
	void *m_data;
	unsigned int m_size;
	// volatile so the read-modify-write is not strength-reduced to `inc`.
	volatile int m_count;
	unsigned int m_lastReleaseTime;
	int m_priority;
	bool m_allocated;
	Rva0040F9D m_ready;
	Rva0040F9D m_failed;
};

void Gen0002857E::handle()
{
	MilesMutexGuard guard(m_owner->m_mutex, 0);
	m_count = m_count + 1;
}

extern "C" __declspec(dllimport) unsigned int __stdcall AIL_ms_count(void);

void Gen0002857E::release()
{
	void *mutex = m_owner->m_mutex;
	MilesMutexGuard guard(mutex, 0);
	m_count -= 1;
	if (m_count == 0)
	{
		m_lastReleaseTime = AIL_ms_count();
		m_owner->rva000A8127(reinterpret_cast<Rva000A80A8Item *>(this));
	}
}

Gen0002857E::Gen0002857E(Rva000A7E9E *owner,const AsciiString &name)
 :m_name(name),m_owner(owner),m_data(0),m_size(0),m_count(0),m_lastReleaseTime(0),m_priority(0),m_allocated(false),m_ready(1,0,0,0),m_failed(1,0,0,0)
{ memset(m_waveInfo,0,sizeof(m_waveInfo)); }
