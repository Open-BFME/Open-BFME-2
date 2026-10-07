// cl: -MD -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// 120B sibling of bfmeHelper6320 (BFME2 retail 0x003351C2):
// the same two-lua-argument lookup shape; only the
// pulsed emotion index differs (6 here, not 4).
// Address-derived name pending the real Lua-bound function name.

struct Rva00990030Value
{
	unsigned char m_padC[0xC];
	unsigned m_value;
};

struct Rva00990030Record
{
	unsigned m_type;
	unsigned m_4;
	Rva00990030Value *m_value;
	unsigned m_C;
};

struct Rva00990030Range
{
	Rva00990030Record *m_begin;
	unsigned char m_pad10[0x10 - 4];
	Rva00990030Record *m_end;
};

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);

class Object
{
public:
	void rva0028EC68(int index, void *source, int delay);
};

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

int bfmeHelper6280(lua_State *state)
{
	void *value = (void *)Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *record = TheGameLogic->findObjectByID((ObjectID)(int)value);
	if (!record)
		return 0;

	value = (void *)Rva00990030Lookup((Rva00990030Range *)state, 2);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *source = TheGameLogic->findObjectByID((ObjectID)(int)value);
	if (!source)
		return 0;

	record->rva0028EC68(6, source, 1);
	return 0;
}
