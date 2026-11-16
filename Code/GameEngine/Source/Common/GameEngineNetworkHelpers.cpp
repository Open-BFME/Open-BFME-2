// cl: /O1 /Ob1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /arch:SSE
//
// Small dependencies recovered while tracing GameEngine's network/logic
// advancement method.  The pause byte getter and Debug frame-report wrapper
// are independently exact; the larger slot-38 body is banked separately until
// its remaining MSVC block-layout differences are resolved.

#include "../../../Libraries/Source/profile/profile.h"

// 0x002259F3 is rowed as this const int getter (Disp8ByteFieldGetters.cpp);
// retail consumes only its low byte (movzx eax,al), as the bool it is.
#include "../../Include/Common/Rva002259F3.h"

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

#include "debug.h"

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

__declspec(noinline) void Rva00225A0C(int value)
{
	theDebug->ExecuteFrameCommands(value);
}

// The slot-38 frame advance (RVA 0x0022634F, 356 bytes with its RET 4): it
// opens the "logic" profile range, and on the first phase decides from
// the pause byte and the network object's admission queries whether a frame
// may run; if not it clears the client's advance flag, otherwise it updates the
// logic, the living-world logic on the first phase, and runs the extra client
// phases that fit between two logic frames before refreshing the frame ratio.
#include "../../Include/GameNetwork/NetworkInterfaceClass.h"

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

#include "../../Include/Common/GameEngine.h"

void GameEngine::_bfme_updateNetworkAndLogic(int phase)
{
	Profile::StartRange("logic");
	bool ready = true;
	if (phase == 1)
	{
		ready = !TheGameLogic->isGamePaused();
		if (TheNetwork != 0)
		{
			int frameAdvanceCount = TheNetwork->slot21();
			if (frameAdvanceCount <= 0 && TheGameLogic->m_field9d == 0)
			{
				ready = false;
			}
			else
			{
				TheNetwork->slot49();
				NetworkInterface *network = TheNetwork;
				network->slot16((unsigned char)((Rva002259F3 *)TheGameLogic)->rva002259F3());
				TheNetwork->slot50();
				ready = true;
				if (!TheNetwork->slot43())
					TheNetwork->slot22();
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
				++m_34;
				GameLogic *logic = TheGameLogic;
				int period = m_34;
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
