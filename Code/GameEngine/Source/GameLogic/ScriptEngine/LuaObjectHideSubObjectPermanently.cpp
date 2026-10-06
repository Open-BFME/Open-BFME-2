// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?ObjectHideSubObjectPermanently@@YAHPAUlua_State@@@Z @0x00334AF3 263B: Lua binding. Evidence: pinned plus donor plus rowed callees plus siblings.
// The hide flag goes to Drawable::rva002724FD as an unsigned char, the pinned
// spelling the sibling ObjectHideSubObject 0x00334A3D also uses (byte sbb/inc
// at the call, no zero-extension).
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
class Drawable
{
public:
    bool rva00278689(const AsciiString &name, bool a2, bool a3);
    void rva002724FD(const AsciiString &name, unsigned char a2, int a3, float a4, float a5);
};
class Object
{
public:
    Drawable *getDrawable() const;
};
class GameLogic
{
public:
    Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
int ObjectHideSubObjectPermanently(lua_State *state)
{
    unsigned id;
    Object *object;
    if (lua_gettop(state) != 3
        || ((id = Rva00990030Lookup((Rva00990030Range *)state, 1)) == 0
            && lua_type(state, 1) != 1)
        || (object = TheGameLogic->findObjectByID((ObjectID)id)) == 0)
        return 0;
    bool notFound;
    {
        AsciiString name(lua_tostring(state, 2));
        notFound = !object->getDrawable()->rva00278689(name, false, true);
    }
    if (!notFound)
        return 0;
    {
        AsciiString name2(lua_tostring(state, 2));
        object->getDrawable()->rva002724FD(name2, (Rva00990210Lookup((Rva00990210Range *)state, 3) == 0), 1, 0.0f, 0.0f);
    }
    return 0;
}
