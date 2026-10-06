// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2's 108-byte frame-admission helper at RVA 0x00225BA6 is the local
// counterpart to BFME1's _bfme_shouldSkipClientFrame.  The GameEngine vtable
// and the caller at 0x00225C59 establish the member ownership; the retail
// body queries the network object's vtable slot +0x58, advances the client
// frame counter at +0x38, and maintains the headroom limit at +0x44.

extern float g_Va00BBB8D8;

// g_Va00DBA2F8: VA 0x00dba2f8 (.data); retail initial bytes 00 00 80 3f (1.0f).
float g_Va00DBA2F8 = 1.0f;

extern class NetworkInterface *TheNetwork;

#define TheNetwork (*(class NetworkInterface **)&TheNetwork)
#define LogicTimeScale g_Va00DBA2F8
#define One g_Va00BBB8D8

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
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual int getFramePacingStatus(void);
};

class GameEngine
{
private:
	bool _bfme_shouldSkipClientFrame(void);
	char m_gap04[0x34];
	int m_clientFramePeriod;
	int m_clientFrameCounter;
	float m_clientFrameRatio;
	char m_gap40[4];
	float m_clientFrameLimit;
};

bool GameEngine::_bfme_shouldSkipClientFrame(void)
{
	NetworkInterface *network = TheNetwork;
	if (network != 0)
	{
		if (!(LogicTimeScale < One))
		{
			if (m_clientFramePeriod != 1)
			{
				if (m_clientFramePeriod > m_clientFrameCounter)
				{
					if (network->getFramePacingStatus() > 1)
						return true;

					if ((float)++m_clientFrameCounter > m_clientFrameLimit)
						m_clientFrameLimit = (float)m_clientFrameCounter;
					return false;
				}
				if (network->getFramePacingStatus() > 3)
				{
					if ((float)m_clientFramePeriod < m_clientFrameLimit)
						m_clientFrameLimit = (float)m_clientFramePeriod;
					return true;
				}
			}
		}
	}

	return false;
}
