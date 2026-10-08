// ?addText@CreditsManager@@QAEXVAsciiString@@@Z
// partial score=0.96 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// BFME1 clean donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f:
// game/GameEngine/Source/GameClient/CreditsGetUnicodeString.cpp, over ZH Credits.cpp.
// Retail 0x005B76AC..0x005B776E, 194 bytes, RET8 with hidden UnicodeString result.
// Named CreditsManager::addText (WB 0x01581450) calls this helper just as the
// reference addText does. The <BLANK> test, colon search, localization and
// literal translation establish the same helper purpose independently of bytes.
// BFME2's TheGameText at VA 0x00DFF0BC uses slot 14 and a const AsciiString
// reference here; the donor used slot 9 and a by-value parameter. Canonical
// BFME2 string headers preserve the actual one-pointer ABI and cleanup calls.

// stlport
#include <list>
#include <new>
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class CreditsLine {
public: CreditsLine() throw(); ~CreditsLine();
int m_style; UnicodeString m_text,m_secondText; bool m_useSecond,m_done;
void *m_displayString,*m_secondDisplayString; int x,y,m_height,m_color;
};
class CreditsManager {
public: void addText(AsciiString);
private: UnicodeString getUnicodeString(AsciiString);
char pad00[0x0C]; _STL::list<CreditsLine*> m_creditLineList; char pad10[0x20]; int m_currentStyle;
};

UnicodeString CreditsManager::getUnicodeString(AsciiString str)
{
	UnicodeString uStr;
	if (str.compare("<BLANK>") == 0)
		return UnicodeString::TheEmptyString;

	if (str.find(':'))
		uStr = TheGameText->fetch(str);
	else
		uStr.translate(str);

	return uStr;
}



void CreditsManager::addText(AsciiString text) {
 CreditsLine *cLine=new CreditsLine;
 switch (m_currentStyle) {
 case 0: case 1: case 2:
  cLine->m_text=getUnicodeString(text); cLine->m_style=m_currentStyle; m_creditLineList.push_back(cLine); break;
 case 3: {
  _STL::list<CreditsLine*>::reverse_iterator rIt=m_creditLineList.rbegin();
  CreditsLine *rcLine=*rIt;
  if (rIt==m_creditLineList.rend() || rcLine->m_style!=3 || (rcLine->m_style==3 && rcLine->m_done==true)) {
   cLine->m_text=getUnicodeString(text); cLine->m_style=3; cLine->m_useSecond=true; m_creditLineList.push_back(cLine);
  } else { rcLine->m_secondText=getUnicodeString(text); rcLine->m_done=true; delete cLine; }
  break;
 }
 default: delete cLine;
 }
}

