// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

// Native 0x00262387 installs table RVA 0x007F91B0. Use the existing compiler
// table emitted by the matched PartitionFilterPossibleToAttack view, rather
// than another array under an address-derived name. Its three native slots
// are the deleting destructor, allow and the shared base getPlayerMask.
// The existing row's class/method spelling remains an unverified view.
extern "C" const void *const __identifier("??_7PartitionFilterPossibleToAttack@@6B@")[3];

class Rva00149E60
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00149E60 &set(int a, int b, int c);
};

Rva00149E60 &Rva00149E60::set(int a, int b, int c)
{
	m_08 = b;
	m_04 = 0;
	m_00 = (void *)__identifier("??_7PartitionFilterPossibleToAttack@@6B@");
	m_0C = c;
	m_10 = a;
	return *this;
}
