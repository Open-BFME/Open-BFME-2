// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva003C549DDo@@YGXVAsciiString@@ABV1@@Z @0x003C549D 152B
// Byte twin of Rva003C5405Do (ScriptActions_garrison.cpp, same evidence) with the
// countdown flag set: the timer's internal name is the script-resolved name
// (resolveName 0x002046C0) plus '/' plus the timer name, the label is fetched
// through TheGameText slot 0x38, and InGameUI::addNamedTimer 0x002A5A50 adds a
// countdown timer.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &s);
};

class GameTextInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0); // slot 0x38
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
	void addNamedTimer(const AsciiString &timerName, const UnicodeString &text, bool isCountdown);
};
extern InGameUI *TheInGameUI;

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C549DDo(AsciiString timerName, const AsciiString &label)
{
	AsciiString tmp = ((Rva002046C0Owner *)TheScriptEngine)->resolveName(timerName);
	tmp += '/';
	tmp += timerName;
	TheInGameUI->addNamedTimer(tmp, TheGameText->fetch(label), true);
}
