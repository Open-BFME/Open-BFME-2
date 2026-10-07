// ?rva003F05CE@Rva003F055A@@QAEHXZ
// partial score=0.1 date=2026-10-07
// cl: /DNDEBUG /MD /GX-
// ?rva003F055A@Rva003F055A@@QAEXXZ 0x003F055A 46B
// Scan pointer range at +0x170/+0x174 calling rowed 0x4E0845 on entry+0x20 when nonzero and byte at entry+0x34 is zero.
// Evidence: callee 0x4E0845 rowed; caller at 0x3F104B; same +0x170/+0x20/+0x34 shape as LivingWorldRegionConnection 0x3F287F vector.
class Rva004E0809
{
public:
	void rva004E0845(); // rowed 0x004E0845, declared only
};

struct Rva003F055AEntry
{
	char _pad0[0x20];
	class Rva004E0809 *m_item; // +0x20
	char _pad1[0x34 - 0x24];
	unsigned char m_flag; // +0x34
};

class Rva003F055A
{
public:
	void rva003F055A();
	void rva003F1044(int a, int b);
	int rva003F05CE();
private:
	__forceinline unsigned int rva003F05CECount() const
	{
		Rva003F055AEntry **finish = m_end;
		return static_cast<unsigned int>(finish - m_begin);
	}
	unsigned char m_pad[0x170];
	struct Rva003F055AEntry **volatile m_begin; // +0x170
	struct Rva003F055AEntry **volatile m_end; // +0x174
};

void Rva003F055A::rva003F055A()
{
	for (struct Rva003F055AEntry **p = m_begin; p != m_end; ++p) {
		struct Rva003F055AEntry *e = *p;
		class Rva004E0809 *item = e->m_item;
		if (item != 0 && e->m_flag == 0)
			item->rva004E0845();
	}
}

// ?rva003F1044@Rva003F055A@@QAEXHH@Z 0x003F1044 15B
// Checks second stack arg at [esp+8]; when zero calls rowed 0x003F055A on same this (ecx pass-through).
// Evidence: callee rowed 0x003F055A; ret 8 with ecx preserved proves thiscall with 2 stack args.
void Rva003F055A::rva003F1044(int a, int b)
{
	if (b == 0)
		rva003F055A();
}

// Native 003F05CE..003F0614 (70 bytes) counts the same entry predicate.
// The pointer cursor is retained while both vector bounds are reread for
// every unsigned index comparison. Volatile describes those measured reads;
// it is a compiler view, not a claim about the original declarations.
int Rva003F055A::rva003F05CE()
{
	int count = 0;
	unsigned int index = 0;
	if (index < rva003F05CECount())
	{
		Rva003F055AEntry **cursor = m_begin;
		do
		{
			Rva003F055AEntry *entry = *cursor;
			if (entry->m_item != 0 && entry->m_flag == 0)
				++count;
			++index;
			++cursor;
		} while (index < rva003F05CECount());
	}
	return count;
}
