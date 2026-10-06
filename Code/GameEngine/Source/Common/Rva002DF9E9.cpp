// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva002DF9E9@Rva002DF9E9@@QAE?AVUnicodeString@@XZ, retail 0x002DF9E9, 90 bytes.
// TheGameText fetch via slot 0x38 into UnicodeString temp at ebp-0x10 then
// StringBaseWide copy ctor 0x00037050 into hidden return plus release 0x00036E70.
// Label is this+0x20 as const char*, exists=0. Guard: EH prolog scopetable.
// Evidence: unlock lane, 3 callers, pin TheGameText 0x009FF0BC,
// precedent Rva005D38C8Fetch.cpp /O1 /EHsc slot 0x38 fetch plus wide copy/release.
// Private StringBase/UnicodeString copied verbatim from precedent (not shared
// header) because shared header lacks UnicodeString and emits ~UnicodeString
// call instead of retail direct releaseBuffer; gate decides.
typedef unsigned short wchar_t;
typedef bool Bool;
template <typename T> class StringBase;
class UnicodeString;
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
};
extern GameTextInterface *TheGameText;
class Rva002DF9E9
{
public:
	UnicodeString rva002DF9E9();
private:
	char m_pad0[0x20];
	char m_label[4];
};
UnicodeString Rva002DF9E9::rva002DF9E9()
{
	UnicodeString tmp = TheGameText->fetch(m_label, 0);
	return tmp;
}
