// cl: /O1 /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??1Rva00161220@@UAE@XZ at 0x004F05F0 102B: ModuleData-style dtor with list teardown.
// Evidence: vptr 0x862B78 at +0 then Snapshot restore 0xBBB554; list at +0x14 via virtual slot0(0) plus operator delete 0x2FD60; flag bytes at +0x5D/+0x5E via +0x1C; layout matches Rva00161220Ctor TU; precedent PillageModuleDataDtor.

void __cdecl operator delete(void *p);

class Xfer;

#include "Common/Snapshot.h"

struct Rva004F05F0Node
{
	virtual void *rvaRelease(int flag);
	unsigned char pad04[8];
	Rva004F05F0Node *m_next;
};

struct Rva004F05F0Flags
{
	unsigned char pad[0x5D];
	unsigned char m_5D;
	unsigned char m_5E;
};

class Rva00161220 : public Snapshot
{
public:
	virtual ~Rva00161220();

private:
	unsigned char m_pad04[0x10]; // +04..+13
	Rva004F05F0Node *m_listHead; // +14
	unsigned char m_pad18[4]; // +18..+1B
	Rva004F05F0Flags *m_flags; // +1C
};

Rva00161220::~Rva00161220()
{
	Rva004F05F0Node *cur = m_listHead;
	while (cur != 0)
	{
		Rva004F05F0Node *next = cur->m_next;
		void *p = cur->rvaRelease(0);
		::operator delete(p);
		cur = next;
	}
	Rva004F05F0Flags *flag = m_flags;
	if (flag != 0 && flag->m_5D == 0)
	{
		flag->m_5E = 1;
		flag->m_5D = 1;
	}
	m_listHead = 0;
}
