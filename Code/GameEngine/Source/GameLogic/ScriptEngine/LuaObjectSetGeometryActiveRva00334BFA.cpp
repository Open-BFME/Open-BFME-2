// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?ObjectSetGeometryActive@@YAHPAUlua_State@@@Z @0x00334BFA 165B: Lua binding setting geometry-active flag via BfmeObjF9::setFlag at Object+0xA8 from name index2 and bool index3. Evidence: pinned name plus rowed gettop Lookup type find tostring StringBase Lookup setFlag release plus TheGameLogic plus siblings 0x00334A3D 0x00334D16 same flags.
#include "ascii_string.h"
struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);
struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);
struct Rva00990210Range;
unsigned Rva00990210Lookup(Rva00990210Range *range, int index);
enum ObjectID { INVALID_OBJECT_ID = 0 };
class GameLogic { public: class Object *findObjectByID(ObjectID id); };
extern GameLogic *TheGameLogic;
class Object;
class BfmeStrF9 { public: void *m_data; };
class BfmeObjF9 { public: void setFlag(const BfmeStrF9 &name, char flag); };
int ObjectSetGeometryActive(lua_State *state)
{
    unsigned id;
    Object *object;
    if (lua_gettop(state) != 3
        || ((id = Rva00990030Lookup((Rva00990030Range *)state, 1)) == 0
            && lua_type(state, 1) != 1)
        || (object = TheGameLogic->findObjectByID((ObjectID)id)) == 0)
        return 0;
    {
        AsciiString name(lua_tostring(state, 2));
        char flag = (Rva00990210Lookup((Rva00990210Range *)state, 3) != 0);
        ((BfmeObjF9 *)((char *)object + 0xA8))->setFlag((const BfmeStrF9 &)name, flag);
    }
    return 0;
}
