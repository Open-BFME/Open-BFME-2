// cl: /MD /EHsc
// ?Rva005EF096Set@@YAXHPAURva005EF096Outer@@HH@Z retail 0x005EF096 207B
// Evidence: TheGameText fetch slot 0x3C STRATEGICHUD:StatsCommandPoints; Unicode format 0x006CB5D0 with +8-or-NullChr; Ascii format APT:_level%u.%s_CommandPoints; bfmeSetText pin 0x00225301; globals 0x009FF0BC 0x009FE4CC 0x007BAC1C 0x007BB5C4; callers 0x005EF2DD 0x005EFADE; precedent Rva005D38C8Fetch.cpp plus Rva005FDF1CApt.cpp
typedef unsigned short wchar_t;
typedef bool Bool;

template <typename T> class StringBase;
class UnicodeString;
class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend void __cdecl Rva005EF096Set(int, struct Rva005EF096Outer *, int, int);

	StringBase(const StringBase<T> &that);
	void releaseBuffer();

public:
	StringBase() { m_data = 0; }
	~StringBase() { releaseBuffer(); }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class UnicodeString
{
	friend void __cdecl Rva005EF096Set(int, struct Rva005EF096Outer *, int, int);
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &that) : m_data(that.m_data) {}
	~UnicodeString() {}
	void __cdecl format(const wchar_t *fmt, ...);
private:
	StringBase<wchar_t> m_data;
};

class AsciiString
{
	friend void __cdecl Rva005EF096Set(int, struct Rva005EF096Outer *, int, int);
public:
	AsciiString() {}
	~AsciiString() {}
	void __cdecl format(const char *fmt, ...);
private:
	StringBase<char> m_data;
};

struct Rva005EF096Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005EF096Outer
{
	Rva005EF096Inner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void __cdecl Rva005EF096Set(int level, Rva005EF096Outer *outer, int a, int b)
{
	UnicodeString tmp;
	Bool exists;
	UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:StatsCommandPoints", &exists);
	if (exists)
	{
		const wchar_t *fmt = fetched.m_data.m_data ? fetched.m_data.m_data->data : L"";
		tmp.format(fmt, a, b);
	}
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_CommandPoints", level, mid);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, tmp, true);
}
