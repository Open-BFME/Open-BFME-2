// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003E3F59@ScriptConditions@@IAE_NPAVParameter@@00@Z @0x003E3F59 165B: player-mask sum of Player+0x94 vs threshold with 0..5 op switch
// Evidence: neighbours ScriptConditions_evaluateNamedUnit and evaluateRva003E3FFE same flags; rowed getEachPlayerFromMask 0x002A7BC9 plus pin rva00357B82 plus globals g_Va009FE16C ThePlayerList plus caller 0x003EAD99
class Parameter
{
public:
	unsigned char m_pad[8];
	int m_int;
};

class ScriptEngine
{
public:
	int rva00357B82(Parameter *p);
};

extern class ScriptEngine *TheScriptEngine;

class Player
{
public:
	unsigned char m_pad[0x90];
	int m_90;
	int m_94;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	bool rva003E3F59(Parameter *pValue, Parameter *pOp, Parameter *pPlayerParm);
};

bool ScriptConditions::rva003E3F59(Parameter *pValue, Parameter *pOp, Parameter *pPlayerParm)
{
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	int total = 0;
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			if (&player->m_90) {
				total += player->m_94;
			}
		}
	}
	int op = pOp->m_int;
	bool result = false;
	switch (op) {
	case 0:
		result = pValue->m_int < total;
		break;
	case 1:
		result = pValue->m_int <= total;
		break;
	case 2:
		result = pValue->m_int == total;
		break;
	case 3:
		result = pValue->m_int >= total;
		break;
	case 4:
		result = pValue->m_int > total;
		break;
	case 5:
		result = pValue->m_int != total;
		break;
	default:
		break;
	}
	return result;
}
