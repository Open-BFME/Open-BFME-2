// ?rva00265173@Rva00265173@@QAEXXZ
// partial score=0.99 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
// ?rva00265173@Rva00265173@@QAEXXZ @0x00265173 225B
// Evidence: unlock lane, fade hide/show via rowed getDrawable fadeOut fadeIn Drawable toggles pinned bfmeAskBIC, caller 0x0026E40A, neighbours share flags.
// ?rva00265173@Rva00265173@@QAEXXZ present-unmatched
extern int g_Va00DBA4E4;

class Drawable
{
public:
	void fadeOut(unsigned int v);
	void fadeIn(unsigned int v);
	void rva00272A02(bool v);
	void rva00272BE7();
	void rva00272BAB(int a, int b);
	char _pad[0x43c];
	bool m_43c;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object
{
public:
	bool isLocallyControlled() const;
	char _pad[0x274];
	Thing *m_thing274;
};

class Rva001E3591
{
public:
	bool rva001E3591();
};

class BfmeSubBIC
{
public:
	int bfmeAskBIC();
};

class Rva00265173
{
public:
	void rva00265173();
private:
	char _pad0[0x8];
	Object *m_8;
	char _pad8[0x140 - 0xc];
	Rva001E3591 *m_140;
	char _pad140[0x3cb - 0x144];
	bool m_3cb;
};

void Rva00265173::rva00265173()
{
	bool flag = false;
	Drawable *saved = ((Thing *)m_8)->getDrawable();
	Drawable *volatile vsaved = saved;
	if (saved == 0)
		return;
	Drawable *d = saved;
	Thing *t2 = m_8->m_thing274;
	if (t2)
	{
		d = t2->getDrawable();
		if (d == 0)
			goto after_flag;
	}
	flag = d->m_43c != 0;
after_flag:;
	Rva001E3591 *p = m_140;
	if (p != 0 && p->rva001E3591() != false)
	{
		if (m_3cb)
			return;
		vsaved->fadeOut((unsigned int)g_Va00DBA4E4);
		vsaved->rva00272A02(false);
		m_3cb = true;
		if (!flag)
			return;
		if (!m_8->isLocallyControlled())
			return;
		vsaved->rva00272BE7();
	}
	else
	{
		if (!m_3cb)
			return;
		vsaved->fadeIn((unsigned int)g_Va00DBA4E4);
		vsaved->rva00272A02(true);
		m_3cb = false;
		if (!flag)
			return;
		if (!m_8->isLocallyControlled())
			return;
		int bic = ((BfmeSubBIC *)m_8)->bfmeAskBIC();
		vsaved->rva00272BAB(1, bic);
	}
}
