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

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
#include "ascii_string.h"
#include "GUI/HeaderTemplateView.h"

#include "../../Include/GameClient/Shell.h"

extern Shell *TheShell;

// ZH's Display slots 16..22.
#include "../../Include/GameClient/Display.h"

extern Display *TheDisplay;

#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

// ZH's mouseNotifyResolutionChange lands on the shared empty body 0x000B3FD0
// (pinned by address, as in AptMainMenuCallbacks.cpp).
#include "../../Include/GameClient/Mouse.h"

extern Mouse *TheMouse;

// Unrowed 0x0041267F (10 bytes: two calls), pinned by address; AptMainMenu's
// ResetResolution calls it after the mouse too.
void Rva0041267F();

// Both window managers refresh through their vslot 10.
#include "../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;


extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// TheInGameUI's vslot 108 refreshes the layout after a resolution change
// (ZH's recreateControlBar position in OptionsMenu.cpp).
#include "../../Include/GameClient/InGameUI.h"

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

		TheWindowManager->update();
		g_bfmeAptWindowManager->update();
		TheInGameUI->recreateControlBar();

		TheShell->push(AsciiString("MainMenu.apt"), false);
	}
}
