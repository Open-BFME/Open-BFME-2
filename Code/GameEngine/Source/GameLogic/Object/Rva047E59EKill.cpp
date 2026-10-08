// cl: /MD /DNDEBUG /EHsc
// ?rva047E59E@Rva047E59E@@QAEXXZ @0x0047E59E 54B: when the owner's +0x130 counter is set and
// the global table's +0x40 limit is not exceeded, kill the object at this-8 with (8, 6); then tail
// into the shared member 0x00468749 with this.
enum DamageType
{
	Rva047E59EDamage8 = 8
};

enum DeathType
{
	Rva047E59EDeath6 = 6
};

class Object
{
public:
	void kill(DamageType d, DeathType t);
};

extern void *g_00DFE78C;

class Rva047E59E
{
public:
	void rva047E59E();
	void rva00468749();

private:
	char m_pad00[0x130];
	int m_130;
};

// ?rva047E59E@Rva047E59E@@QAEXXZ @0x0047E59E
void Rva047E59E::rva047E59E()
{
	if (m_130 != 0)
	{
		char *far = *(char **)((char *)this - 0xC);
		int total = *(int *)(far + 0x278) + m_130;
		if ((unsigned int)total <= (unsigned int)*(int *)((char *)g_00DFE78C + 0x40))
		{
			Object *obj = *(Object **)((char *)this - 8);
			obj->kill(Rva047E59EDamage8, Rva047E59EDeath6);
		}
	}
	rva00468749();
}
