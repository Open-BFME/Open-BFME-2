// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// Target evidence: 0x005E755E is a 36-byte copy of the 0x001EB382 fetch
// wrapper. It reads TheGameText at VA 0x00DFF0BC, passes its member
// AsciiString label (this+0x0C) to virtual slot +0x38 with a null exists
// pointer, and returns the hidden UnicodeString result pointer. The containing
// class identity remains unproven.
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

class Rva005E755E
{
public:
	UnicodeString rva005e755e();

private:
	unsigned int m_unknown00[3];
	AsciiString m_label;
};

UnicodeString Rva005E755E::rva005e755e()
{
	return TheGameText->fetch(m_label);
}
