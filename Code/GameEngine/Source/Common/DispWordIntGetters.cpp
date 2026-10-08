// Word-int getters: eight-byte __thiscall members with one shape:
//
//     movzx eax,word ptr [ecx+<DISP>] / ret
//
// One word is read at a fixed displacement from `this`, zero-extended, and
// returned as an int. Unlike DispWordFieldGetters (which returns
// unsigned short via mov ax), these return int, so MSVC 7.1 emits movzx.
// Class names are address-derived (identity unrecoverable from 8 bytes);
// member names positional. No // cl: line (defaults match the shape).

class Rva0028A952WordIntField
{
public:
	int get() const;

private:
	char m_pad[0x5DE];
	unsigned short m_value; // +0x5DE
};

// ?get@Rva0028A952WordIntField@@QBEHXZ
int Rva0028A952WordIntField::get() const
{
	return m_value;
}

class Rva0006E185WordIntField
{
public:
	int get() const;

private:
	char m_pad[0x5E2];
	unsigned short m_value; // +0x5E2
};

// ?get@Rva0006E185WordIntField@@QBEHXZ
int Rva0006E185WordIntField::get() const
{
	return m_value;
}

class Rva0033A444WordIntField
{
public:
	int get() const;

private:
	char m_pad[0x5DA];
	unsigned short m_value; // +0x5DA
};

// ?get@Rva0033A444WordIntField@@QBEHXZ
int Rva0033A444WordIntField::get() const
{
	return m_value;
}

class Rva00391614WordIntField
{
public:
	int get() const;

private:
	char m_pad[0x5DC];
	unsigned short m_value; // +0x5DC
};

// ?get@Rva00391614WordIntField@@QBEHXZ
int Rva00391614WordIntField::get() const
{
	return m_value;
}

class Rva006E3C40WordIntField
{
public:
	int get() const;

private:
	char m_pad[0x02];
	unsigned short m_value; // +0x02
};

// ?get@Rva006E3C40WordIntField@@QBEHXZ
int Rva006E3C40WordIntField::get() const
{
	return m_value;
}

class Rva004CEEA1WordIntField
{
public:
	int get() const;

private:
	char m_pad[0x10];
	unsigned short m_value; // +0x10
};

// ?get@Rva004CEEA1WordIntField@@QBEHXZ
int Rva004CEEA1WordIntField::get() const
{
	return m_value;
}

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 donor
// game/GameEngine/Source/Common/SignedFieldAccessor00191450.cpp supplies the
// signed-short to int expression under /O1 /arch:SSE /G7 (also exact /O2).
// Retail independently proves MOVSX from word[ecx+0x18], EAX return and the
// complete 0x003297C4..0x003297C9 leaf after RET4 at 0x003297C1 and before
// the following constructor. Original receiver and field purpose are unknown.
class Rva003297C4SignedWordIntField
{
public:
    int get() const;
private:
    char m_pad[0x18];
    short m_value;
};

int Rva003297C4SignedWordIntField::get() const
{
    return m_value;
}
