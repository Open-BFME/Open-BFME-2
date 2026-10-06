// cl: /O1 /DNDEBUG /MD /EHsc
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

class ControlBar
{
protected:
	void updateContextOCLTimer();
	void updateOCLTimerTextDisplay(unsigned int totalSeconds, float percent);

private:
	unsigned char m_pad00[0x6C];
	Drawable *m_currentSelectedDrawable; // +0x6C
	unsigned char m_pad70[0x7C - 0x70];
	unsigned int m_displayedOCLTimerSeconds; // +0x7C
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
