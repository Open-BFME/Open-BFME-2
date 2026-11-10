// cl: /O1 /DNDEBUG /MD /EHs

// ??1Rva005C18F0@@UAE@XZ, RVA 0x005C18F0, 54B. Unlock lane: virtual dtor
// storing vtable 0x008743C4, destroying the member at +8 through rowed
// ??1ProfilePreferences@@UAE@XZ at 0x00535776 under EH state 0, then storing the
// base vtable 0x008743B8 with no base call (trivial inline base). Member
// size is a placeholder: nothing follows it so codegen is unaffected.
// Caller is its ??_G at 0x005C18D4. Flags copy Rva005C1A36Dtor.cpp.
class ProfilePreferences
{
public:
	virtual ~ProfilePreferences();
private:
	char m_pad[4];
};

class Rva005DDE01;
class UserPreferences;

// Retail table 0x008743B8: deleting destructor plus two pure slots.
class Rva005C1860
{
public:
	virtual ~Rva005C1860() {}
	virtual void slot1(Rva005DDE01 *table) = 0;
	virtual UserPreferences *slot2() = 0;
};

class Rva005C18F0 : public Rva005C1860
{
public:
	virtual ~Rva005C18F0();
	virtual void slot1(Rva005DDE01 *table);
	virtual UserPreferences *slot2();
private:
	char m_pad04[4];
	ProfilePreferences m_08;
};

inline Rva005C18F0::~Rva005C18F0()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva005C18F0DtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva005C18F0DtorInlineAnchor()
{
    static_cast<Rva005C18F0 *>(0)->Rva005C18F0::~Rva005C18F0();
}
#pragma inline_depth()

// ??1Rva005C1980@@UAE@XZ, RVA 0x005C1980, 54B. Unlock lane: same shape as the
// 0x005C18F0 dtor above (derived vtable 0x008743D0 here, same member at +8
// through rowed 0x00535776, same base vtable 0x008743B8). Caller is its ??_G
// at 0x005C1964.
class Rva005C1980 : public Rva005C1860
{
public:
	virtual ~Rva005C1980();
	virtual UserPreferences *slot2();
private:
	char m_pad04[4];
	ProfilePreferences m_08;
};

Rva005C1980::~Rva005C1980()
{
}
