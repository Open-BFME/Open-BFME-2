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
	Rva003F11ECHolder **it = m_beginFC;
	Rva003F11ECHolder **end = m_end100;
	for (; it != end; ++it) {
		Rva003F11ECHolder *holder = *it;
		if (((Rva003F0DA5 *)holder)->rva003F0DA5(val))
			return holder->m_value;
	}
	Rva003F11ECVec8 *vec = &m_vecE8;
	return vec->end - vec->begin;
}

// ?rva003F1AB1@Rva003F1AB1Owner@@QAEHPAVCreateAHeroData@@@Z @0x003F1AB1 8B: offsets this to the Rva003F11EC embedded at +0x14 and
// tail-jumps Rva003F11EC::rva003F11EC. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva003F1AB1Owner
{
public:
	int rva003F1AB1(CreateAHeroData *val);
};

int Rva003F1AB1Owner::rva003F1AB1(CreateAHeroData *val)
{
	return ((Rva003F11EC *)((char *)this + 0x14))->rva003F11EC(val);
}
