// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/GUI/LoadScreenUpdates.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ShellGameLoadScreen::update 0x00356082 (32B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// LoadScreen layout and subclass relation follow the donor. BFME 2 confirms
// the ready byte at +0x0C and ShellGameLoadScreen's progress bar at +0x10.
// The base frame below is reconstructed from retail's complete 109-byte
// body; its slot offsets and scripted-UI global differ from BFME 1.

#include "unicode_string.h"

#define BFME_VSLOT(n) virtual void slot##n();

class GameWindow;
struct RGBColor;

void GadgetProgressBarSetProgress( GameWindow *g, int progress );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
// The union of the two views the six bodies had of this table: MapTransfer's
// full update at +0x28 sat where GameSpy's copy counted an unnamed slot 10.
class NetworkInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4) BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	BFME_VSLOT(8)
	virtual void liteupdate( int mode );              // +0x24
	virtual void update( int mode );                  // +0x28
	BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13)
	BFME_VSLOT(14) BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17)
	BFME_VSLOT(18) BFME_VSLOT(19) BFME_VSLOT(20) BFME_VSLOT(21)
	BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24) BFME_VSLOT(25)
	BFME_VSLOT(26) BFME_VSLOT(27)
	virtual void updateLoadProgress( int percent );   // +0x70
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4)
	virtual int getLocalSlotNum();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void processProgress( int player, int percent );
};

class Mouse
{
public:
	void rva001EEA6D( UnicodeString tooltip, int index, const RGBColor *color,
		float delay );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15)
	BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22)
	virtual void serviceWindowsOS();  // BFME 2 +0x5C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual void update();  // BFME 2 +0x28
};

// BFME 2 Apt window manager at VA 0x00DFE4CC.
class BfmeAptWindowManager
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual void update();  // BFME 2 +0x28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual void update();  // BFME 2 +0x28
	BFME_VSLOT(11)
	virtual void draw();    // BFME 2 +0x30
};

#undef BFME_VSLOT

extern NetworkInterface *TheNetwork;
extern GameInfo *TheGameInfo;
extern GameLogic *TheGameLogic;
extern Mouse *TheMouse;
extern GameEngine *TheGameEngine;
extern GameWindowManager *TheWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern Display *TheDisplay;
extern void setFPMode();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
// The donor places update in slot 1 and carries a 16-byte base. BFME 2
// independently tests +0x0C and uses the subclass progress bar at +0x10.
class LoadScreen
{
public:
	virtual void slot00();
	virtual void update( int percent );
	virtual void init();
	virtual void reset();

protected:
	unsigned char m_unmodelled_04[4];
	GameWindow *m_loadScreen;					// this+0x08
	unsigned char m_ready;						// this+0x0C
	unsigned char m_unmodelled_0D[3];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class ShellGameLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
	virtual void reset();

private:
	GameWindow *m_progressBar;					// this+0x10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class MultiPlayerLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class GameSpyLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class MapTransferLoadScreen
{
public:
	void update( int percent );
};


// ?update@ShellGameLoadScreen@@UAEXH@Z
// BFME 2 retail 0x00356082, 32 bytes.
void ShellGameLoadScreen::update( int percent )
{
	GadgetProgressBarSetProgress( m_progressBar, percent );
	LoadScreen::update( percent );
}



// ?update@LoadScreen@@UAEXH@Z retail 0x00355FF9..0x00356066 (109B).
// Donor: Open-BFME-1 ba7ddda7 LoadScreenUpdates.cpp and readable LoadScreen.cpp.
// Target: byte +0xC readiness guard, UnicodeString copy 0x00037050,
// mouse tooltip 0x001EEA6D, globals DFDCA0/DFE710/DFEF1C/DFE4CC/DFE9D8,
// virtual slots 5C/28/28/28/30, then rowed setFPMode 0x00040EA9.
// Existing ShellGameLoadScreen wrapper calls this address nonvirtually;
// target slots are wider than the donor's BFME 1 tables.
void LoadScreen::update(int)
{
	if (m_ready) {
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		TheGameEngine->serviceWindowsOS();
		TheWindowManager->update();
		g_bfmeAptWindowManager->update();
		TheDisplay->update();
		TheDisplay->draw();
	}
	setFPMode();
}
