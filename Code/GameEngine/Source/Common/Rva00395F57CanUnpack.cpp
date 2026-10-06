// cl: /O1 /MD /arch:SSE /Ireference/shims/bfme2_ascii
//
// ?canUnpack@Rva00395F57@@QAE_N_N@Z, retail 0x00395F57, 176 bytes.
// Castle canUnpack with debug-log gate plus readiness check. Donor is BFME1
// Rva0036E420Castle::canUnpack (same CAMP log string, same getControllingPlayer
// plus AsciiString str() pattern, same needInstantBuild/state/timer logic).
// Retail drift: TheGameLogic+0x1B4 (vs 0x1A0) and +0x40 frame (vs +0x3C),
// theLogicRandomLogFile plus fprintf (vs CRCParameterCheck custom log),
// Player name AsciiString at +0x4C (vs +0x1C), override value at +0x64
// (vs +0x20, no getFinalOverride), Castle layout m_object+8/m_currentState
// +0x34/m_needInstantBuild +0x3C/m_timer +0x40 (vs +8/+0x9C/+0xA4/+0xA8),
// final timer check via movss/comiss against BfmeZeroRange. AsciiString via
// shared header (str() gives +8-or-empty shape, literals link).
#include "ascii_string.h"

extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
	void *m_pad00;
	void *m_chain;
	char m_pad08[0x6C];
	int m_id;
};
class Player
{
public:
	char m_pad00[0x4C];
	AsciiString m_name;
};
struct ChainValue
{
	char m_pad00[0x64];
	AsciiString m_value;
};
class GameLogic
{
public:
	char m_pad00[0x40];
	int m_frame;
	char m_pad44[0x170];
	int m_1b4;
};
extern GameLogic *TheGameLogic;
extern "C" void *theLogicRandomLogFile;

class Rva00395F57
{
public:
	bool canUnpack(bool checkTimer);
private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x28];
	int m_currentState;
	char m_pad38[4];
	unsigned char m_needInstantBuild;
	char m_pad3d[3];
	float m_timer;
};
bool Rva00395F57::canUnpack(bool checkTimer)
{
	Object *object = m_object;
	if (*(int *)((char *)TheGameLogic + 0x1B4) > 0)
	{
		if (theLogicRandomLogFile != 0)
		{
			Player *player = object->getControllingPlayer();
			const char *textA = player->m_name.str();
			int id = object->m_id;
			ChainValue *chain = (ChainValue *)object->m_chain;
			const char *textB = chain->m_value.str();
			fprintf(theLogicRandomLogFile,
				"CAMP: Frame %d: Castle %s(%d) %s ::canUnpack() -- m_needInstantBuild=%d, m_currentState=%d, checkTimer=%d, m_timer=%g",
				*(int *)((char *)TheGameLogic + 0x40), textB, id, textA,
				m_needInstantBuild, m_currentState, checkTimer, (double)m_timer);
		}
	}
	if (m_needInstantBuild)
		return false;
	bool stateReady = (m_currentState == 0);
	if (!stateReady)
		goto returnState;
	if (!checkTimer)
		goto returnState;
	if (m_timer > 0.0f)
		return false;
returnState:
	return stateReady;
}
// _theLogicRandomLogFile: the global at VA 0xdfeff0 is ?g_00DFEFF0@@3PAXA.
#pragma comment(linker, "/alternatename:_theLogicRandomLogFile=?g_00DFEFF0@@3PAXA")
