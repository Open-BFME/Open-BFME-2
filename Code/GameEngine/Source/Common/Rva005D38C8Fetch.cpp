// cl: /MD /EHsc
// StrategicHUD::FormatCommandPointsString retail 0x005D38C8 158B and
// StrategicHUD::SetCommandPointsString retail 0x005D3966 132B: WorldBuilder
// names both (StrategicHUDSelectionUIImpl.cpp; SetCommandPointsString assert
// line 52, the _CP key). The clip name stays the opaque holder this unit
// already models.
// Evidence: unlock; TheGameText fetch slot 0x3C STRATEGICHUD:ArmyUnitSwapperCP; UnicodeString format 0x006CB5D0; releaseBuffer 0x00036E70; copy ctor 0x00037050; caller 0x005D3966
typedef unsigned short wchar_t;
typedef bool Bool;

template <typename T> class StringBase;
class UnicodeString;
struct Rva005D2FD0Outer;
namespace StrategicHUD
{
	UnicodeString FormatCommandPointsString(int a, int b);
	void SetCommandPointsString(int level, Rva005D2FD0Outer *outer, int a, int b);
}

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend UnicodeString StrategicHUD::FormatCommandPointsString(int, int);

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
	friend UnicodeString StrategicHUD::FormatCommandPointsString(int, int);
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
public:
	AsciiString() {}
	~AsciiString() {}
	void __cdecl format(const char *fmt, ...);
private:
	StringBase<char> m_data;
};

struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005D2FD0Outer
{
	Rva005D2FD0Inner *m_ptr;
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

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

UnicodeString StrategicHUD::FormatCommandPointsString(int a, int b)
{
	UnicodeString tmp;
	if (b >= 0) {
		Bool exists;
		UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:ArmyUnitSwapperCP", &exists);
		if (exists) {
			const wchar_t *fmt = fetched.m_data.m_data ? fetched.m_data.m_data->data : L"";
			tmp.format(fmt, a, b);
		}
	}
	return tmp;
}

// StrategicHUD::SetCommandPointsString retail 0x005D3966 132B
// Evidence: chain from 0x005D38C8; APT:_level%u.%s_CP via 0x00038150; bfmeSetText pin 0x00225301; release wide 0x00036E70 ansi 0x00036410; callers 0x005D3A0A 0x005D3F46
void StrategicHUD::SetCommandPointsString(int level, Rva005D2FD0Outer *outer, int a, int b)
{
	AsciiString key;
	const char *mid = outer->m_ptr ? outer->m_ptr->m_name : "";
	key.format("APT:_level%u.%s_CP", level, mid);
	g_bfmeAptWindowManager->bfmeSetText(key, FormatCommandPointsString(a, b), true);
}
