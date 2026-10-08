// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// GameClient's pending display mode switch, run from GameClient::update
// (call at 0x0023C2EB). BFME 1 inlines the same code into its client update
// (Open-BFME-1 ClientUpdate004329D0.cpp); BFME 2 keeps it out of line. The
// mode change itself follows ZH OptionsMenu.cpp: set the display mode, store
// the resolution in TheWritableGlobalData and notify the header templates and
// the mouse, then delete and recreate the shell on "MainMenu.apt".
//
// Target evidence: the request fields are written by the rowed setters
// 0x00238F91 (new mode, remember the current one) and 0x00238FC0 (back to
// the remembered mode), Rva00238E1BCounter.cpp's view of this class.

#include "ascii_string.h"
#include "GUI/HeaderTemplateView.h"

class Shell
{
public:
	Shell();
	virtual ~Shell();
	virtual void init();

	void push(AsciiString filename, bool shutdownImmediate);

private:
	unsigned char m_pad004[0x78 - 0x04];
};

extern Shell *TheShell;

// ZH's Display slots 16..22.
class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual void setBitDepth(unsigned int bitDepth);
	virtual unsigned int getBitDepth();
	virtual void setWindowed(bool windowed);
	virtual bool getWindowed();
	virtual bool setDisplayMode(unsigned int xres, unsigned int yres, unsigned int bitdepth, bool windowed);
};

extern Display *TheDisplay;

class GlobalData
{
public:
	unsigned char m_pad000[0x30];
	unsigned int m_xResolution; // +0x30
	unsigned int m_yResolution; // +0x34
};

extern GlobalData *TheWritableGlobalData;

// ZH's mouseNotifyResolutionChange lands on the shared empty body 0x000B3FD0
// (pinned by address, as in AptMainMenuCallbacks.cpp).
class Mouse
{
public:
	void rva000B3FD0();
};

extern Mouse *TheMouse;

// Unrowed 0x0041267F (10 bytes: two calls), pinned by address; AptMainMenu's
// ResetResolution calls it after the mouse too.
void Rva0041267F();

// Both window managers refresh through their vslot 10.
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void v10();
};

extern GameWindowManager *TheWindowManager;

class BfmeAptWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void v10();
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// TheInGameUI's vslot 108 refreshes the layout after a resolution change
// (ZH's recreateControlBar position in OptionsMenu.cpp).
class InGameUI
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107)
#undef V
	virtual void v108();
};

extern InGameUI *TheInGameUI;

extern HeaderTemplateManager *TheHeaderTemplateManager;

class GameClient
{
public:
	virtual ~GameClient();

	void rva00239759();

private:
	unsigned char m_pad004[0xC9 - 0x04];
	bool m_displayModeChangePending; // +0xC9
	bool m_rememberDisplayMode; // +0xCA
	unsigned int m_newXResolution; // +0xCC
	unsigned int m_newYResolution; // +0xD0
	unsigned int m_newBitDepth; // +0xD4
	unsigned int m_oldXResolution; // +0xD8
	unsigned int m_oldYResolution; // +0xDC
	unsigned int m_oldBitDepth; // +0xE0
};

// Retail 0x00239759, 440 bytes.
void GameClient::rva00239759()
{
	if (m_displayModeChangePending)
	{
		::delete TheShell;
		TheShell = 0;
		m_displayModeChangePending = false;

		if (m_newXResolution > 0 && m_newYResolution > 0 && m_newBitDepth > 0
			&& (m_newXResolution != TheWritableGlobalData->m_xResolution
				|| m_newYResolution != TheWritableGlobalData->m_yResolution))
		{
			if (m_rememberDisplayMode)
			{
				m_oldXResolution = TheDisplay->getWidth();
				m_oldYResolution = TheDisplay->getHeight();
				m_oldBitDepth = TheDisplay->getBitDepth();
			}

			if (TheDisplay->setDisplayMode(m_newXResolution, m_newYResolution, m_newBitDepth, TheDisplay->getWindowed()))
			{
				TheWritableGlobalData->m_xResolution = m_newXResolution;
				TheWritableGlobalData->m_yResolution = m_newYResolution;
				TheHeaderTemplateManager->headerNotifyResolutionChange();
				TheMouse->rva000B3FD0();
				Rva0041267F();
			}
			else
			{
				m_rememberDisplayMode = false;
			}

			m_newXResolution = 0;
			m_newYResolution = 0;
			m_newBitDepth = 0;
		}

		TheShell = new Shell;
		if (TheShell)
			TheShell->init();

		TheWindowManager->v10();
		g_bfmeAptWindowManager->v10();
		TheInGameUI->v108();

		TheShell->push(AsciiString("MainMenu.apt"), false);
	}
}
