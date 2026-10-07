// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020E89C@Rva0020E89C@@QAE?AVUnicodeString@@XZ @0x0020E89C 63B
// Honest-address method returning the translated label at this+0x38:
// empty AsciiString returns UnicodeString::TheEmptyString (data 0x00A0C898
// via rowed wide copy 0x00037050) else TheGameText->fetch Ascii overload at
// slot 0x38 (char overload at 0x3C per VersionUnicode/DownloadManager precedent,
// reverse-order virtuals). Callees isEmpty 0x00001E2F rowed. Callers include
// LivingWorld hero cutoff 0x002BA235 and wrapper 0x005C95EC.

typedef unsigned short wchar_t;
typedef bool Bool;

#include "ascii_string.h"


#include "unicode_string.h"

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

class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();

private:
	char m_pad[0x38];
	AsciiString m_label;
};

UnicodeString Rva0020E89C::rva0020E89C()
{
	if (m_label.isEmpty())
		return UnicodeString::TheEmptyString;
	return TheGameText->fetch(m_label);
}

// ?Rva005C95ECGet@@YA?AVUnicodeString@@PAVRva0020E89C@@@Z @0x005C95EC 24B
// Chain wrapper forwarding hidden return to Rva0020E89C::rva0020E89C.
// Callers at 0x005D1806/0x005D1C18/0x005D220F pass out temp and obj.

UnicodeString Rva005C95ECGet(Rva0020E89C *obj)
{
	return obj->rva0020E89C();
}

// ?Rva005C95CAGet@@YA?AVUnicodeString@@XZ @0x005C95CA 34B
// Free fetch of STRATEGICHUD:BuildPlotName via TheGameText slot 0x3C.
// Callers at 0x0056BC86 and 0x005E24A9 pass hidden temp.

UnicodeString Rva005C95CAGet()
{
	return TheGameText->fetch("STRATEGICHUD:BuildPlotName");
}

// Native 003F0403..003F0442, RET4 consumes the hidden result pointer.
// The same translated-label ABI as rva0020E89C is independently visible:
// isEmpty at 1E2F, empty wide-string copy at 37050 and GameText slot38.
// The label is at +0x3C. Receiver and original method name remain opaque.
class Rva003F0403
{
public:
    UnicodeString rva003F0403();
private:
    char unknown00[0x3C];
    AsciiString label;
};
UnicodeString Rva003F0403::rva003F0403()
{
    if (label.isEmpty()) return UnicodeString::TheEmptyString;
    return TheGameText->fetch(label);
}
