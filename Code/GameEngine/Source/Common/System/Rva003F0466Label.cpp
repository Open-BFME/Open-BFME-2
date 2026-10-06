// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003F0466@Rva003F0466@@QAE?AVUnicodeString@@XZ, retail 0x003F0466, 122 bytes.
// __thiscall UnicodeString getter via AsciiString at +0x124: returns TheEmptyString
// when empty else TheGameText virtual slot 0x38 fetch. Evidence: rowed StringBase<char>
// isEmpty 0x00001E2F, rowed StringBase<ushort> copy 0x00037050, rowed releaseBuffer
// 0x00036E70, globals TheGameText 0x00DFF0BC and UnicodeString::TheEmptyString
// 0x00A0C898, caller 0x005E2644, neighbours 0x003F0442 0x003F07E5.
// Note: the shared header's AsciiString::isEmpty is inline, but retail calls the
// rowed out-of-line StringBase<char>::isEmpty, so the check goes through a
// StringBase<char> reference (same one-pointer layout the header itself relies on).
#include "ascii_string.h"

#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class Rva003F0466
{
public:
	UnicodeString rva003F0466();
private:
	char m_pad[0x124];
	AsciiString m_label;
};

// 0x003F04E0 is the same getter via the AsciiString at +0x128 (caller 0x005E2644).

UnicodeString Rva003F0466::rva003F0466()
{
	return !((const StringBase<char> *)&m_label)->isEmpty() ? TheGameText->fetchLabel(m_label) : UnicodeString::TheEmptyString;
}

class Rva003F04E0
{
public:
	UnicodeString rva003F04E0();
private:
	char m_pad[0x128];
	AsciiString m_label;
};

UnicodeString Rva003F04E0::rva003F04E0()
{
	return !((const StringBase<char> *)&m_label)->isEmpty() ? TheGameText->fetchLabel(m_label) : UnicodeString::TheEmptyString;
}
