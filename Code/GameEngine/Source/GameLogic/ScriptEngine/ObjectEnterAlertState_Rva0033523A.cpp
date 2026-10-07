// cl: -MD -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine

// The registration table at 0x002EC990 binds the name ObjectEnterAlertState to
// the ILT thunk at 0x0002F24D, which jumps here to 0x002E63C0: the body pushed
// by lua_pushcclosure is the one the next lua_setglobal names. The callback
// resolves one object and pulses emotion index 9 with source 0 and delay 1.

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);

class Object
{
public:
	void rva0028EC68(int index, void *source,
		int delay);
};

// Native lookup 0x00049DC5 takes the same 32-bit ObjectID enum as its
// verified provider; only the declaration changes, not the ID representation.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID value);
};

extern GameLogic *TheGameLogic;

int ObjectEnterAlertState(lua_State *state)
{
	void *value = (void *)Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *object = TheGameLogic->findObjectByID((ObjectID)(int)value);
	if (object)
		object->rva0028EC68(9, 0, 1);
	return 0;
}
