// cl: /Ireference/shims/bfme2_ascii /MD /GX
// ?Rva003E80DAGet@@YG_NPAVParameter@@0@Z @0x003E80DA 270B evidence: free stdcall bool Parameter pair like sibling 0x003E803D; callees rowed StringBase copy resolveName findPrototype rva00357B82 getPlayerFromMask rva002A7548 rva002D06CA releaseBuffer plus globals g_Va009FE16C TheTeamFactory ThePlayerList g_009FF000 g_Va007C26F0; caller 0x003EBF46
#include "ascii_string.h"

class Parameter
{
public:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class TeamPrototype;
class Player;
class TeamFactory;
class PlayerList;
class Rva002D06CA;
class ScriptEngine;

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &s);
};

class ScriptEngine : public Rva002046C0Owner
{
public:
	int rva00357B82(Parameter *p);
};
extern class ScriptEngine *TheScriptEngine;

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &a, const AsciiString &b);
};
class TeamFactory : public Rva0039FE6COwner
{
};
extern TeamFactory *TheTeamFactory;

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

class Rva002A7461
{
public:
	int rva002A7548(int v);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;
extern float g_Va007C26F0;

struct TeamEntry
{
	int m_00;
	int m_04;
	char m_pad08[8];
	AsciiString m_10;
	int m_14;
};

class TeamPrototype
{
public:
	char m_pad00[0x130];
	TeamEntry m_entries[7];
	int m_1D8;
};

bool __stdcall Rva003E80DAGet(Parameter *p0, Parameter *p1)
{
	AsciiString s1 = p1->m_string;
	AsciiString s2 = TheScriptEngine->resolveName(s1);
	TeamPrototype *proto = TheTeamFactory->findPrototype(s2, s1);
	if (proto == 0)
		return false;
	int mask = TheScriptEngine->rva00357B82(p0);
	if (mask == 0)
		return false;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player == 0)
		return false;
	int thresh = ((Rva002A7461 *)((char *)player + 0x60))->rva002A7548(1);
	int total = 0;
	for (int i = 0; i < proto->m_1D8; ++i) {
		TeamEntry &e = proto->m_entries[i];
		void *found = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&e.m_10);
		if (found != 0) {
			int c = e.m_00 + e.m_04;
			float f = (float)c * g_Va007C26F0;
			int ci = (int)f;
			int v = *(int *)((char *)found + 0x618);
			total += v * ci;
		}
	}
	return total <= thresh;
}
