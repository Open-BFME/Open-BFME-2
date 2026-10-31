// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies with no caller and no table reference (out-of-line
// copies of inline members), found by their instruction skeletons matching
// rowed bodies. Owners are not recovered: each keeps an address-derived
// name and a view of only the members it touches.

// --- 0x0042665E (9B): raise the byte at +5 and clear the one at +6; the
// shape of GameInfo::endGame 0x003FF296.
class Rva0042665E
{
public:
	void rva0042665E();

private:
	char m_pad00[5];
	bool m_05;
	bool m_06;
};

void Rva0042665E::rva0042665E()
{
	m_05 = true;
	m_06 = false;
}

// --- 0x004F5FCF (9B): zero the float at +0xC; the shape of
// Rva00094BA0Float::zero 0x00094BA0 (SSE zero store).
class Rva004F5FCF
{
public:
	void zero();

private:
	char m_pad00[0xC];
	float m_0C;
};

void Rva004F5FCF::zero()
{
	m_0C = 0.0f;
}

// --- 0x003BA655 (10B): store the bool argument at +0x4A (ret 4); the shape
// of DockUpdate::setDockCrippled 0x00589661.
class Rva003BA655
{
public:
	void set(bool value);

private:
	char m_pad00[0x4A];
	bool m_4A;
};

void Rva003BA655::set(bool value)
{
	m_4A = value;
}

// --- 0x0047B9A6 (7B): return the float at +0x354 (x87 return, fld).
class Rva0047B9A6
{
public:
	float get() const;
private:
	char m_pad00[0x354];
	float m_354;
};

float Rva0047B9A6::get() const
{
	return m_354;
}

// --- 0x004F032A (10B): whether the int at +0x10 is below the one at +0x14.
class Rva004F032A
{
public:
	bool isBelow() const;
private:
	char m_pad00[0x10];
	int m_10;
	int m_14;
};

bool Rva004F032A::isBelow() const
{
	return m_10 < m_14 ? true : false;
}

// --- 0x00481BAB (7B): invert the word the argument points at.
void invertWord(unsigned int *value)
{
	*value = ~*value;
}

// --- 0x003FDD25: return the float at +0x5C.
class Rva003FDD25
{
public:
	float get() const;
private:
	char m_pad00[0x5C];
	float m_5C;
};

float Rva003FDD25::get() const
{
	return m_5C;
}

// --- 0x0041F27F: return the float at +0x170.
class Rva0041F27F
{
public:
	float get() const;
private:
	char m_pad00[0x170];
	float m_170;
};

float Rva0041F27F::get() const
{
	return m_170;
}

// --- 0x00403129: return the flag byte at +0xD2.
class Rva00403129
{
public:
	bool get() const;
private:
	char m_pad00[0xD2];
	bool m_D2;
};

bool Rva00403129::get() const
{
	return m_D2;
}

// --- 0x0042CAE4: return the flag byte at +0x8C4.
class Rva0042CAE4
{
public:
	bool get() const;
private:
	char m_pad00[0x8C4];
	bool m_8C4;
};

bool Rva0042CAE4::get() const
{
	return m_8C4;
}

// --- 0x0040FB36 (7B): the address of the member at +0x270.
class Rva0040FB36
{
public:
	void *get();
private:
	char m_pad00[0x270];
	int m_270;
};

void *Rva0040FB36::get()
{
	return &m_270;
}

// --- 0x0036CB70 (7B): pre-increment the counter at +0x1C and return it.
class Rva0036CB70
{
public:
	int next();
private:
	char m_pad00[0x1C];
	int m_1C;
};

int Rva0036CB70::next()
{
	return ++m_1C;
}

// --- 0x00355138 (9B): follow +4, then +0, and return the word at +8.
struct Rva00355138Inner { char m_pad00[8]; int m_08; };
struct Rva00355138Mid { Rva00355138Inner *m_00; };
class Rva00355138
{
public:
	int get() const;
private:
	int m_00;
	Rva00355138Mid *m_04;
};

int Rva00355138::get() const
{
	return m_04->m_00->m_08;
}

// --- 0x00388C98 / 0x00388CA0 (8B each): the address of the argument's
// +0xC / +0x10 member (cdecl).
struct Rva00388C98Record { char m_pad00[0xC]; int m_0C; int m_10; };

int *Rva00388C98Field(Rva00388C98Record *record)
{
	return &record->m_0C;
}

int *Rva00388CA0Field(Rva00388C98Record *record)
{
	return &record->m_10;
}

// --- 0x00419CAF (3B): invert the word at +0.
class Rva00419CAF
{
public:
	void invert();
private:
	unsigned int m_00;
};

void Rva00419CAF::invert()
{
	m_00 = ~m_00;
}
