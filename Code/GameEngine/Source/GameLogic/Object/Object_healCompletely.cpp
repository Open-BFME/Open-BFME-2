// cl: /DNDEBUG /MD
//
// ?healCompletely@Object@@QAEXXZ @0x0028FF9E (18B).
// Object::healCompletely(): restores max health by attempting healing with
// the shared HUGE amount at 0x007FBC84 and a null source. Retail shape is
// fld of the shared float plus push 0 plus placeholder push plus fstp plus
// call to the rowed attemptHealing at 0x0028FE55 plus ret. BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp:2279
// proves the name and body; BFME2 delta is the shared float address.
// Caller at 0x0039DCFD iterates a Team member list and heals each entry.

extern float g_Va00BFBC84;
// g_Va00BFBC84: matched references place it at VA 0xbfbc84 (retail .rdata value 999999.0f).
float g_Va00BFBC84 = 999999.0f;

class Object
{
public:
	void attemptHealing(float amount, const Object *source);
	void healCompletely();
};

void Object::healCompletely()
{
	attemptHealing(g_Va00BFBC84, 0);
}
