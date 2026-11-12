// cl: /MD /EHsc /EHc- /D_CRTIMP=
// ??1AptOptions@@UAE@XZ @0x00518769 297B
// AptOptions dtor: current-window global clear, audio handle release via TheAudio slot 0x70, InitGadgets close, GameClient triple, globals gate Shell, three strings free base AptGameWindow. Evidence: literal AptOptions::InitGadgets 0x0086667C, base pin 0x005126F5, caller 0x00518AE9 deleting dtor.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <stdlib.h>


void _bfme_closeAptScreen(const AsciiString &name);

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();
private:
	char m_pad[0x218 - 4];
};

#include "../../Include/GameClient/BfmeAptFunctorMarker.h"

#include "../../Include/Common/GameAudio.h"

class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

#include "../../Include/GameClient/Rva00238E1B.h"

#include "../../Include/GameClient/Shell.h"

struct GlobalA04910
{
	char m_pad[0x278];
	unsigned char m_278;
};
class AptQuitMenu; extern AptQuitMenu *TheAptQuitMenu;

struct GlobalA01E48
{
	char m_pad[0x54];
	unsigned char m_54;
};
class Shell;
extern Shell *TheShell;

extern int g_Va00A04908;

struct AptFreePtr
{
	void *p;
	~AptFreePtr() { if (p) free(p); }
};

class __multiple_inheritance AptOptions : public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~AptOptions();
private:
	char m_pad21C[0x6C];
	AptFreePtr m_288;
	char m_pad28C[0x10];
	int m_29C;
	int m_2A0;
	int m_2A4;
	char m_pad2A8[0x50];
	unsigned char m_2F8;
	char m_pad2F9[3];
	unsigned int m_2FC;
	char m_pad300[8];
	AsciiString m_308;
	char m_pad30C[8];
	AsciiString m_314;
	char m_pad318[8];
	AsciiString m_320;
};

AptOptions::~AptOptions()
{
	if (g_Va00A04908 == (int)this)
	{
		g_Va00A04908 = 0;
		if (m_2FC != 0)
		{
			TheAudio->killAudioEventImmediately(m_2FC);
			m_2FC = 0;
		}
		_bfme_closeAptScreen(AsciiString("AptOptions::InitGadgets"));
		if (m_2F8)
		{
			((Rva00238E1B *)((ClientFrameSubsystem *)TheGameClient))->rva00238F91(m_29C, m_2A0, m_2A4);
		}
		if ((*(GlobalA04910 * *)&TheAptQuitMenu) != 0 && (*(GlobalA04910 * *)&TheAptQuitMenu)->m_278 != 0)
		{
			if (TheShell != 0)
			{
				((GlobalA01E48 *)TheShell)->m_54 = 1;
				((Shell *)TheShell)->pop();
			}
		}
	}
}
