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

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void releaseAt70(void *p);
};
extern AudioManager *TheAudio;

class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva00238E1B
{
public:
	void rva00238F91(int a, int b, int c);
};

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
	void *m_2FC;
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
			TheAudio->releaseAt70(m_2FC);
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
