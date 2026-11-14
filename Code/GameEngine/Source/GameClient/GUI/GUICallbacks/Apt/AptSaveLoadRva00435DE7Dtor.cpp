// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /O1 /G7 /arch:SSE /I.
class AptSaveLoad;
// stlport
// Target evidence: vptr pair 0x00C3CDC8/0x00C3CDC4 at this/+0x218, AptSaveLoad
// strings and neighboring callbacks, pending kind at +0x28, and the fields
// read through +0x2AC. The opaque address-derived type keeps the owner name
// unclaimed. The two-base/string prefix follows the independently matched
// BFME2 _bfme_AptGameWindow destructor; BFME1 AptSaveLoad dtor is a semantic
// and control-flow donor, with target-specific pending and replay branches.
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class RecorderClass; extern RecorderClass *TheRecorder;

class AptQuitMenu; extern AptQuitMenu *TheAptQuitMenu;

extern int g_Va00E0333C;


extern class GameWindowManager *TheWindowManager;

extern class Shell *TheShell;

extern class LivingWorldLogic *TheLivingWorldLogic;

extern class GameState *TheGameState;

extern class GameLogic *TheGameLogic;

extern class GameEngine *TheGameEngine;

extern class AudioManager *TheAudio;

#include <list>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../../../Include/GameClient/Rva005248D0.h"

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename270;
};

struct BfmeSubobject0022CE19
{
	virtual ~BfmeSubobject0022CE19();
	unsigned char m_pad004[0x20];
	int m_kind;
	unsigned char m_opaque028[0xDE4 - 0x24];
	BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};

struct TreeHintOpaque0043671B
{
	UnicodeString m_text;
	BfmeSubobject0022CE19 m_subobject;
	unsigned int m_wordDEC;
	unsigned int m_wordDF0;
	TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
	~TreeHintOpaque0043671B();
};

#include "../../../../../Include/GameClient/Rva002244CA.h"

#include "../../../../../Include/Common/Rva00222A8BTarget.h"

#include "../../../../../Include/Common/GameState.h"

#include "../../../../../Include/Common/RecorderClass.h"

#include "../../../../../Include/GameClient/Shell.h"

class GameEngineView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
};

class GameWindowManagerView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
};

class AudioManagerView
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void slot8C(int a, int b, int c);
};

// The rowed 0x002B2E77 ignores ECX, but both native callers load the
// living-world receiver before its ret-4 call: a thiscall member.
#include "../../../../../Include/GameLogic/LivingWorldLogic.h"

void Rva0051AF0BEnable(int value);
void Rva005210ECEnable(bool value);
void _bfme_closeAptScreen(const AsciiString &name);

class AptSaveLoad : public _bfme_AptGameWindow
{
public:
	static AptSaveLoad *s_instance;
	virtual ~AptSaveLoad();

private:
	unsigned char m_pad274[8];
	int m_state; // +0x27C
	TreeHintOpaque0043671B *m_pending; // +0x280
	bool m_pausedOnEntry; // +0x284
	unsigned char m_pad285[3];
	void *m_gameList; // +0x288
	void *m_autoSaveList; // +0x28C
	void *m_fileName; // +0x290
	unsigned char m_pad294[8];
	bool m_29C;
	bool m_29D;
	unsigned char m_pad29E[2];
	int m_mode; // +0x2A0
	bool m_flag2A4;
	unsigned char m_pad2A5[3];
	int m_2A8;
	_STL::list<TreeHintOpaque0043671B, _STL::allocator<TreeHintOpaque0043671B> > m_list;
};

// Native DC8A20 is the complete three-pointer deregistration table.
// The pointed strings are independently owned bytes at C3CB64/C3CB58/C3CB48;
// the original source identifiers are unknown.
extern const char BfmeSaveLoadRegistrationMode[] = "SaveLoadMode";
extern const char BfmeSaveLoadRegistrationTypes[] = "GameTypes";
extern const char BfmeSaveLoadRegistrationCurrentType[] = "CurrentGameType";
extern const char *const BfmeSaveLoadRegistrations[3] = {
 BfmeSaveLoadRegistrationMode,
 BfmeSaveLoadRegistrationTypes,
 BfmeSaveLoadRegistrationCurrentType
};

AptSaveLoad::~AptSaveLoad()
{
	bool showBackground = true;
	const char *const *registrations =
		BfmeSaveLoadRegistrations;

	if (*(void **)&g_bfmeAptWindowManager != 0)
	{
		showBackground = false;
		for (int i = 0; i < 3; ++i)
		{
			AsciiString name(registrations[i]);
			((Rva002244CA *)*(void **)&g_bfmeAptWindowManager)->RemoveExternHandler(&name);
		}

		_bfme_closeAptScreen(AsciiString("AptSaveLoad::InitGadgets"));

		GameLogic *logic = (GameLogic *)*(void **)&TheGameLogic;
		int one = 1;
		*(int *)&AptSaveLoad::s_instance = 0;
		if (logic != 0)
			logic->rva0023CD9E(m_pausedOnEntry, 2, one);

		if (m_state == 6 && m_pending != 0)
		{
			switch (m_pending->m_subobject.m_kind)
			{
			case 0:
			case 3:
			case 5:
				showBackground = true;
				// fall through
			case 4:
			case 7:
			case 8:
				m_flag2A4 = true;
				break;
			case 2:
			{
				void *pendingWindow = *(void **)&(*(int *)&TheAptQuitMenu);
				if (pendingWindow != 0)
					*((unsigned char *)pendingWindow + 0x27D) = 1;
			}
				// fall through
			case 1:
			case 6:
				m_flag2A4 = false;
				break;
			}

			if (m_pending->m_subobject.m_kind == 6)
			{
				void *owner = *(void **)&g_Va00E0333C;
				if (owner != 0)
					*(TreeHintOpaque0043671B **)((char *)owner + 0x2B0) = m_pending;
			}
			else
			{
				Rva0051AF0BEnable(2);
				Rva005210ECEnable(false);
				Rva00222A8BTarget *aptWindowManager =
					(Rva00222A8BTarget *)*(void **)&g_bfmeAptWindowManager;
				aptWindowManager->slot28();
				GameWindowManagerView *windowManager =
					(GameWindowManagerView *)*(void **)&TheWindowManager;
				windowManager->slot28();
				((Shell *)*(void **)&TheShell)->hide(one);

				if (m_pending->m_subobject.m_kind != 7)
				{
					int result = ((GameState *)*(void **)&TheGameState)->
							rva002DE3C1(*m_pending);
					if (result != 0)
					{
						((Shell *)*(void **)&TheShell)->showShell(one);
						m_flag2A4 = false;
					}
				}
			else if (!TheRecorder->
				playbackFile(m_pending->m_text))
			{
				((GameLogic *)*(void **)&TheGameLogic)->clearGameData(
					false, one);
				GameEngineView *engine =
					(GameEngineView *)*(void **)&TheGameEngine;
				engine->slot24();
				((Shell *)*(void **)&TheShell)->showShell(one);
				}
			}
		}

		else if (m_state == 10)
	{
		Rva0051AF0BEnable(0);
		if (m_29C)
			((Shell *)*(void **)&TheShell)->hide(one);

		LivingWorldLogic *livingWorld = TheLivingWorldLogic;
		if (m_2A8 == 1 && livingWorld != 0)
			livingWorld->rva002B2E77(1);
		else if (m_2A8 == 2 && livingWorld != 0)
		{
			livingWorld->rva002B2E77(2);
		}
	}

	if (m_flag2A4)
		((Rva00222A8BTarget *)*(void **)&g_bfmeAptWindowManager)->
			rva00222F55(showBackground);

	if (m_29D)
	{
		Shell *shell = (Shell *)*(void **)&TheShell;
		if (shell == 0 || !shell->rva0035BD5D())
		{
			AudioManagerView *audio =
				(AudioManagerView *)*(void **)&TheAudio;
			audio->slot8C(2, one, 0);
		}
	}
	}
}
