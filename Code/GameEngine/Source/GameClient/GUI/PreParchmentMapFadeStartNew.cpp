// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /Oi- /DNDEBUG /DWIN32 /O1 /arch:SSE /G7
#include "ascii_string.h"

typedef bool Bool;

// Target string "PreParchmentMapFade_StartNew" and matching BFME1 reference
// function rva0051E280PreParchmentMapFadeStartNew establish this callback's
// identity. Retail uses the BFME2 WindowManager owner and a shifted audio slot.
class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name, bool immediate);
	bool isFinished();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Shell
{
public:
	char m_pad00[0x6c];
	bool m_unknown6c;
};
extern Shell *TheShell;

class Rva0035BD3F
{
public:
	void rva0035BD3F();
};

class ModuleData;
class Rva00223CBD
{
public:
	void rva00223CBD(const ModuleData *data);
};
class BfmeAptWindowManager : public Rva00223CBD {};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(int, int, int);
};
extern AudioManager *TheAudio;

// ?rva0051E280PreParchmentMapFadeStartNew@@YAHH_N@Z
// The donor's transition result and group setup transfer directly. Retail
// 0x005157EE uses the target-specific WindowManager call and Audio slot 38.
int rva0051E280PreParchmentMapFadeStartNew(int, bool start)
{
	const bool go = start;
	int result = 1;
	if (go)
	{
		TheTransitionHandler->setGroup(AsciiString("PreParchmentMapFade_StartNew"), 0);
		if (TheShell)
		{
			((Rva0035BD3F *)TheShell)->rva0035BD3F();
			TheShell->m_unknown6c = false;
		}
		g_bfmeAptWindowManager->rva00223CBD((const ModuleData *)-1);
	}
	else if (TheTransitionHandler->isFinished())
	{
		TheAudio->slot38(1, 1, 1);
		TheAudio->slot38(2, 1, 1);
		TheAudio->slot38(0, 1, 1);
		result = 3;
	}
	return result;
}
