// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (second
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

// --- 0x00367E31 / 0x00545393 (40B each): a vtable (0x00C17640 / 0x00C69F34)
// over two cleared words (+0x04, +0x18) and four zero floats (+0x08..+0x14).
class Rva00367E31
{
public:
	Rva00367E31();
	virtual ~Rva00367E31() {}
private:
	int m_04;
	float m_progressOverlayColor;
	float m_backButtonTooltip;
	float m_10;
	float m_14;
	int m_18;
};

Rva00367E31::Rva00367E31() : m_04(0), m_18(0)
{
	m_14 = 0.0f;
	m_progressOverlayColor = 0.0f;
	m_backButtonTooltip = 0.0f;
	m_10 = 0.0f;
}

class Rva00545393
{
public:
	Rva00545393();
	virtual ~Rva00545393() {}
private:
	int m_04;
	float m_progressOverlayColor;
	float m_backButtonTooltip;
	float m_10;
	float m_14;
	int m_18;
};

Rva00545393::Rva00545393() : m_04(0), m_18(0)
{
	m_14 = 0.0f;
	m_progressOverlayColor = 0.0f;
	m_backButtonTooltip = 0.0f;
	m_10 = 0.0f;
}

// --- 0x005E7026 (17B): clamp the second argument at zero and forward both to
// virtual slot 12; 0x005E7037 (18B): parse this from INI with the field
// table at VA 0x00C77E98; 0x005E7049 (5B): forward to the rowed 0x004E0625.
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
};

// Retail's field table at VA 0x00C77E98 (RVA 0x00877E98, .rdata, two records and the zero sentinel), transcribed from retail's bytes.
extern const FieldParse s_Rva005E7037FieldParse[] =
{
	{ "ProgressOverlayColor", INI::parseColorInt, 0, 0x8 },
	{ "BackButtonTooltip", INI::parseAsciiString, 0, 0xC },
	{ 0, 0, 0, 0 }
};

class Rva004E0625
{
public:
	int rva004E0625() const;								// 0x004E0625
};

class Rva005E7026
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12(int a, int b);

	void rva005E7026(int a, int b);
	void rva005E7037(INI *ini);
	int rva005E7049() const;
};

void Rva005E7026::rva005E7026(int a, int b)
{
	if (b <= 0)
		b = 0;
	s12(a, b);
}

void Rva005E7026::rva005E7037(INI *ini)
{
	ini->initFromINI(this, s_Rva005E7037FieldParse);
}

int Rva005E7026::rva005E7049() const
{
	return ((const Rva004E0625 *)this)->rva004E0625();
}

// --- 0x00428DC1 (41B, cdecl): when the player list's +0x10 player has a
// rowed 0x002ABCF0(1, 0) result, the tactical view takes its +0x38 point
// (virtual slot 21).
class Player
{
public:
	int rva002ABCF0(unsigned char a, int *b);				// 0x002ABCF0
};

class PlayerList;
extern PlayerList *ThePlayerList;
struct PlayerListView
{
	char m_pad[0x10];
	Player *m_10;
};

class View
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21(void *point);
};
extern View *TheTacticalView;

void Rva00428DC1()
{
	Player *player = ((PlayerListView *)ThePlayerList)->m_10;
	if (player)
	{
		int found = player->rva002ABCF0(1, 0);
		if (found)
			TheTacticalView->s21((char *)found + 0x38);
	}
}

// --- 0x00570405 / 0x0057041B / 0x00570455 / 0x00570469: this-returning
// forwarders of a referenced value to the class's rowed setters.
class Rva0056FCDB
{
public:
	void rva0056FCDB(short value);							// 0x0056FCDB
	Rva0056FCDB *rva00570405(const short &value);
};

class Rva0056FAA5
{
public:
	void rva0056FD14(int value);							// 0x0056FD14
	void rva0056FD2D(int value);							// 0x0056FD2D
	void rva0056FD46(short value);							// 0x0056FD46
	Rva0056FAA5 *rva0057041B(const int &value);
	Rva0056FAA5 *rva00570455(const int &value);
	Rva0056FAA5 *rva00570469(const short &value);
};

// --- 0x005C8774 (19B): +0x00 = 1.0f, +0x04 = 0; 0x005C8787 (23B): +0x00 and
// +0x04 cleared, +0x08 = 1.0f.
struct Rva005C8774
{
	Rva005C8774();
	float m_00;
	int m_04;
};

Rva005C8774::Rva005C8774() : m_00(1.0f), m_04(0)
{
}

struct Rva005C8787
{
	Rva005C8787();
	int m_00;
	int m_04;
	float m_progressOverlayColor;
};

Rva005C8787::Rva005C8787() : m_00(0), m_04(0), m_progressOverlayColor(1.0f)
{
}


template <class T> struct GapClassVector
{
	T *m_begin;
	T *m_end;
	T *m_storage;
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	T &operator[](unsigned int i) { return m_begin[i]; }
};

// --- 0x0021A18B (42B): bounds-checked dispatch into the +0x14C table of
// 32-byte CreateAHero classes (rowed 0x00219D3B), else 0.
class CreateAHeroManager
{
public:
	class CreateAHeroClass
	{
	public:
		int rva00219D3B(unsigned int value);				// 0x00219D3B
		char m_data[32];
	};
	int rva0021A18B(unsigned int index, unsigned int value);
private:
	char m_pad[0x14C];
	GapClassVector<CreateAHeroClass> m_classes;			// +0x14C
};

int CreateAHeroManager::rva0021A18B(unsigned int index, unsigned int value)
{
	if (index < m_classes.size())
		return m_classes[index].rva00219D3B(value);
	return 0;
}

// --- 0x002C902A (43B): five zero floats, then FLT_MAX at +0x14.
struct Rva002C902A
{
	Rva002C902A();
	float m_00;
	float m_04;
	float m_progressOverlayColor;
	float m_backButtonTooltip;
	float m_10;
	float m_14;
};

Rva002C902A::Rva002C902A() : m_00(0.0f), m_04(0.0f), m_progressOverlayColor(0.0f), m_backButtonTooltip(0.0f), m_10(0.0f), m_14(3.4028234663852886e+38f)
{
}

struct Rva0058C475Arg
{
	char m_pad[0x28];
	int m_28;
};
