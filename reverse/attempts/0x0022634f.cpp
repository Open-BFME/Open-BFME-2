// ?_bfme_updateNetworkAndLogic@GameEngine@@UAEXH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /Os /GX /arch:SSE
//
// GameEngine's vtable slot 38 (RVA 0x0022634F) advances network and logic
// frames.  The body is kept separate from the client-subsystem update because
// it exposes the frame-admission path used by multiplayer simulation: network
// availability is tested first, the network update is bracketed by its prep and
// completion calls, and only then are logic frames consumed.

class WWProfileManager
{
public:
	static void Start_Profile(const char *name);
	static void Stop_Profile(const char *name);
};

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

class GameLogic
{
public:
	__declspec(noinline) unsigned char isGamePaused(void);
	unsigned char Rva002259F3(void);

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
	virtual void update(int phase);

	char m_gap04[0x3c];
	int m_frame;
	unsigned char m_field44;
	char m_gap45[0x58];
	unsigned char m_field9d;
	char m_gap9e[0xa];
	unsigned char m_fielda8;
	char m_gapa9[0x67];
	int m_gameMode;
	char m_gap114[0x10];
	unsigned char m_paused;
};

unsigned char GameLogic::isGamePaused(void)
{
	return m_paused;
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

__declspec(noinline) void Rva00416C69(void);

GameLogic *TheGameLogic;
NetworkInterface *TheNetwork;
class ClientFrameState
{
public:
	char m_gap04[0xc4];
	unsigned char m_advanceFrame;
};
ClientFrameState *TheGameClient;
class AuxiliarySubsystem
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
AuxiliarySubsystem *TheAuxiliarySubsystem;
int FramesPerSecond;
int LogicFramesPerSecond;

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
	int m_clientFramePeriod;
	private:
	void _bfme_updateClientFrameRatio(void);
};

void GameEngine::_bfme_updateNetworkAndLogic(int phase)
{
	WWProfileManager::Start_Profile((const char *)0x00BE7278);
	bool ready;
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
				network->update(TheGameLogic->Rva002259F3());
				TheNetwork->endUpdate();
				ready = true;
				if (!TheNetwork->isPacketRouter())
					TheNetwork->getFramePacingStatus();
			}
		}

		GameLogic *logic = TheGameLogic;
		if (logic != 0 && logic->m_gameMode == 5)
			Rva00416C69();
		switch (ready)
		{
		case 0:
			goto frame_not_ready;
		default:
			break;
		}
	}

	{
		TheGameLogic->update(phase);
		if (phase == 1)
			TheAuxiliarySubsystem->update();

		int clientFrameCounter = FramesPerSecond / LogicFramesPerSecond;
		if (clientFrameCounter < 6)
		{
			int endPhase = (((phase - 1) * clientFrameCounter) / 6 + 1) * 6 / clientFrameCounter + 1;
			for (;;)
			{
				++m_clientFramePeriod;
				GameLogic *logic = TheGameLogic;
				int period = m_clientFramePeriod;
				Rva00225A0C(logic->m_frame * 10 + period - 1);
				TheGameLogic->update(phase);
				++phase;
				if (phase >= endPhase)
					break;
			}
			// The ratio helper is called after the burst loop in retail.
		this->_bfme_updateClientFrameRatio();
		}
	}
	goto profile_done;

frame_not_ready:
	TheGameClient->m_advanceFrame = 0;

profile_done:
	WWProfileManager::Stop_Profile((const char *)0x00BE7278);
}
