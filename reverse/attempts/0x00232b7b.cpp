// ?rva00232B7B@Keyboard@@QAEXXZ
// partial score=0.8 date=2026-10-08
// Stash: Keyboard::rva00232B7B (76 B), closest shape (nested loops, keys local).
// cl: /DNDEBUG /MD /EHsc
// ?rva00232B7B@Keyboard@@AAEXXZ 0x00232B7B 76B. Keyboard member: erase the key
// list at +0x10, then pump one 8-byte entry at a time from virtual slot 0x40.
// 0xFF rebuilds the list via rva00232AE8 and erases again; 0 ends the loop;
// any other entry is appended. Erase and push_back are the ICF-folded 8-byte
// vector bodies at 0x003FA4DB and 0x00539A2E, pinned under address-derived names.
struct Rva00232B7BEntry
{
	unsigned char m0;
	unsigned char m1;
	unsigned short m2;
	int m4;
};

struct Rva00232B7BKeys
{
	void *m_first;
	void *m_last;
	void *m_cap;
	void rva003FA4DB(void *first, void *last);
	void rva00539A2E(const Rva00232B7BEntry &e);
};

class Keyboard
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void slot3C();
	virtual void slot40(Rva00232B7BEntry *e);
	void rva00232B7B();
private:
	void rva00232AE8();
	unsigned char m_pad04[0x10 - 0x04];
	Rva00232B7BKeys m_keys;
};

void Keyboard::rva00232B7B()
{
	Rva00232B7BEntry e;
	Rva00232B7BKeys *keys = &m_keys;
	bool rebuild = false;
	for (;;)
	{
		if (rebuild)
			rva00232AE8();
		keys->rva003FA4DB(keys->m_first, keys->m_last);
		for (;;)
		{
			slot40(&e);
			if (e.m0 == 0xff)
			{
				rebuild = true;
				break;
			}
			if (e.m0 == 0)
				return;
			keys->rva00539A2E(e);
		}
	}
}
