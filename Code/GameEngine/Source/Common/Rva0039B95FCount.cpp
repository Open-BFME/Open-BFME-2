// cl: /DNDEBUG /MD /EHsc
// ?Rva0039B95FCount@@YGHPAH@Z @0x0039B95F 114B count flags over Rva004266A1 vector.
// Outer null-checked global at 0x00E031E8 (+0x10 object), inner size from
// [obj+8]-[obj+4]>>3, triple getter filter flag1/flag0/flag2 with two counters.
// Evidence: callees rowed 0x42680D flag1 0x4269F7 flag0 0x4268F6 flag2;
// callers 0x39BB0A/0x39BC85; ret 4 proves one int* out param.

class Rva004266A1
{
public:
	unsigned char rva0042680D(int index);
	unsigned char rva004269F7(int index);
	unsigned char rva004268F6(int index);
	char m_pad00[4];
	int m_begin;
	int m_end;
};

struct Rva0039B95FHolder
{
	char m_pad00[0x10];
	Rva004266A1 *m_obj;
};

extern Rva0039B95FHolder *g_00E031E8;
// g_00E031E8: matched references place it at VA 0xe031e8 (zero-filled .bss).
Rva0039B95FHolder * g_00E031E8;

int __stdcall Rva0039B95FCount(int *outFirst)
{
	int countThree = 0;
	int countTwo = 0;
	Rva0039B95FHolder *holder = g_00E031E8;
	if (holder != 0)
	{
		Rva004266A1 *obj = holder->m_obj;
		if (obj != 0)
		{
			int total = (obj->m_end - obj->m_begin) >> 3;
			for (int i = 0; i < total; ++i)
			{
				if (!obj->rva0042680D(i))
					continue;
				if (!obj->rva004269F7(i))
					continue;
				++countTwo;
				if (!obj->rva004268F6(i))
					continue;
				++countThree;
			}
		}
	}
	if (outFirst != 0)
		*outFirst = countTwo;
	return countThree;
}
