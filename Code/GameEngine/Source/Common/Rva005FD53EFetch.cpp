// cl: /MD /EHsc
// ?Rva005FD53EGet@@YA?AVUnicodeString@@HH@Z @0x005FD53E (150B): ArmyUnitSwapperCP fetch+format twin of 0x005D38C8.
// TheGameText fetch slot 0x3C with null exists; fmt via +8-or-empty at 0x007BB5C4; UnicodeString format
// 0x006CB5D0; releaseBuffer 0x00036E70; copy ctor 0x00037050; b>0 guard; caller 0x005FD916.
// Evidence: same label STRATEGICHUD:ArmyUnitSwapperCP; neighbours 0x005FD4FF/0x005FD788.
typedef unsigned short wchar_t;
typedef bool Bool;

template <typename T> class StringBase;
class UnicodeString;
UnicodeString Rva005FD53EGet(int a, int b);

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend UnicodeString Rva005FD53EGet(int, int);

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
	friend UnicodeString Rva005FD53EGet(int, int);
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

UnicodeString Rva005FD53EGet(int a, int b)
{
	UnicodeString tmp;
	if (b > 0) {
		UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:ArmyUnitSwapperCP", 0);
		const wchar_t *fmt = fetched.m_data.m_data ? fetched.m_data.m_data->data : L"";
		tmp.format(fmt, a, b);
	}
	return tmp;
}
