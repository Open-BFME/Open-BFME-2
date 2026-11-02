// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Slots 60-62 of Rva005756B6's vtable (101 bytes each, EH, RET 4). Each asks
// TheLivingWorldLogic about the given parent (0x002B3416 / 0x002B3484 /
// 0x002B5A5F, not yet rowed; pinned) and, when it agrees, resets the +0x28
// holder (rowed 0x00575674) to a new 0x10-byte listener object for the outer
// object 4 bytes before this interface -- the rowed constructors 0x005761C6,
// 0x0057605D and 0x00576172 respectively, under the names they are rowed
// as. No WorldBuilder names are matched.
//   ?rva00576388@Rva005756B6@@UAEXPAUParent00575EEA@@@Z  slot 60 (this-4 thunk 0x00576446)
//   ?rva00576105@Rva005756B6@@UAEXPAUParent0057605D@@@Z  slot 61 (also reached by the this-4 thunk 0x0057616A)
//   ?rva00576323@Rva005756B6@@UAEXPAUParent00575E4E@@@Z  slot 62 (this-4 thunk 0x0057644E)

struct Parent0057605D;
struct Parent00575E4E;
struct Parent00575EEA;

#include "../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva0057605D
{
public:
	Rva0057605D(int owner, Parent0057605D *parent);
private:
	unsigned char m_pad00[0x10];
};

class Rva00575E4E
{
public:
	Rva00575E4E(int owner, Parent00575E4E *parent);
private:
	unsigned char m_pad00[0x10];
};

class Rva00575EEA
{
public:
	Rva00575EEA(int owner, Parent00575EEA *parent);
private:
	unsigned char m_pad00[0x10];
};

class Object;

class Rva00575674
{
public:
	void rva00575674(Object *object);
};

class Rva005756B6
{
public:
	virtual void rva00576388(Parent00575EEA *parent);
	virtual void rva00576105(Parent0057605D *parent);
	virtual void rva00576323(Parent00575E4E *parent);
private:
	int outer() { return (int)((char *)this - 4); }

	unsigned char m_pad04[0x28 - 4];
	Rva00575674 m_holder28;					// +0x28
};

void Rva005756B6::rva00576388(Parent00575EEA *parent)
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva002B3416(parent))
		m_holder28.rva00575674((Object *)new Rva00575EEA(outer(), parent));
}

void Rva005756B6::rva00576105(Parent0057605D *parent)
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva002B3484(parent))
		m_holder28.rva00575674((Object *)new Rva0057605D(outer(), parent));
}

void Rva005756B6::rva00576323(Parent00575E4E *parent)
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva002B5A5F(parent))
		m_holder28.rva00575674((Object *)new Rva00575E4E(outer(), parent));
}
