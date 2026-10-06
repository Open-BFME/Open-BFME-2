// cl: /MD /EHsc
// ?Rva00579900Get@@YA?AVUnicodeString@@H@Z retail 0x00579900 149B
// Evidence: unlock; TheGameText fetch slot 0x3C STRATEGICHUD:StatsBonus; UnicodeString format 0x006CB5D0; releaseBuffer 0x00036E70; copy ctor 0x00037050; callers 0x00579D3D 0x00579E82; precedent Rva005D38C8Fetch.cpp single-int
typedef unsigned short wchar_t;
typedef bool Bool;

template <typename T> class StringBase;
class UnicodeString;
UnicodeString Rva00579900Get(int a);
UnicodeString Rva00579868Get(int a, int b);
UnicodeString Rva00579995Get(float v);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend UnicodeString Rva00579900Get(int);
	friend UnicodeString Rva00579868Get(int, int);
	friend UnicodeString Rva00579995Get(float);

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

class UnicodeString
{
	friend UnicodeString Rva00579900Get(int);
	friend UnicodeString Rva00579868Get(int, int);
	friend UnicodeString Rva00579995Get(float);
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &that) : m_data(that.m_data) {}
	~UnicodeString() {}
	void __cdecl format(const wchar_t *fmt, ...);
private:
	StringBase<wchar_t> m_data;
};

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
	virtual UnicodeString fetch(const class AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;
extern unsigned short g_Va007BB5C4;

UnicodeString Rva00579900Get(int a)
{
	UnicodeString tmp;
	Bool exists;
	UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:StatsBonus", &exists);
	if (exists) {
		const wchar_t *fmt = fetched.m_data.m_data ? fetched.m_data.m_data->data : (const wchar_t *)&g_Va007BB5C4;
		tmp.format(fmt, a);
	}
	return tmp;
}

UnicodeString Rva00579868Get(int a, int b)
{
	UnicodeString tmp;
	Bool exists;
	UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:StatsCommandPoints", &exists);
	if (exists) {
		const wchar_t *fmt = fetched.m_data.m_data ? fetched.m_data.m_data->data : (const wchar_t *)&g_Va007BB5C4;
		tmp.format(fmt, a, b);
	}
	return tmp;
}

UnicodeString Rva00579995Get(float v)
{
	UnicodeString tmp;
	Bool exists;
	UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:StatsResourceMultiplier", &exists);
	if (exists) {
		const wchar_t *fmt = fetched.m_data.m_data ? fetched.m_data.m_data->data : (const wchar_t *)&g_Va007BB5C4;
		tmp.format(fmt, v);
	}
	return tmp;
}

// ?g_Va007BB5C4@@3GA: matched references place it at VA 0xbbb5c4; also referenced as ?g_bfmeLit1042@@3PADA.
unsigned short g_Va007BB5C4 = 0u;
#pragma comment(linker, "/alternatename:?g_bfmeLit1042@@3PADA=?g_Va007BB5C4@@3GA")
