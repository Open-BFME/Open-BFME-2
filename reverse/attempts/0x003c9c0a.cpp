// ?Rva003C9C0AAttack@@YGXPAVParameter@@H@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C9C0AAttack@@YGXPAVParameter@@H@Z @0x003C9C0A 259B
// Evidence: leaf between ScriptActions_doTeamFaceWaypoint and Rva003C9D0D; getUnitNamed Parameter slot then PlayerList mask 0xFFFFF walk then Player rva002AB1DE with single-bit mask and empty clear then Coord3D length closest pick then AI rva0036F4DF with 0 and 1. Globals g_Va009FE16C ThePlayerList g_00BC93FC g_defaultStorage009FEFA4. NOTE row 0x2AB1DE says BitFlags but retail fills slots via BitSet 0x45411 and FixedStorage copy 0x4543D so declared here as BitSet plus FixedStorage for byte shape; callee body identical 28B blobs.
// ?Rva003C9C0AAttack@@YGXPAVParameter@@H@Z present-unmatched
class Parameter; class Object; class Player; class ScriptEngine; class PlayerList;
struct Coord3D { float x; float y; float z; float length() const; };
class BfmeFixedStorage0004543D { char m_bytes[28]; public: __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other); };
struct Rva00045411BitSet { unsigned int m_bits[7]; Rva00045411BitSet(int unused, int bit); __declspec(nothrow) Rva00045411BitSet(const Rva00045411BitSet &other); };
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
class AICommandInterface { public: void rva0036F4DF(Object *target, int value, CommandSourceType cmdSource); };
class AIUpdateInterface { public: unsigned char m_pad[32]; AICommandInterface m_cmd; };
class Object { public: const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); } AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); } };
class ScriptEngine { public: Object *getUnitNamed(Parameter *p); };
class PlayerList { public: Player *getEachPlayerFromMask(int &mask); };
class Player { public: Object *rva002AB1DE(const Coord3D *pos, Rva00045411BitSet setMask, BfmeFixedStorage0004543D clearMask); };
extern ScriptEngine *g_Va009FE16C; extern PlayerList *ThePlayerList; extern float g_00BC93FC; extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;
void __stdcall Rva003C9C0AAttack(Parameter *param, int kindBit)
{
	Object *unit = g_Va009FE16C->getUnitNamed(param);
	if (!unit) return;
	float bestDist = g_00BC93FC;
	Object *best = 0;
	int mask = 0xFFFFF;
	const Coord3D *unitPos = unit->getPosition();
	do {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		Object *cand = player->rva002AB1DE(unitPos, Rva00045411BitSet(0, kindBit), g_defaultStorage009FEFA4);
		if (cand) {
			const Coord3D *candPos = cand->getPosition();
			Coord3D delta; delta.x = candPos->x - unitPos->x; delta.y = candPos->y - unitPos->y; delta.z = candPos->z - unitPos->z;
			float d = delta.length();
			if (!best || d < bestDist) { best = cand; bestDist = d; }
		}
	} while (mask != 0);
	if (!best) return;
	AIUpdateInterface *ai = unit->getAI();
	if (!ai) return;
	ai->m_cmd.rva0036F4DF(best, 0, CMD_FROM_SCRIPT);
}
