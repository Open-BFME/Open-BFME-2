// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?InitGadgets@AptOptions@@QAEXPBDHPAVGameWindow@@@Z
// retail 0x00519E1E..0x0051A669 (2123 bytes) thiscall RET 0xC.
//
// The options screen's gadget binder: AptOptions' constructor registers it
// as the Apt command "AptOptions::InitGadgets" (the member pointer pushed at
// 0x0051AACB). The WorldBuilder twin 0x013D5870 (AptOptions.cpp lines
// 1059..1351) names it and has the same chain of strcmp tests: each named
// gadget is stored on the screen and filled from a temporary
// OptionPreferences - the resolution combo (+0x2AC) from the display modes
// and the "Resolution" key; the detail combo (+0x2B0) with its six presets;
// the five volume sliders (+0x2DC.. by getVolume index); brightness
// (+0x2F4) and scroll speed (+0x2F0 times 50); the health bar (+0x2BC)
// refresh; the online IP combo (+0x2B4) from IPEnumeration; the port entry
// (+0x2B8); and the check boxes for alternate mouse (+0x2C0) send delay
// (+0x2C4) messenger (+0x2C8) foreign language (+0x2CC) language filter
// (+0x2D0) EAX3 (+0x2D4) and high audio quality (+0x2D8). Gadgets are
// disabled when the screen's +0x280/+0x281/+0x283 flags are clear.
#include <map>
#include <stdio.h>

#include "ascii_string.h"
#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *a, const char *b);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class GameWindow
{
public:
	int winEnable(bool enable);
};

class BfmeKeyLC;

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int selectedIndex, bool dontHide);
void GadgetCheckBoxSetChecked(GameWindow *checkBox, bool isChecked);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetTextEntrySetValidationFlags(GameWindow *textEntry, int flags);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxChars);
// The rowed slider position setter (Zero Hour's GadgetSliderSetPosition).
int Rva0050E776Send(GameWindow *slider, int position);

// The 0x14-byte UserPreferences layout (vftable then the map at +4 and the
// file name at +0x10) as OptionPreferences_ctor.cpp has it; the temporaries'
// frame slot depends on that size.
class OptionPreferences : public _STL::map<AsciiString, AsciiString>
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	float getVolume(int which);
	float getBrightness();
	float getScrollFactor();
	bool getAlternateMouseSetup();
	unsigned int rva002E514A();
	unsigned short getFirewallPortOverride();
	bool getSendDelay();
	bool getDisplayForeignLanguage();
	bool getTurnOffMessengerInGame();
	bool getLanguageFilter();
	bool getUseEAX3();
	int getAudioLOD();

private:
	UnicodeString m_filename; // +0x10
};

// Zero Hour's EnumeratedIP without its pool glue: the address string at +0,
// the address at +4 and the next entry at +8. Its getIPstring body is
// identical-code-folded with the rowed
// MultiplayerColorDefinition::getTooltipName (a copy of the string at +0).
class EnumeratedIP
{
public:
	AsciiString m_IPstring;
	unsigned int m_IP;
	EnumeratedIP *m_next;
};

class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName() const;
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses();

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

class GameLODManager
{
public:
	unsigned char m_pad[0x17C4];
	int m_17C4; // +0x17C4
};

extern GameLODManager *TheGameLODManager;

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual int getDisplayModeCount();												// +0x5C
	virtual void getDisplayModeDescription(int modeIndex, int *xres, int *yres, int *bitDepth);	// +0x60
};

extern Display *TheDisplay;

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

// The rowed 0x00518359, run on the screen after the detail combo fills.
class Rva00518359
{
public:
	void rva00518359();
};

// The rowed 0x005183FA, called on the screen.
class Rva005183A0
{
public:
	void rva005183FA();
};

class AptOptions
{
public:
	void InitGadgets(const char *name, int unused, GameWindow *window);

private:
	unsigned char m_pad000[0x280];
	bool m_280; // +0x280
	bool m_281; // +0x281
	bool m_282; // +0x282
	bool m_online; // +0x283
	unsigned char m_pad284[0x2AC - 0x284];
	GameWindow *m_resolutionCombo; // +0x2AC
	GameWindow *m_detailCombo; // +0x2B0
	GameWindow *m_onlineIPCombo; // +0x2B4
	GameWindow *m_portEntry; // +0x2B8
	GameWindow *m_healthBars; // +0x2BC
	GameWindow *m_alternateMouse; // +0x2C0
	GameWindow *m_sendDelay; // +0x2C4
	GameWindow *m_messenger; // +0x2C8
	GameWindow *m_foreignLanguage; // +0x2CC
	GameWindow *m_languageFilter; // +0x2D0
	GameWindow *m_eax3; // +0x2D4
	GameWindow *m_highAudioQuality; // +0x2D8
	GameWindow *m_volumeSliders[5]; // +0x2DC
	GameWindow *m_scrollSpeed; // +0x2F0
	GameWindow *m_brightness; // +0x2F4
	unsigned char m_pad2F8[0x304 - 0x2F8];
	int m_defaultResolution; // +0x304
	unsigned char m_pad308[0x30C - 0x308];
	int m_resolution; // +0x30C
};

void AptOptions::InitGadgets(const char *name, int unused, GameWindow *window)
{
	if (window == 0)
		return;

	int color = -1;
	GadgetComboBoxReset(window);
	UnicodeString str;
	int val = 0;

	if (strcmp(name, "Options::Resolution") == 0)
	{
		m_resolutionCombo = window;
		AsciiString selectedResolution = OptionPreferences()["Resolution"];
		int defaultXRes, defaultYRes, selectedXRes, selectedYRes;
		if (TheGameLODManager->m_17C4 <= 0)
		{
			defaultXRes = 800;
			selectedXRes = defaultXRes;
			defaultYRes = 600;
			selectedYRes = defaultYRes;
		}
		else
		{
			defaultXRes = 1024;
			selectedXRes = defaultXRes;
			defaultYRes = 768;
			selectedYRes = defaultYRes;
		}
		int selectedResIndex = -1;
		if (!selectedResolution.isEmpty())
		{
			if (sscanf(selectedResolution.str(), "%d%d", &selectedXRes, &selectedYRes) != 2)
			{
				selectedXRes = defaultXRes;
				selectedYRes = defaultYRes;
			}
		}
		int numResolutions = TheDisplay->getDisplayModeCount();
		for (int i = 0; i < numResolutions; ++i)
		{
			int xres, yres, bitDepth;
			TheDisplay->getDisplayModeDescription(i, &xres, &yres, &bitDepth);
			str.format(L"%dx%d", xres, yres);
			GadgetComboBoxAddEntry(window, str, color);
			if (xres == defaultXRes && yres == defaultYRes)
				m_defaultResolution = i;
			if (xres == selectedXRes && yres == selectedYRes)
				selectedResIndex = i;
		}
		m_resolution = selectedResIndex;
		GadgetComboBoxSetSelectedPos(window, selectedResIndex, false);
		if (!m_280)
			window->winEnable(false);
		return;
	}
	if (strcmp(name, "Options::Detail") == 0)
	{
		int index;
		index = GadgetComboBoxAddEntry(window, TheGameText->fetch("GUI:UltraHigh"), color);
		GadgetComboBoxSetItemData(window, index, (void *)4);
		index = GadgetComboBoxAddEntry(window, TheGameText->fetch("GUI:High"), color);
		GadgetComboBoxSetItemData(window, index, (void *)3);
		index = GadgetComboBoxAddEntry(window, TheGameText->fetch("GUI:Medium"), color);
		GadgetComboBoxSetItemData(window, index, (void *)2);
		index = GadgetComboBoxAddEntry(window, TheGameText->fetch("GUI:Low"), color);
		GadgetComboBoxSetItemData(window, index, (void *)1);
		index = GadgetComboBoxAddEntry(window, TheGameText->fetch("GUI:VeryLow"), color);
		GadgetComboBoxSetItemData(window, index, (void *)0);
		index = GadgetComboBoxAddEntry(window, TheGameText->fetch("GUI:Custom"), color);
		GadgetComboBoxSetItemData(window, index, (void *)5);
		m_detailCombo = window;
		((Rva00518359 *)this)->rva00518359();
		if (!m_281)
			window->winEnable(false);
		return;
	}
	if (strcmp(name, "Options::MusicVolume") == 0)
	{
		m_volumeSliders[2] = window;
		val = (int)OptionPreferences().getVolume(2);
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::SoundFxVolume") == 0)
	{
		m_volumeSliders[0] = window;
		val = (int)OptionPreferences().getVolume(0);
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::VoiceVolume") == 0)
	{
		m_volumeSliders[1] = window;
		val = (int)OptionPreferences().getVolume(1);
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::AmbientVolume") == 0)
	{
		m_volumeSliders[3] = window;
		val = (int)OptionPreferences().getVolume(3);
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::MovieVolume") == 0)
	{
		m_volumeSliders[4] = window;
		val = (int)OptionPreferences().getVolume(4);
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::Brightness") == 0)
	{
		m_brightness = window;
		val = (int)OptionPreferences().getBrightness();
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::ScrollSpeed") == 0)
	{
		m_scrollSpeed = window;
		val = (int)(OptionPreferences().getScrollFactor() * 50.0f);
		Rva0050E776Send(window, val);
	}
	else if (strcmp(name, "Options::HealthBars") == 0)
	{
		m_healthBars = window;
		((Rva005183A0 *)this)->rva005183FA();
	}
	else if (strcmp(name, "Options::AlternateMouseSetUp") == 0)
	{
		m_alternateMouse = window;
		bool checked = !OptionPreferences().getAlternateMouseSetup();
		GadgetCheckBoxSetChecked(window, checked);
	}
	else if (strcmp(name, "Options::OnlineIp") == 0)
	{
		m_onlineIPCombo = window;
		unsigned int selectedIP = OptionPreferences().rva002E514A();
		UnicodeString ipText;
		IPEnumeration IPs;
		EnumeratedIP *IPlist = IPs.getAddresses();
		int selectedIndex = -1;
		while (IPlist)
		{
			ipText.translate(((const MultiplayerColorDefinition *)IPlist)->getTooltipName());
			int index = GadgetComboBoxAddEntry(m_onlineIPCombo, ipText, color);
			GadgetComboBoxSetItemData(m_onlineIPCombo, index, (void *)IPlist->m_IP);
			if (selectedIP == IPlist->m_IP)
				selectedIndex = index;
			IPlist = IPlist->m_next;
		}
		if (selectedIndex >= 0)
			GadgetComboBoxSetSelectedPos(m_onlineIPCombo, selectedIndex, false);
		else
			GadgetComboBoxSetSelectedPos(m_onlineIPCombo, 0, false);
		if (!m_online)
			m_onlineIPCombo->winEnable(false);
	}
	else if (strcmp(name, "Options::OnlinePortNum") == 0)
	{
		m_portEntry = window;
		GadgetTextEntrySetValidationFlags(window, 0x20);
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 5);
		unsigned short port = OptionPreferences().getFirewallPortOverride();
		if (port > 0)
		{
			UnicodeString portText;
			portText.format(L"%d", port);
			GadgetTextEntrySetText(m_portEntry, portText);
		}
		else
		{
			GadgetTextEntrySetText(m_portEntry, L"");
		}
		if (!m_online)
			window->winEnable(false);
	}
	else if (strcmp(name, "Options::Firewall") == 0)
	{
	}
	else if (strcmp(name, "Options::SendDelay") == 0)
	{
		m_sendDelay = window;
		bool checked = OptionPreferences().getSendDelay();
		GadgetCheckBoxSetChecked(window, checked);
		if (!m_online)
			window->winEnable(false);
	}
	else if (strcmp(name, "Options::DisplayForeignLanguage") == 0)
	{
		m_foreignLanguage = window;
		bool checked = OptionPreferences().getDisplayForeignLanguage();
		GadgetCheckBoxSetChecked(window, checked);
	}
	else if (strcmp(name, "Options::TurnOffMessengerInGame") == 0)
	{
		m_messenger = window;
		bool checked = OptionPreferences().getTurnOffMessengerInGame();
		GadgetCheckBoxSetChecked(window, checked);
		if (!m_online)
			window->winEnable(false);
	}
	else if (strcmp(name, "Options::FilterLanguage") == 0)
	{
		m_languageFilter = window;
		bool checked = OptionPreferences().getLanguageFilter();
		GadgetCheckBoxSetChecked(window, checked);
	}
	else if (strcmp(name, "Options::EAX3") == 0)
	{
		m_eax3 = window;
		GadgetCheckBoxSetChecked(window, OptionPreferences().getUseEAX3());
	}
	else if (strcmp(name, "Options::HighAudioQuality") == 0)
	{
		m_highAudioQuality = window;
		int lod = OptionPreferences().getAudioLOD();
		if (lod == 1)
			GadgetCheckBoxSetChecked(window, true);
		else
			GadgetCheckBoxSetChecked(window, false);
	}
}
