// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva003F83B5@Rva003F83B5@@QAE?AVUnicodeString@@XZ, retail 0x003F83B5, 36 bytes.
// Fetches UnicodeString via TheGameText slot 0x38 from AsciiString at
// +0x18. GameTextInterface declaration copied verbatim from
// DownloadManagerOnStatusUpdate.cpp (AsciiString overload at 0x38 via
// reverse virtual order). Callers at 0x003F84C2 0x00520B4F 0x005CB6AF.
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
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class Rva003F83B5
{
public:
	UnicodeString rva003F83B5();
private:
	char m_pad00[0x18];
	AsciiString m_str18;
};

UnicodeString Rva003F83B5::rva003F83B5()
{
	return TheGameText->fetch(m_str18);
}
