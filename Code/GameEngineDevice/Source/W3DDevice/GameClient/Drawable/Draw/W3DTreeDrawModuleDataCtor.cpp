// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG
//
// W3DTreeDrawModuleData file-unit (retail 0x000CEBBF..0x000CED02): the empty
// virtual base brackets the EH states with no emitted code (its vtable store
// is dead and removed, the derived store leads), the four AsciiString
// members (+08/+0C/+28/+48) build inline as nulls and tear down through the
// folded string dtor (0x36410), and the float/int/bool tail follows the BFME1
// W3DTreeDraw donor with BFME2 Morph/Fade/Tainted fields plus the
// LogicFramesPerSecond*10 sink/morph times. Factory 0x64C0B news 0x64 with
// the ctor as sole caller and pushes the rowed proc 0xCED03.

extern int g_Va00DBA4E4;

#define LogicFramesPerSecond g_Va00DBA4E4

#include "ascii_string.h"

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
	virtual ~W3DTreeDrawModuleData();

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

// ??1W3DTreeDrawModuleData@@UAE@XZ @0xCECA6 (matched): inline empty dtor
// emits the 4-string teardown. Ctor 0xCEBBF lives in
// W3DTreeDrawModuleDataCtorG7.cpp under /G7 for the imul and float scheduling.
W3DTreeDrawModuleData::~W3DTreeDrawModuleData() {}
