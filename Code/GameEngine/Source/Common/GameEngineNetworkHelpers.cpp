// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /Os /GX /arch:SSE
//
// Small dependencies recovered while tracing GameEngine's network/logic
// advancement method.  The pause byte getter and Debug frame-report wrapper
// are independently exact; the larger slot-38 body is banked separately until
// its remaining MSVC block-layout differences are resolved.

class GameLogic
{
public:
	__declspec(noinline) unsigned char isGamePaused(void);
};

unsigned char GameLogic::isGamePaused(void)
{
	return *(const unsigned char *)((const char *)this + 0x124);
}

class Debug
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual void slot6c(void);
	virtual void slot70(void);
	virtual void slot74(void);
	virtual void slot78(void);
	virtual void slot7c(void);
	virtual void slot80(void);
	virtual void slot84(void);
	virtual void slot88(void);
	virtual void slot8c(void);
	virtual void Rva00225A0C(int value);
};

Debug *theDebug;

__declspec(noinline) void Rva00225A0C(int value)
{
	theDebug->Rva00225A0C(value);
}
