// cl: /O1 /MD
// ?rva0033A9A5@Rva0033A9A5@@QAEPBVRva00427157@@PBX@Z @0x0033A9A5 61B.
// Array scan over 0x104 entries from +0x3EC to +0x3F0 via rowed
// Rva0033A8D9 tester; on match return entry armor else rowed
// LivingWorldAutoResolveArmorStore::getDefault via g_00E031F0.
// Evidence: rowed 0x0033A8D9 plus rowed 0x0042724D plus ret-4.
class Rva00427157;

class Rva0033A8D9
{
public:
	bool rva0033A8D9(const void *mask) const;
};

struct Rva0033A9A5Entry
{
	const Rva00427157 *armor;
	char m_pad[0x104 - 4];
};

class LivingWorldAutoResolveArmorStore
{
public:
	const Rva00427157 *getDefault();
};

extern LivingWorldAutoResolveArmorStore *g_00E031F0;

class Rva0033A9A5
{
public:
	const Rva00427157 *rva0033A9A5(const void *arg);

private:
	char m_pad[0x3EC];
	Rva0033A9A5Entry *m_begin;
	Rva0033A9A5Entry *m_end;
};

const Rva00427157 *Rva0033A9A5::rva0033A9A5(const void *arg)
{
	Rva0033A9A5Entry *begin = m_begin;
	Rva0033A9A5Entry *end = m_end;
	for (Rva0033A9A5Entry *p = begin; p != end; p = (Rva0033A9A5Entry *)((char *)p + 0x104)) {
		if (((const Rva0033A8D9 *)p)->rva0033A8D9(arg))
			return p->armor;
	}
	return g_00E031F0->getDefault();
}
