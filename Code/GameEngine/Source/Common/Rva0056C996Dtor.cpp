// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX
// ??1Rva0056C996@@QAE@XZ @ 0x0056C996 155B.
// Dtor: frees 5 DisplayStrings at +0x1c..+0x2c via TheDisplayStringManager
// slot 0x3c, then 4 wide strings at +0x4..+0x10 via rowed releaseBuffer
// 0x00036E70 with EH states 3..0. No vptr store: non-virtual.
// Evidence: callees 0x00629188 0x00036E70 rows callers 0x0056D2D0 0x0056D3EF
// deleting dtor and 0x0056D3E3 free wrapper prev/next flags.
class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void freeDisplayString(DisplayString *string);
};

extern DisplayStringManager *TheDisplayStringManager;

#include "unicode_string.h"


class Rva0056C996
{
public:
	~Rva0056C996();
private:
	char m_pad0[4];
	UnicodeString m_s0;
	UnicodeString m_s1;
	UnicodeString m_s2;
	UnicodeString m_s3;
	char m_pad14[8];
	DisplayString *m_d0;
	DisplayString *m_d1;
	DisplayString *m_d2;
	DisplayString *m_d3;
	DisplayString *m_d4;
};

Rva0056C996::~Rva0056C996()
{
	TheDisplayStringManager->freeDisplayString(m_d0);
	TheDisplayStringManager->freeDisplayString(m_d1);
	TheDisplayStringManager->freeDisplayString(m_d2);
	TheDisplayStringManager->freeDisplayString(m_d3);
	TheDisplayStringManager->freeDisplayString(m_d4);
}
