// cl: /DNDEBUG /MD
// GameWinBlockInput -- Zero Hour's GameWindow.cpp input callback that
// swallows input over blocking windows.
//
// ?GameWinBlockInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// retail 0x0031435A, 95 bytes, after winPointInAnyChild 0x003142E1; the
// function lexicon binds it to the name "GameWinBlockInput". Zero Hour's
// body: GWM_CHAR and GWM_MOUSE_POS pass, and GWM_LEFT_UP stops a drag
// selection. BFME 2 differences: setDragSelecting takes no argument (rowed
// 0x0042FA01, called as InGameUIInputModes.cpp does) and setLeftMouseButton
// is out of line (0x00452354, the 10-byte +0x04 byte setter, pinned).
// View::setMouseLock is TacticalView slot 105, InGameUI setSelecting slot
// 43 (as InGameUIInputModes.cpp) and endAreaSelectHint slot 27.

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
class GameWindow;
class GameMessage;

enum { GWM_LEFT_UP = 6, GWM_CHAR = 0x15, GWM_MOUSE_POS = 0x18 };

class SelectionTranslator;
extern SelectionTranslator *TheSelectionTranslator;

class BfmeSelectionTranslator
{
public:
	void setLeftMouseButton( bool state );
	void setDragSelecting( void );
};

class View
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void setMouseLock( bool mouseLocked );	// slot 105
};
extern View *TheTacticalView;

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
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
	virtual void endAreaSelectHint( const GameMessage *msg );	// slot 27
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
	virtual void setSelecting( bool selecting );	// slot 43
};
extern InGameUI *TheInGameUI;

WindowMsgHandledType GameWinBlockInput( GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2 )
{
	if (msg == GWM_CHAR || msg == GWM_MOUSE_POS)
		return MSG_IGNORED;

	//Fix for drag selecting in the control bar
	if (msg == GWM_LEFT_UP)
	{
		//stop drag selecting
		reinterpret_cast<BfmeSelectionTranslator *>( TheSelectionTranslator )->setLeftMouseButton( false );
		reinterpret_cast<BfmeSelectionTranslator *>( TheSelectionTranslator )->setDragSelecting();

		TheTacticalView->setMouseLock( false );
		TheInGameUI->setSelecting( false );
		TheInGameUI->endAreaSelectHint( 0 );
	}

	return MSG_HANDLED;
}
