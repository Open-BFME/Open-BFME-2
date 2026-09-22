// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
//
// W3DTreeDrawModuleData file-unit (retail 0x000CEBBF..0x000CED02): the empty
// virtual base brackets the EH states with no emitted code (its vtable store
// is dead and removed, the derived store leads), the four AsciiString
// members (+08/+0C/+28/+48) build inline as nulls and tear down through the
// folded string dtor (0x36410), and the float/int/bool tail follows the BFME1
// W3DTreeDraw donor with BFME2 Morph/Fade/Tainted fields plus the
// LogicFramesPerSecond*10 sink/morph times. Factory 0x64C0B news 0x64 with
// the ctor as sole caller and pushes the rowed proc 0xCED03.

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void clear();

private:
	void *m_data;
};

class W3DTreeDrawModuleDataBase
{
public:
	W3DTreeDrawModuleDataBase() {}
	virtual ~W3DTreeDrawModuleDataBase() {}
};

class W3DTreeDrawModuleData : public W3DTreeDrawModuleDataBase
{
public:
	W3DTreeDrawModuleData();
	virtual ~W3DTreeDrawModuleData() {}

private:
	unsigned int m_unused04;
	AsciiString m_modelName; // +08
	AsciiString m_textureName; // +0C
	unsigned int m_framesToMoveOutward; // +10
	unsigned int m_framesToMoveInward; // +14
	float m_maxOutwardMovement; // +18
	float m_darkening; // +1C
	void *m_toppleFX; // +20
	void *m_bounceFX; // +24
	AsciiString m_stumpName; // +28
	float m_initialVelocityPercent; // +2C
	float m_initialAccelPercent; // +30
	float m_bounceVelocityPercent; // +34
	float m_minimumToppleSpeed; // +38
	bool m_killWhenToppled; // +3C
	bool m_doTopple; // +3D
	unsigned char m_pad3e[2];
	unsigned int m_sinkFrames; // +40
	float m_sinkDistance; // +44
	AsciiString m_morphTree; // +48
	unsigned int m_morphTime; // +4C
	const void *m_morphFX; // +50
	bool m_taintedTree; // +54
	unsigned char m_pad55[3];
	unsigned int m_fadeRate; // +58
	unsigned int m_fadeTarget; // +5C
	float m_fadeDistance; // +60
};

// ??0W3DTreeDrawModuleData@@QAE@XZ @0xCEBBF (in progress; walls: imul vs
// lea/shl for the *10 times plus float/bool scheduling)
W3DTreeDrawModuleData::W3DTreeDrawModuleData() :
	m_framesToMoveOutward(1),
	m_framesToMoveInward(1),
	m_maxOutwardMovement(1.0f),
	m_darkening(0.0f)
{
	m_toppleFX = 0;
	m_bounceFX = 0;
	m_stumpName.clear();
	m_doTopple = false;
	m_killWhenToppled = true;
	m_sinkFrames = LogicFramesPerSecond * 10;
	m_sinkDistance = 20.0f;
	m_morphTime = LogicFramesPerSecond * 10;
	m_morphFX = 0;
	m_taintedTree = false;
	m_initialVelocityPercent = 0.2f;
	m_initialAccelPercent = 0.01f;
	m_bounceVelocityPercent = 0.3f;
	m_minimumToppleSpeed = 0.5f;
	m_fadeRate = 5;
	m_fadeTarget = 105;
	m_fadeDistance = 40.0f;
}
