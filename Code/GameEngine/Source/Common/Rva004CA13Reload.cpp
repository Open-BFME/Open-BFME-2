// cl: /O1 /Oa /MD
//
// ?rva002CF172@Rva004CA13@@UAE_NPA_N@Z, retail 0x002CF172, 87 bytes.
// Virtual slot 4 (offset 0x10) of vtable 0x007C4858 (class of
// ??1Rva004CA13@@UAE@XZ) and of base vtable 0x0080233C (class of
// ??1Rva002D0588@@UAE@XZ, pinned SEH base); both tables share slots 1-13,
// only slot 0 differs, so the body belongs to the base family and is served
// here under the derived opaque name per the packet. Slot 2 (+8) is the
// shared 0x001B5384 Subsystem load gate; slot 5 (+0x14) is the 0x002CEF14
// flag clearer over the same 0x009FF005 byte this body sets and returns.
// Retail constructs a wide RIF string from 0x00802280
// (L"RIF: ThingTemplates (Objects, Units, etc) reloaded") and passes it by
// value to TheInGameUI->message at slot 0x40 (variadic __cdecl, this on
// stack; UnicodeString overload, cf. the narrow 0x3C overload used by
// InGameUI::displayCantBuildMessage 0x0029C291 which shows the same
// A1..8B08..50..FF51..59..59 shape). Twins: 0x001E51AC slot (RIF Locomotor,
// flags 0x009FDC60/61, extra TheInGameUI-null guard) and 0x00061C25 Audio
// path (RIF AudioEvents, flag 0x009E1E4C, same push-mov-call order).
// BSS flags: 0x009FEFFC (cleared on entry, sets *out) and 0x009FF005
// (set before the message, returned). /Oa (assume no aliasing) hoists the
// vtable load above the flag store to match retail load-mov-call; /O1 keeps
// the EBP frame.

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &that);
	StringBase(const T *s);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	void releaseBuffer();
	Header *m_data;
};

class UnicodeString
{
public:
	UnicodeString(const wchar_t *s) : m_data(s) {}
	~UnicodeString() { m_data.releaseBuffer(); }
private:
	StringBase<wchar_t> m_data;
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void message(UnicodeString format, ...);
};

extern InGameUI *TheInGameUI;
extern bool g_flag1;
extern bool g_flag2;

class Rva004CA13
{
public:
	virtual ~Rva004CA13();
	virtual void slot1();
	virtual bool slot2();
	virtual void slot3();
	virtual bool rva002CF172(bool *out);
};

bool Rva004CA13::rva002CF172(bool *out)
{
	g_flag1 = false;
	if (slot2()) {
		g_flag2 = true;
		TheInGameUI->message(UnicodeString(L"RIF: ThingTemplates (Objects, Units, etc) reloaded"));
	}
	if (g_flag1) {
		*out = true;
		g_flag1 = false;
	}
	return g_flag2;
}
