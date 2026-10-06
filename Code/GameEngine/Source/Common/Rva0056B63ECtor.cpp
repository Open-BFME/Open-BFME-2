// cl: /O1 /MD
//
// ??0Rva0056B63E@@QAE@PAX@Z @0x0056B63E 42B.
// Constructor: run the pinned 0x0056B7E4 initializer on the +0x14 member,
// clear the +0x5C/+0x5D/+0x5E flags, install the 0x00C3789C vftable at +0,
// and set the +0x58 count to 15. Honest address-derived name.
class Rva0056B7E4
{
public:
	void rva0056B7E4(void *arg);
};
extern "C" const void *const vtbl_00C3789C[];

class Rva0056B63E
{
public:
	Rva0056B63E(void *arg);
private:
	char m_pad[0x58];
	unsigned m_58;
	unsigned char m_5C;
	unsigned char m_5D;
	unsigned char m_5E;
};

Rva0056B63E::Rva0056B63E(void *arg)
{
	((Rva0056B7E4 *)this)->rva0056B7E4(arg);
	m_5C = 0;
	m_5D = 0;
	m_5E = 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C3789C);
	m_58 = 15;
}
