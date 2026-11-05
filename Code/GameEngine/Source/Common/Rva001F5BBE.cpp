// cl: /MD /EHsc
//
// ?rva001F5BBE@Rva001F58D4@@QAEXPAURva001F5BBEArg@@@Z, retail 0x001F5BBE, 123 bytes.
// List drain at +0x4C matching Rva001F58D4 TU: iterate sentinel list,
// copy 12B handle at node+8 via rowed RvaSmartPtr12 copy 0x4CC19, compare
// system +0xB4 against arg +0x74, destroy via rowed 0x1F462C, release via
// rowed handle dtor 0x4CBC0. Caller at 0x48FF56. Honest Rva names.

#include "../../Include/Common/RvaSmartPtr12.h"

inline RvaSmartPtr12::~RvaSmartPtr12() throw()
{
	if (field00)
		rva0004CBC0();
}

#include "../../Include/GameClient/ParticleSystemClass.h"

struct Rva001F5BBEArg
{
	int m_pad00[0x74 / 4];
	int m_id74;
};

struct ListNode001F5BBE
{
	ListNode001F5BBE *m_next;
	int m_pad04;
	RvaSmartPtr12 m_handle;
};

class Rva001F58D4
{
public:
	void rva001F58D4();
	void rva001F5BBE(Rva001F5BBEArg *arg);
	char m_pad00[0x10];
private:
	int m10[7]; // +0x10
	int m2c[7]; // +0x2C
	int m48; // +0x48
	void **m4c; // +0x4C
	int m50; // +0x50
	int m54; // +0x54
	int m58; // +0x58
	int m5c; // +0x5C
	float m60; // +0x60
	int m64; // +0x64
	char m_pad68[0xC];
	int m74; // +0x74
};

void Rva001F58D4::rva001F5BBE(Rva001F5BBEArg *arg)
{
	if (arg == 0)
		return;
	if (*m4c == (void *)m4c)
		return;
	ListNode001F5BBE *cur = (ListNode001F5BBE *)*m4c;
	do
	{
		ListNode001F5BBE *curCopy = cur;
		cur = cur->m_next;
		RvaSmartPtr12 tmp = curCopy->m_handle;
		if (tmp.field00 == 0)
			continue;
		ParticleSystem *sys = (ParticleSystem *)tmp.field00;
		if (sys->m_attachedToObjectID == arg->m_id74)
			sys->destroy();
	} while (cur != (ListNode001F5BBE *)m4c);
}
