// cl: /DNDEBUG /MD
// ?rva004FC8D6@Rva004FC8D6@@QAE_NPAVRva002E1001@@@Z @0x004FC8D6 (71B).
// Evidence: rowed rva002104B6 0x002104B6 plus rowed rva002E1001 0x002E1001
// plus g_009FEF10; caller 0x004FD5F0; prev 0x004FC563 next 0x004FC957;
// unlocks 0x004FD5C7.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002104B6
{
public:
	void *rva002104B6(void *a1);
};

class Rva002E1001
{
public:
	int rva002E1001();
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x2c - 0x18];
};

class Rva002BA8F1Logic
{
public:
	char m_pad00[0xb0];
	Rva002104B6 *m_b0;
};

class Rva004FC8D6
{
public:
	bool rva004FC8D6(Rva002E1001 *arg);
private:
	char m_pad00[0x10];
	int m_10;
	bool m_14;
};

// ?rva004FC8D6@Rva004FC8D6@@QAE_NPAVRva002E1001@@@Z
bool Rva004FC8D6::rva004FC8D6(Rva002E1001 *arg)
{
	if (m_14 != 0)
	{
		Rva002104B6 *t = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b0;
		void *q = (void *)((char *)arg + 0x2c);
		void *p = t->rva002104B6(q);
		if (p != 0)
		{
			if (*(int *)((char *)p + 0x13c) != arg->m_14)
				return true;
		}
	}
	bool ok = arg->rva002E1001() <= m_10;
	return ok;
}
