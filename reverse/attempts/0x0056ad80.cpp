// ??0Rva0056AD80@@QAE@PAX@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD /GX
//
// ??0Rva0056AD80@@QAE@PAX@Z @0x0056AD80 85B.
// EH constructor: null +4, install 0x00C37298 vftable at +8, run the arg's
// pinned 0x003F855D on the +0xC member with EH state 1, then install the
// 0x00C6D058 vftable at +0 and the 0x00C6D01C vftable at +8, and store the
// arg at +0x10. Two empty bases with external dtors supply the two EH
// states. Unblocks 0x0056AF4B. Honest address-derived name.
class Rva003F855D
{
public:
	void rva003F855D(void *arg);
};

extern "C" const void *const vtbl_00C37298[];
extern "C" const void *const vtbl_00C6D058[];
extern "C" const void *const vtbl_00C6D01C[];

struct Rva0056AD80M0C
{
	~Rva0056AD80M0C();
	char m_data[4];
};

struct Rva0056AD80Extra
{
	~Rva0056AD80Extra();
	char m_data[4];
};

class Rva0056AD80
{
public:
	Rva0056AD80(void *arg);
private:
	char m_pad[0xC];
	Rva0056AD80M0C m_0C;
	void *m_10;
	Rva0056AD80Extra m_extra;
};

Rva0056AD80::Rva0056AD80(void *arg)
{
	*(int *)((char *)this + 4) = 0;
	*(volatile unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C37298);
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D058);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D01C);
	((Rva003F855D *)arg)->rva003F855D(&m_0C);
	m_10 = arg;
}
