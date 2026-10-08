// cl: /GX-
// ?rva005B35E8@Rva005B35E8@@QAEXXZ @0x005B35E8 33B
// Evidence: retail calls rowed Rva002162CFInvoke with TheRva00222A8BTarget plus owner at [ecx+4]+0x274 plus SetPowersSelectedNum literal plus arg at ecx+0x50 plus callers at 0x005B373D 0x005B3D89 0x005B45E8.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva002162CFInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &arg);

struct Rva005B35E8Holder
{
	char m_pad00[0x274];
	void *m_owner;
};

class Rva005B35E8
{
public:
	void rva005B35E8();
private:
	char m_pad00[0x4];
	Rva005B35E8Holder *m_holder;
	char m_pad08[0x48];
	unsigned int m_arg;
};

void Rva005B35E8::rva005B35E8()
{
	Rva002162CFInvoke((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_holder->m_owner, "SetPowersSelectedNum", m_arg);
}
