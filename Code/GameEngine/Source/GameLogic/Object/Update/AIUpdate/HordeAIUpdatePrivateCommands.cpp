// cl: /DNDEBUG /MD
//
// HordeAIUpdate's private-command overrides. Slots 13 and 23 of the vftable
// 0x00C505F8 whose slot-2 name getter returns "HordeAIUpdate" replace the
// AIUpdateInterface entries every other AI module keeps there (the rowed
// privateMoveToPosition 0x0026B487 and bfmePrivateCommand42 0x0026D56C);
// each runs the base command only when the owner has the provider at
// Object+0x250 answering slot 31 (the rowed Object::rva0028C197).
//
// ?privateMoveToPosition@HordeAIUpdate@@MAEXPBUCoord3D@@MW4CommandSourceType@@@Z, retail 0x0049A93B, 56 bytes.
// Slot 13 (HordeWorkerAIUpdate 0x00C508C8 inherits it); the provider test
// is inlined.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// The command values are numbered only; the porcupine-formation tables below
// list every value from 0 through 0x53 except 0x52, which (as in the
// WorldBuilder build) falls to the DEBUG_CRASH default.
enum AICommandType
{
	AICMD_NUM_TESTED = 0x54
};

struct AICommandParms
{
	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
};

class Rva0028C197Provider
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual void *s31();
};

class Object
{
public:
	__forceinline void *providedEntry() const
	{
		Rva0028C197Provider *provider = m_250;
		return provider ? provider->s31() : 0;
	}
private:
	char m_unrecovered00[0x250];
	Rva0028C197Provider *m_250;
};

class AIUpdateInterface
{
protected:
	virtual void privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource);
	Object *getObject() const { return m_object; }
private:
	void *m_moduleData;
	Object *m_object;
};

class HordeAIUpdate : public AIUpdateInterface
{
public:
	bool commandCancelsPorcupineFormation(const AICommandParms *parms);
	bool porcupineFormationIgnoresCommand(const AICommandParms *parms);
protected:
	virtual void privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource);
};

// ?privateMoveToPosition@HordeAIUpdate@@MAEXPBUCoord3D@@MW4CommandSourceType@@@Z @0x0049A93B
void HordeAIUpdate::privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource)
{
	if (getObject()->providedEntry())
		AIUpdateInterface::privateMoveToPosition(pos, speed, cmdSource);
}

// ?commandCancelsPorcupineFormation@HordeAIUpdate@@QAE_NPBUAICommandParms@@@Z @0x0049A6DC
// WorldBuilder names it (HordeAIUpdate.cpp, DEBUG_CRASH default at line 476);
// its only caller is the unrowed command dispatcher at 0x0049A9A9.
bool HordeAIUpdate::commandCancelsPorcupineFormation(const AICommandParms *parms)
{
	switch (parms->m_cmd)
	{
	case 46:
	case 48:
		return true;

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 83:
		return parms->m_cmdSource == CMD_FROM_PLAYER;

	case 5:
	case 21:
	case 22:
	case 38:
	case 39:
	case 45:
	case 47:
	case 59:
	case 67:
		return false;

	default:
		return false;
	}
}

// WorldBuilder names it; called from the same dispatcher at 0x0049A9A9.
bool HordeAIUpdate::porcupineFormationIgnoresCommand(const AICommandParms *parms)
{
	switch (parms->m_cmd)
	{
	case 38:
	case 39:
	case 45:
	case 47:
	case 59:
	case 67:
		return true;

	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 46:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 83:
		return true;

	case 11:
		return false;

	default:
		return false;
	}
}
