// cl: /MD /EHsc
//
// ?rva001F5BBE@Rva001F58D4@@QAEXPAURva001F5BBEArg@@@Z, retail 0x001F5BBE, 123 bytes.
// List drain at +0x4C matching Rva001F58D4 TU: iterate sentinel list,
// copy 12B handle at node+8 via rowed RvaSmartPtr12 copy 0x4CC19, compare
// system +0xB4 against arg +0x74, destroy via rowed 0x1F462C, release via
// rowed handle dtor 0x4CBC0. Caller at 0x48FF56. Honest Rva names.

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_prev;
	void *m_next;
};

class RvaSmartPtr12
{
	public: void rva0004CBC0(); // 0x0004CBC0, the unlink the inline dtor null test calls
private:

public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12()
	{
		if (m_ptr != 0)
			reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
	}
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class ParticleSystem
{
public:
	void destroy();
	int m_pad00[0xB4 / 4];
	int m_idB4;
};

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
	void rva001F5BBE(Rva001F5BBEArg *arg);
private:
	char m_pad00[0x4C];
	void **m4c;
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
		if (tmp.m_ptr == 0)
			continue;
		ParticleSystem *sys = (ParticleSystem *)tmp.m_ptr;
		if (sys->m_idB4 == arg->m_id74)
			sys->destroy();
	} while (cur != (ListNode001F5BBE *)m4c);
}
