// cl: /DNDEBUG /MD /GX-
// ?rva003F11EC@Rva003F11EC@@QAEHPAVCreateAHeroData@@@Z, retail 0x003F11EC, 70 bytes.
class CreateAHeroData;

class Rva003F0DA5
{
public:
	bool rva003F0DA5(CreateAHeroData *val);
private:
	CreateAHeroData **m_first;
	CreateAHeroData **m_last;
};

struct Rva003F11ECHolder
{
	Rva003F0DA5 m_range;
	char m_pad8[4];
	int m_value;
};

struct Rva003F11ECElem8
{
	int m_a;
	int m_b;
};

struct Rva003F11ECVec8
{
	Rva003F11ECElem8 *begin;
	Rva003F11ECElem8 *end;
};

class Rva003F11EC
{
public:
	int rva003F11EC(CreateAHeroData *val);
private:
	char m_pad[0xE8];
	Rva003F11ECVec8 m_vecE8;
	char m_padF0[0xFC - 0xF0];
	Rva003F11ECHolder **m_beginFC;
	Rva003F11ECHolder **m_end100;
};

int Rva003F11EC::rva003F11EC(CreateAHeroData *val)
{
	Rva003F11ECHolder **p = m_beginFC;
	Rva003F11ECHolder **end = m_end100;
	for (; p != end; ++p) {
		Rva003F11ECHolder *h = *p;
		if (((Rva003F0DA5 *)h)->rva003F0DA5(val))
			return h->m_value;
	}
	Rva003F11ECVec8 *v = &m_vecE8;
	return v->end - v->begin;
}
