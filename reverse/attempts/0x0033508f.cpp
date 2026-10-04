// ?Rva0033508F@@YAHPAUlua_State@@@Z
// partial score=0.87 date=2026-10-04
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE
//
// ?Rva0033508F@@YAHPAUlua_State@@@Z @ 0x0033508F (187B).
// Lua binding: Lookup ID, findObjectByID, attr 4, random gate 0x85A,
// AI state 0x2D check, push bool via bfmeGo1039E, nil on miss.
// Evidence: callees rowed Lookup, lua_type, lua_pushnil, findObjectByID,
// rva0028C149, GetGameLogicRandomValue, getCurrentStateID, bfmeGo1039E;
// TheGameLogic, string literal.

struct lua_State;
extern "C" int lua_type(lua_State *L, int idx);
extern "C" void lua_pushnil(lua_State *L);

struct Rva00990030Range;
unsigned int Rva00990030Lookup(Rva00990030Range *r, int i);

class GameLogic;
class Object;
enum ObjectID
{
	INVALID_ID = 0
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	bool rva0028C149(int attr, float *value, int arg);
public:
	char m_pad00[0x258];
	void *m_ai258;
};
class AIUpdateInterface
{
public:
	int getCurrentStateID() const;
};
int GetGameLogicRandomValue(int a, int b, char *name, int line);
struct BfmeQ1039;
void bfmeGo1039E(const BfmeQ1039 *q, int v);

// ?Rva0033508F@@YAHPAUlua_State@@@Z present-unmatched
int __cdecl Rva0033508F(lua_State *L)
{
	unsigned int id = Rva00990030Lookup((Rva00990030Range *)L, 1);
	if (!id)
	{
		if (lua_type(L, 1) != 1)
		{
			lua_pushnil(L);
			return 0;
		}
	}
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (!obj)
	{
		lua_pushnil(L);
		return 1;
	}
	float v = 0.0f;
	bool doPush = true;
	if (obj->rva0028C149(4, &v, 0))
	{
		int r = GetGameLogicRandomValue(0, 1, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp", 0x85A);
		if ((float)r <= v)
			doPush = false;
	}
	{
		AIUpdateInterface *ai = (AIUpdateInterface *)obj->m_ai258;
		if (ai)
		{
			if (ai->getCurrentStateID() == 0x2D)
				doPush = 0;
		}
	}
	bfmeGo1039E((const BfmeQ1039 *)L, doPush);
	return 1;
}
