// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005E3DE8@@QAE@XZ @0x005E3DE8 53B.
// Non-virtual dtor: inline AsciiString member at +8 torn down via releaseBuffer
// with EH state 0 then member at +0 destroyed via 0x0022167C. No vptr store.
// Evidence: unlock lane plus caller 0x005E3EF1 deleting dtor plus callee releaseBuffer 0x00036410 plus pin ??1Rva0022167C plus precedent Rva0057A4E7Dtor.
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class Rva0022167C
{
public:
	~Rva0022167C();
private:
	char m_bytes[8];
};

class Rva005E3DE8
{
public:
	~Rva005E3DE8();
	UnicodeString rva005E3E1D();
private:
	Rva0022167C m_at00;
	AsciiString m_at08;
};

Rva005E3DE8::~Rva005E3DE8()
{
}

// RVA 0x005E3E1D..0x005E3E41: return the translation of the AsciiString
// member already established by this destructor at +8. Target calls
// TheGameText (VA 0x00DFF0BC), virtual slot +0x38, with a null exists pointer
// and forwards the hidden UnicodeString result. The application type/name
// remain unknown; the GameText ABI agrees with INITranslatedLabelParse.cpp.
UnicodeString Rva005E3DE8::rva005E3E1D()
{
	return TheGameText->fetch(m_at08);
}
