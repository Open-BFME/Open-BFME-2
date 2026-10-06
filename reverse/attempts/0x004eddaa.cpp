// ?rva004EDDAA@Rva004EDDAA@@QAEXXZ
// partial score=0.7 date=2026-10-06
// cl: /O1 /MD
//
// Two small dump-range bodies: 0x4ED3A2 conditionally refreshes a cursor
// through the pinned cdecl 0x5B09D8 then rewinds it, and 0x4EDDAA guards
// on the rowed 0x4ECF41, resolves a float through the pinned 0x4ECE93,
// and tail-calls the rowed 0x4EDA60 on negative. Retail 0x004ED3A2 47B,
// 0x004EDDAA 41B. Pins are honest address-derived candidates.

void __cdecl rva005B09D8(void *a, void *b, void *c, void *d);

class Rva004ED3A2
{
public:
	void *rva004ED3A2(void *arg);

private:
	char m_pad[4];
	char *m_04;
};

// ?rva004ED3A2@Rva004ED3A2@@QAEPAXPAX@Z @0x004ED3A2 47B.
void *Rva004ED3A2::rva004ED3A2(void *arg)
{
	char tmp;
	char *m = m_04;
	char *p = (char *)arg + 0x14;
	if (p != m)
		rva005B09D8(p, m, arg, &tmp);
	m_04 -= 20;
	return arg;
}

class Rva002E2903Player;

class Rva004E0705
{
public:
	Rva002E2903Player *rva004E0705();
};

class Rva004ECECD
{
public:
	bool rva004ECF41();
	void rva004EDA60();
};

class Rva004ECE93
{
public:
	float rva004ECE93(void *arg);
};

class Rva004EDDAA
{
public:
	void rva004EDDAA();

private:
	char m_pad[0x38];
	void *m_38;
};

// ?rva004EDDAA@Rva004EDDAA@@QAEXXZ @0x004EDDAA 41B.
void Rva004EDDAA::rva004EDDAA()
{
	if (((Rva004ECECD *)this)->rva004ECF41())
		return;
	float f = ((Rva004ECE93 *)this)->rva004ECE93(&m_38);
	if (0.0f <= f)
	{
		((Rva004ECECD *)this)->rva004EDA60();
		return;
	}
}
