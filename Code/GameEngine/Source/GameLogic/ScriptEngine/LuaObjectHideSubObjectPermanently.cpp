// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class ThingTemplate;
class Player;
class Drawable;
class SpecialPowerModuleInterface;
enum SpecialPowerType { SPECIAL_POWER_TYPE_UNKNOWN = 0 };
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
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
#include "../../Common/GameLogicObjectLookupView.h"
class Drawable
{
public:
	DrawableID getID() const;
	bool rva00278689(const AsciiString &name, bool a, bool b);
	void rva002724FD(const AsciiString &name, int show, int permanent, float c, float d);
 void rva002724FD(const AsciiString &name, unsigned char show, int permanent, float c, float d);

	__forceinline unsigned char testModelCondition(int bit) const
	{
		return (m_conditionState[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}

	char m_pad000[0xFC];
	Object *m_object;	// +0xFC
	char m_pad100[0x258 - 0x100];
	unsigned int m_conditionState[10];	// +0x258, tested with BitFlags<304> bits
};
class UpgradeTemplate;
class Object
{
public:
	bool rva0028C149(int,float*,int);
 void rva00293077(const void *a);
 void removeUpgrade(const UpgradeTemplate *u);
 void rva0028EBDA(bool flag);
 void rva00291080(bool flag);
 float rva002C97E8(const Coord3D *a, const Coord3D *b) const;
 float GetRelativeAngle(const Coord3D *pos) const;
 Drawable *getDrawable() const;
public:
	__forceinline unsigned char testStatus(int bit) const
	{
		return (m_status[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0;
	}
public:
	char m_pad00[0x04];
public:
	ThingTemplate *m_template;
public:
	char m_pad08[0x38 - 0x08];
 Coord3D m_position; // +0x38
 char m_pad44[0x74 - 0x44];
 ObjectID m_id; // +0x74
 char m_pad78[0x94 - 0x78];
public:
	unsigned int m_status[2];
public:
	char m_pad9C[0x258 - 0x9C];
public:
	void *m_ai258;
public:
	char m_pad25C[0x38C - 0x25C];
 Coord3D m_targetPos; // +0x38C
public:
	int m_currentTargetID;
public:
	void rva0028EC68(int index, void *source, int delay);
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
public:
	Player *getControllingPlayer() const;
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
        object->getDrawable()->rva002724FD(name2, (unsigned char)(Rva00990210Lookup((Rva00990210Range *)state, 3) == 0), 1, 0.0f, 0.0f);
    }
    return 0;
}
