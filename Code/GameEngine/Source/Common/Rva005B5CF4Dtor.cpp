// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG
// ??1Rva005B5CF4@@UAE@XZ, retail 0x005B5CF4..0x005B5E03 (271 bytes, EH):
// by its literals the Create-a-Hero manager screen's destructor (opaque pin
// of its scalar deleting destructor 0x005B6166; table 0x00C735C0). It closes
// the "CahManager::InitGadgets" Apt screen; when its +0x16 flag is set it
// stops the game (rowed GameLogic::clearGameData) and continues by the mode at
// +0x40C of its +4 object: 1 starts the "TEST CaHTestMap" map the way
// AptMainMenu::OnTutorial starts a tutorial (message 0x1D, map name, random
// loading film 0x0023D614 through 0x0023DC8E, message 0x1E with 6, 0, 0), 2
// and 3 start the good and evil campaigns (rowed 0x00515BCA / 0x00515C17)
// at 0x45. The base's inline destructor restores 0x00C72B74 (out-of-line
// copy ??1Rva005B253F 0x005B2551).
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"

void _bfme_closeAptScreen(const AsciiString &name);
void Rva0023D614Set(StringBase<char> *out);
void __cdecl startGoodCampaign(char side);
void __cdecl startEvilCampaign(char side);

extern GameLogic *TheGameLogic;

class Rva0023DC8E
{
public:
	void rva0023DC8E(const AsciiString &value);
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *TheMessageStream;

struct CahGlobalView
{
	char m_pad00[0xAC0];
	AsciiString m_mapName;			// +0xAC0
};

extern class GlobalData *TheWritableGlobalData;

struct Rva005B5CF4Setup
{
	char m_pad00[0x40C];
	int m_mode;				// +0x40C
};

class Rva005B253F
{
public:
	virtual ~Rva005B253F() {}
};

class Rva005B5CF4 : public Rva005B253F
{
public:
	virtual ~Rva005B5CF4();
private:
	Rva005B5CF4Setup *m_setup;		// +0x04
	char m_pad08[0x16 - 8];
	bool m_startOnExit;			// +0x16
};

Rva005B5CF4::~Rva005B5CF4()
{
	_bfme_closeAptScreen(AsciiString("CahManager::InitGadgets"));
	if (m_startOnExit)
	{
		TheGameLogic->clearGameData(false, false);
		switch (m_setup->m_mode)
		{
		case 1:
		{
			TheMessageStream->appendMessage(0x1D);
			((CahGlobalView *)TheWritableGlobalData)->m_mapName = "UserData\\Maps\\TEST CaHTestMap\\TEST CaHTestMap.map";
			AsciiString film;
			Rva0023D614Set((StringBase<char> *)&film);
			((Rva0023DC8E *)TheGameLogic)->rva0023DC8E(film);
			GameMessage *message = TheMessageStream->appendMessage(0x1E);
			message->appendIntegerArgument(6);
			message->appendIntegerArgument(0);
			message->appendIntegerArgument(0);
			break;
		}
		case 3:
			startEvilCampaign('E');
			break;
		case 2:
			startGoodCampaign('E');
			break;
		}
	}
}
