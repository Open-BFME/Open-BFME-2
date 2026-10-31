// cl: /O1 /Ob1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /arch:SSE
//
// Small dependencies recovered while tracing GameEngine's network/logic
// advancement method.  The pause byte getter and Debug frame-report wrapper
// are independently exact; the larger slot-38 body is banked separately until
// its remaining MSVC block-layout differences are resolved.

#include "../../../Libraries/Source/profile/profile.h"

// 0x002259F3 is rowed as this const int getter (Disp8ByteFieldGetters.cpp);
// retail consumes only its low byte (movzx eax,al), as the bool it is.
class Rva002259F3
{
public:
	int rva002259F3() const;
};

class GameLogic
{
public:
	__declspec(noinline) unsigned char isGamePaused(void);
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void update(int phase);				// slot 13

	char m_gap04[0x3c];
	int m_frame;								// +0x40
	char m_gap44[0x59];
	unsigned char m_field9d;					// +0x9D
	char m_gap9e[0x72];
	int m_gameMode;								// +0x110
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

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

__declspec(noinline) void Rva00225A0C(int value)
{
	theDebug->Rva00225A0C(value);
}

// The slot-38 frame advance (RVA 0x0022634F, 356 bytes with its RET 4): it
// opens the "logic" profile range, and on the first phase decides from
// the pause byte and the network object's admission queries whether a frame
// may run; if not it clears the client's advance flag, otherwise it updates the
// logic, the living-world logic on the first phase, and runs the extra client
// phases that fit between two logic frames before refreshing the frame ratio.
class NetworkInterface
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void update(int allow);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual int getFrameAdvanceCount(void);
	virtual int getFramePacingStatus(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual bool isPacketRouter(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void slot47(void);
	virtual void slot48(void);
	virtual void beginUpdate(void);
	virtual void endUpdate(void);
};

class GameClient;
class LivingWorldLogic;

// The client's frame state, read at its advance flag.
class GameClientAdvanceView
{
public:
	char m_gap00[0xc8];
	unsigned char m_advanceFrame;				// +0xC8
};

// The living-world logic's per-frame update, vtable slot 10.
class LivingWorldLogicUpdateView
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void update(void);
};

extern GameLogic *TheGameLogic;
extern NetworkInterface *TheNetwork;
extern GameClient *TheGameClient;
extern LivingWorldLogic *TheLivingWorldLogic;
extern int BfmeClientFramesPerSecond;
extern int BfmeLogicFramesPerSecond;

void HandleBuddyResponses(void);

class GameEngine
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void _bfme_updateNetworkAndLogic(int phase);

	char m_gap04[0x30];
	int m_clientFramePeriod;					// +0x34

private:
	void updateClientFrameRatio(void);	// 0x00225D78
};

void GameEngine::_bfme_updateNetworkAndLogic(int phase)
{
	Profile::StartRange("logic");
	bool ready = true;
	if (phase == 1)
	{
		ready = !TheGameLogic->isGamePaused();
		if (TheNetwork != 0)
		{
			int frameAdvanceCount = TheNetwork->getFrameAdvanceCount();
			if (frameAdvanceCount <= 0 && TheGameLogic->m_field9d == 0)
			{
				ready = false;
			}
			else
			{
				TheNetwork->beginUpdate();
				NetworkInterface *network = TheNetwork;
				network->update((unsigned char)((Rva002259F3 *)TheGameLogic)->rva002259F3());
				TheNetwork->endUpdate();
				ready = true;
				if (!TheNetwork->isPacketRouter())
					TheNetwork->getFramePacingStatus();
			}
		}

		GameLogic *logic = TheGameLogic;
		if (logic != 0 && logic->m_gameMode == 5)
			HandleBuddyResponses();
	}

	if (ready)
	{
		TheGameLogic->update(phase);
		if (phase == 1)
			((LivingWorldLogicUpdateView *)TheLivingWorldLogic)->update();

		int clientFrameCounter = BfmeClientFramesPerSecond / BfmeLogicFramesPerSecond;
		if (clientFrameCounter < 6)
		{
			int endPhase = (((phase - 1) * clientFrameCounter) / 6 + 1) * 6 / clientFrameCounter + 1;
			while (++phase < endPhase)
			{
				++m_clientFramePeriod;
				GameLogic *logic = TheGameLogic;
				int period = m_clientFramePeriod;
				Rva00225A0C(logic->m_frame * 10 + period - 1);
				TheGameLogic->update(phase);
			}
			updateClientFrameRatio();
		}
	}
	else
	{
		((GameClientAdvanceView *)TheGameClient)->m_advanceFrame = 0;
	}
	Profile::StopRange("logic");
}
