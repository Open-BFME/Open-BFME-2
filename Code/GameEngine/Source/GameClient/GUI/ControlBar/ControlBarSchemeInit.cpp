// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /G7 /arch:SSE /MD
// ?init@ControlBarScheme@@QAEXXZ
// Native boundary: Ghidra FUN_0071ed2c, 0x0031ED2C..0x0031F743 (ret at F742).
// Donor: Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme.cpp.
// Identity: the complete donor image/window setup sequence, the ten window
// names and their native nameToKey / window-manager calls, the creation
// resolution at +4/+8, and the image/rectangle accesses agree independently.
// Member labels and the repeated positioning algorithm follow the donor.
// Target layout: fifth border color at +2C; images and rectangles at the
// offsets below; ControlBar border/arrow slots are +22C/+26C here.
// The called helper names retain the existing ledger's address-derived types
// where its current recovered declarations do not establish an original name.
// Only the virtual slots observed by this body are declared in the call views.
typedef int Int;
typedef int Color;
#define NULL 0
#define INT_TO_REAL(x) ((float)(x))
struct ICoord2D { int x,y; };
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include "ascii_string.h"
class Image;
class ModuleData;
enum ControlBarStages { CONTROL_BAR_STAGE_DEFAULT=0 };
class ControlBar {
public:
 void switchControlBarStage(ControlBarStages);
 void updateRightHUDImage(const Image *);
 void rva0031AD14(int,int,int,int,int);
 void rva0031B1BC(const Image *,const Image *,const Image *,const Image *,const Image *,const Image *,const Image *,const Image *);
};
class Rva0031410CDwordSlot { public: void set(int); };
class Rva0031BE07 { public: void rva0031BE58(const ModuleData *); };
struct BfmeControlBarSchemeInitBar {
 unsigned char pad0[0x22c]; Color m_commandBarBorderColor;
 unsigned char pad230[0x26c-0x230]; const Image *m_genArrow;
};
extern ControlBar *TheControlBar;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindow {
public:
 GameWindow *winGetParent();
 int winGetScreenPosition(int *,int *);
 int winSetPosition(int,int);
 int winSetSize(int,int);
 int winSetEnabledImage(int,const Image *);
 int winSetDisabledImage(int,const Image *);
};
class Display { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual unsigned int getWidth();
virtual unsigned int getHeight();
};
extern Display *TheDisplay;
class GameWindowManager { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual GameWindow *winGetWindowFromId(GameWindow *,NameKeyType);
};
extern GameWindowManager *TheWindowManager;
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *, const Image *);
void GadgetButtonSetHiliteImage_Rva002C04DB(GameWindow *, const Image *);
void GadgetButtonSetHiliteImage123_Rva002C0505(GameWindow *, const Image *);
void GadgetButtonSetDisabledImage_Rva002C0487(GameWindow *, const Image *);
enum { COMMAND_BAR_SIZE_OFFSET=0 };
class ControlBarScheme { public: void init(); };
struct BfmeControlBarSchemeInitView
{
	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;
	Image *m_buttonQueueImage;
	Image *m_rightHUDImage;					///< +0x14
	Color m_buildUpClockColor;				///< +0x18
	Color m_borderBuildColor;				///< +0x1c
	Color m_borderActionColor;
	Color m_borderUpgradeColor;
	Color m_borderSystemColor;
	Color m_bfmeBorderFifthColor;			///< +0x2c
	Color m_commandBarBorderColor;			///< +0x30
	Image *m_optionsButtonEnable;			///< +0x34
	Image *m_optionsButtonHightlited;
	Image *m_optionsButtonPushed;
	Image *m_optionsButtonDisabled;
	Image *m_idleWorkerButtonEnable;		///< +0x44
	Image *m_idleWorkerButtonHightlited;
	Image *m_idleWorkerButtonPushed;
	Image *m_idleWorkerButtonDisabled;
	Image *m_buddyButtonEnable;				///< +0x54
	Image *m_buddyButtonHightlited;
	Image *m_buddyButtonPushed;
	Image *m_buddyButtonDisabled;
	Image *m_beaconButtonEnable;			///< +0x64
	Image *m_beaconButtonHightlited;
	Image *m_beaconButtonPushed;
	Image *m_beaconButtonDisabled;
	Image *m_genBarButtonIn;				///< +0x74
	Image *m_genBarButtonOn;
	Image *m_toggleButtonUpIn;				///< +0x7c
	Image *m_toggleButtonUpOn;
	Image *m_toggleButtonUpPushed;
	Image *m_toggleButtonDownIn;
	Image *m_toggleButtonDownOn;
	Image *m_toggleButtonDownPushed;
	Image *m_generalButtonEnable;			///< +0x94
	Image *m_generalButtonHightlited;
	Image *m_generalButtonPushed;
	Image *m_generalButtonDisabled;
	Image *m_uAttackButtonEnable;			///< +0xa4
	Image *m_uAttackButtonHightlited;
	Image *m_uAttackButtonPushed;
	Image *m_minMaxButtonEnable;			///< +0xb0
	Image *m_minMaxButtonHightlited;
	Image *m_minMaxButtonPushed;
	Image *m_genArrow;						///< +0xbc
	ICoord2D m_moneyUL;						///< +0xc0
	ICoord2D m_moneyLR;
	ICoord2D m_minMaxUL;
	ICoord2D m_minMaxLR;
	ICoord2D m_generalUL;
	ICoord2D m_generalLR;
	ICoord2D m_uAttackUL;					///< +0xf0
	ICoord2D m_uAttackLR;
	ICoord2D m_optionsUL;
	ICoord2D m_optionsLR;
	ICoord2D m_workerUL;
	ICoord2D m_workerLR;
	ICoord2D m_chatUL;						///< +0x120
	ICoord2D m_chatLR;
	ICoord2D m_beaconUL;
	ICoord2D m_beaconLR;
	ICoord2D m_powerBarUL;
	ICoord2D m_powerBarLR;
	Image *m_expBarForeground;				///< +0x150
	Image *m_commandMarkerImage;			///< +0x154
};

void ControlBarScheme::init(void)
{
	BfmeControlBarSchemeInitView *self = (BfmeControlBarSchemeInitView *)this;
	if(TheControlBar)
	{
		TheControlBar->switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
		TheControlBar->updateRightHUDImage(self->m_rightHUDImage);
		((Rva0031410CDwordSlot *)TheControlBar)->set( self->m_buildUpClockColor );
		TheControlBar->rva0031AD14(self->m_borderBuildColor, self->m_borderActionColor, self->m_borderUpgradeColor, self->m_borderSystemColor, self->m_bfmeBorderFifthColor);
		((BfmeControlBarSchemeInitBar *)TheControlBar)->m_commandBarBorderColor = self->m_commandBarBorderColor;
		((Rva0031BE07 *)TheControlBar)->rva0031BE58((const ModuleData *)self->m_commandMarkerImage);
		TheControlBar->rva0031B1BC(self->m_toggleButtonUpIn, self->m_toggleButtonUpOn, self->m_toggleButtonUpPushed, self->m_toggleButtonDownIn, self->m_toggleButtonDownOn, self->m_toggleButtonDownPushed, self->m_generalButtonEnable, self->m_generalButtonHightlited);
		((BfmeControlBarSchemeInitBar *)TheControlBar)->m_genArrow = self->m_genArrow;
	}
	GameWindow *win = NULL;
	Coord2D resMultiplier;
	resMultiplier.x = TheDisplay->getWidth()/INT_TO_REAL(self->m_ScreenCreationRes.x) ;
	resMultiplier.y = TheDisplay->getHeight()/INT_TO_REAL(self->m_ScreenCreationRes.y);

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:PopupCommunicator" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage_Rva002C0433(win, self->m_buddyButtonEnable);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, self->m_buddyButtonHightlited);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, self->m_buddyButtonPushed);
		GadgetButtonSetDisabledImage_Rva002C0487(win, self->m_buddyButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_chatUL.x * resMultiplier.x - parX;
			y = self->m_chatUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_chatUL.x * resMultiplier.x;
			y = self->m_chatUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_chatLR.x - self->m_chatUL.x)*resMultiplier.x + COMMAND_BAR_SIZE_OFFSET,(self->m_chatLR.y - self->m_chatUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonIdleWorker" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage_Rva002C0433(win, self->m_idleWorkerButtonEnable);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, self->m_idleWorkerButtonHightlited);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, self->m_idleWorkerButtonPushed);
		GadgetButtonSetDisabledImage_Rva002C0487(win, self->m_idleWorkerButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_workerUL.x * resMultiplier.x - parX;
			y = self->m_workerUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_workerUL.x * resMultiplier.x;
			y = self->m_workerUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );

		win->winSetSize((self->m_workerLR.x - self->m_workerUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_workerLR.y - self->m_workerUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);

	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ExpBarForeground" ) );
	if(win)
	{
		win->winSetEnabledImage(0, self->m_expBarForeground);
	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonOptions" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage_Rva002C0433(win, self->m_optionsButtonEnable);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, self->m_optionsButtonHightlited);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, self->m_optionsButtonPushed);
		GadgetButtonSetDisabledImage_Rva002C0487(win, self->m_optionsButtonDisabled);
		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_optionsUL.x * resMultiplier.x - parX;
			y = self->m_optionsUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_optionsUL.x * resMultiplier.x;
			y = self->m_optionsUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_optionsLR.x - self->m_optionsUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_optionsLR.y - self->m_optionsUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}
	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonPlaceBeacon" ) );
	if(win)
	{
		GadgetButtonSetEnabledImage_Rva002C0433(win, self->m_beaconButtonEnable);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, self->m_beaconButtonHightlited);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, self->m_beaconButtonPushed);
		GadgetButtonSetDisabledImage_Rva002C0487(win, self->m_beaconButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_beaconUL.x * resMultiplier.x - parX;
			y = self->m_beaconUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_beaconUL.x * resMultiplier.x;
			y = self->m_beaconUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_beaconLR.x - self->m_beaconUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_beaconLR.y - self->m_beaconUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:MoneyDisplay" ) );
	if(win)
	{

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_moneyUL.x * resMultiplier.x - parX;
			y = self->m_moneyUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_moneyUL.x * resMultiplier.x;
			y = self->m_moneyUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_moneyLR.x - self->m_moneyUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_moneyLR.y - self->m_moneyUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:PowerWindow" ) );
	if(win)
	{

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_powerBarUL.x * resMultiplier.x - parX;
			y = self->m_powerBarUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_powerBarUL.x * resMultiplier.x;
			y = self->m_powerBarUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_powerBarLR.x - self->m_powerBarUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_powerBarLR.y - self->m_powerBarUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonGeneral" ) );
	if(win)
	{

		GadgetButtonSetEnabledImage_Rva002C0433(win, self->m_generalButtonEnable);
		GadgetButtonSetHiliteImage_Rva002C04DB(win, self->m_generalButtonHightlited);
		GadgetButtonSetHiliteImage123_Rva002C0505(win, self->m_generalButtonPushed);
		GadgetButtonSetDisabledImage_Rva002C0487(win, self->m_generalButtonDisabled);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_generalUL.x * resMultiplier.x - parX;
			y = self->m_generalUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_generalUL.x * resMultiplier.x;
			y = self->m_generalUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_generalLR.x - self->m_generalUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_generalLR.y - self->m_generalUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonLarge" ) );
	if(win)
	{
		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_minMaxUL.x * resMultiplier.x - parX;
			y = self->m_minMaxUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_minMaxUL.x * resMultiplier.x;
			y = self->m_minMaxUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_minMaxLR.x - self->m_minMaxUL.x)*resMultiplier.x + COMMAND_BAR_SIZE_OFFSET,(self->m_minMaxLR.y - self->m_minMaxUL.y)*resMultiplier.y + COMMAND_BAR_SIZE_OFFSET);
	}

	win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:WinUAttack" ) );
	if(win)
	{
		win->winSetEnabledImage(0,self->m_uAttackButtonEnable);
		win->winSetDisabledImage(0,self->m_uAttackButtonHightlited);

		Int x, y;
		GameWindow* parent =win->winGetParent();
		if(parent)
		{
			Int parX, parY;
			parent->winGetScreenPosition(&parX, &parY);
			x = self->m_uAttackUL.x * resMultiplier.x - parX;
			y = self->m_uAttackUL.y * resMultiplier.y - parY;
		}
		else
		{
			x = self->m_uAttackUL.x * resMultiplier.x;
			y = self->m_uAttackUL.y * resMultiplier.y;
		}
		win->winSetPosition(x,y );
		win->winSetSize((self->m_uAttackLR.x - self->m_uAttackUL.x)*resMultiplier.x+ COMMAND_BAR_SIZE_OFFSET,(self->m_uAttackLR.y - self->m_uAttackUL.y)*resMultiplier.y+ COMMAND_BAR_SIZE_OFFSET);
	}
}

