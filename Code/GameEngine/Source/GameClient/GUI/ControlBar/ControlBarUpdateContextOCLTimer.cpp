// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ControlBar::updateContextOCLTimer, retail 0x0053E2B6 (148 bytes):
// ?updateContextOCLTimer@ControlBar@@IAEXXZ
// Identity (target): WorldBuilder's debug ControlBarOCLTimer.cpp
// ControlBar::updateContextOCLTimer looks up "OCLUpdate" once and calls
// Object::findModule, the OCL update's remaining-frames and countdown
// queries and ControlBar::updateOCLTimerTextDisplay (WB-named, 0x0053E17E),
// as retail does.
// Donor (Zero Hour ControlBar::updateContextOCLTimer): refresh the timer
// text when the remaining whole seconds differ from the ones shown (+0x7C).
// BFME 2 delta (target): nothing when the selected drawable (+0x6C) has no
// object (Drawable +0xFC). Seconds divide by the logic frame rate global.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

extern const unsigned int g_00DBA4E4; // logic frames per second

class Module;

class OCLUpdate
{
public:
	unsigned int getRemainingFrames();
	float getCountdownPercent();
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }

private:
	unsigned char m_pad000[0xFC];
	Object *m_object; // +0xFC
};

class GameWindow
{
public:
	unsigned int winSetStatus(unsigned int status);
};

class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void rva0031B641(GameWindow *window, const CommandButton *button);
	void rva0053E34A(int status);

protected:
	void updateContextOCLTimer();
	void updateOCLTimerTextDisplay(unsigned int totalSeconds, float percent);

private:
	unsigned char m_pad00[0x64];
	GameWindow *m_contextOCLTimerParent; // +0x64, field identity unknown
	unsigned char m_pad68[0x6C - 0x68];
	Drawable *m_currentSelectedDrawable; // +0x6C
	unsigned char m_pad70[0x7C - 0x70];
	unsigned int m_displayedOCLTimerSeconds; // +0x7C
};

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
};

extern GameWindowManager *TheWindowManager;

struct Gen_003bcb40
{
	void m(int value);
};

void ControlBar::updateContextOCLTimer()
{
	Object *obj = m_currentSelectedDrawable->getObject();
	if (!obj)
		return;
	static const NameKeyType key_OCLUpdate = TheNameKeyGenerator->nameToKey("OCLUpdate");
	OCLUpdate *update = (OCLUpdate *)obj->findModule(key_OCLUpdate);
	unsigned int frames = update->getRemainingFrames();
	unsigned int seconds = frames / g_00DBA4E4;
	float percent = update->getCountdownPercent();
	// if the time has changed since what was last shown to the user update the text
	if (m_displayedOCLTimerSeconds != seconds)
		updateOCLTimerTextDisplay(seconds, percent);
}

// ?rva0053E34A@ControlBar@@QAEXH@Z
// Target evidence: arg 0 skips the body; this+0x64 and the strings
// "Command_Sell" and "ControlBar.wnd:OCLTimerSellButton" feed the rowed
// findCommandButton, NameKeyGenerator and WindowManager paths. The returned
// window and button are passed to address-derived helper 0x0031B641; the body
// sets status 0x00200000, calls updateContextOCLTimer, then forwards the arg
// to the rowed empty ret-4 body 0x0047A69C. The ControlBar association is
// structural, from neighboring matched methods and the call relationships.
void ControlBar::rva0053E34A(int status)
{
	if (status == 0)
		return;
	GameWindow *parent = m_contextOCLTimerParent;
	const CommandButton *button;
	{
		AsciiString name("Command_Sell");
		button = findCommandButton(name);
	}
	NameKeyType key = TheNameKeyGenerator->nameToKey(
		"ControlBar.wnd:OCLTimerSellButton");
	GameWindow *sellButton = TheWindowManager->winGetWindowFromId(parent, key);
	rva0031B641(sellButton, button);
	sellButton->winSetStatus(0x00200000);
	updateContextOCLTimer();
	((Gen_003bcb40 *)this)->m(status);
}
