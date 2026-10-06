// cl: /MD
// ?rva00407020@Rva00407020@@QAE_NXZ @0x00407020 94B: thiscall bool init reading +0xC +0x10 via TheCreateAHeroManager then conditional setters 0x406F12 0x406F27 0x406F3C then flag +0x39. Evidence: chain via 0x406F12 now ready; callees all rowed; callers 0x5B48BC 0x5B4CFB 0x5B56DC.
class CreateAHeroManager
{
public:
	int rva0021A016(unsigned int o, unsigned int i);
	int rva0021A041(unsigned int o, unsigned int i);
	int rva0021A06C(unsigned int o, unsigned int i);
};
class Rva00406F12
{
public:
	bool rva00406F12(int v);
};
class Rva00406F27
{
public:
	bool rva00406F27(int v);
};
class Rva00406F3C
{
public:
	bool rva00406F3C(int v);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva00407020
{
	int m_00[3];
	int m_0C;
	int m_10;
	char m_14[0x38 - 0x14];
	int m_38;
public:
	bool rva00407020();
};
bool Rva00407020::rva00407020()
{
	if (!TheCreateAHeroManager)
		return false;
	((Rva00406F12 *)this)->rva00406F12(TheCreateAHeroManager->rva0021A016(m_0C, m_10));
	((Rva00406F27 *)this)->rva00406F27(TheCreateAHeroManager->rva0021A041(m_0C, m_10));
	((Rva00406F3C *)this)->rva00406F3C(TheCreateAHeroManager->rva0021A06C(m_0C, m_10));
	m_38 |= 0x100;
	return true;
}
