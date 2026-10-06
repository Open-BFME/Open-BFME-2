// cl: /DNDEBUG /MD /EHsc
// ?rva00273648@Drawable@@QAEX PAX@Z @0x00273648 34B: Drawable module walk at +0x14c calling slot 0xEC; callers 0x00275F24 0x00275F33; unblocks 0x00275DCE.
class DrawModule00273648
{
public:
	virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0C();
	virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1C();
	virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2C();
	virtual void d30(); virtual void d34(); virtual void d38(); virtual void d3C();
	virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4C();
	virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5C();
	virtual void d60(); virtual void d64(); virtual void d68(); virtual void d6C();
	virtual void d70(); virtual void d74(); virtual void d78(); virtual void d7C();
	virtual void d80(); virtual void d84(); virtual void d88(); virtual void d8C();
	virtual void d90(); virtual void d94(); virtual void d98(); virtual void d9C();
	virtual void dA0(); virtual void dA4(); virtual void dA8(); virtual void dAC();
	virtual void dB0(); virtual void dB4(); virtual void dB8(); virtual void dBC();
	virtual void dC0(); virtual void dC4(); virtual void dC8(); virtual void dCC();
	virtual void dD0(); virtual void dD4(); virtual void dD8(); virtual void dDC();
	virtual void dE0(); virtual void dE4();
	virtual void slotE8(void* arg);
	virtual void slotEC(void* arg);
};

class Rva00270025
{
public:
	void rva0027006C(int v);
};

class Drawable
{
public:
	void rva00273648(void* arg);
	void rva00273686(void* arg);
	void rva002736A8();
	void rva0027366A();
private:
	unsigned char m_pad[0x14c];
	DrawModule00273648** m_mods;
	unsigned char m_pad2[0x354 - 0x150];
	Rva00270025* m_354;
};

void Drawable::rva00273648(void* arg)
{
	DrawModule00273648** mods = m_mods;
	while (*mods != 0) {
		(*mods)->slotEC(arg);
		++mods;
	}
}

void Drawable::rva00273686(void* arg)
{
	DrawModule00273648** mods = m_mods;
	while (*mods != 0) {
		(*mods)->slotE8(arg);
		++mods;
	}
}

void Drawable::rva002736A8()
{
	if (m_354 != 0)
		m_354->rva0027006C(10);
}

void Drawable::rva0027366A()
{
	DrawModule00273648** mods = m_mods;
	while (*mods != 0) {
		(*mods)->dE4();
		++mods;
	}
}
