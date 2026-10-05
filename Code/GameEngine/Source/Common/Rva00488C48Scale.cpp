// cl: /O1 /DNDEBUG /MD
//
// ?rva00488C48@Rva00488C48@@QAEMXZ @0x00488C48 72B.
// Object at this-0x3DC, module float at this-0x3E0 + 0x6C. A computer player
// (type 1) scales that float by TheAI inner+0x88. Both calls stay.

extern class AI *TheAI;

struct Rva00488C48Inner
{
	char m_pad[0x88];
	float m_scale;
};

struct Rva00488C48Outer
{
	char m_pad[0x18];
	Rva00488C48Inner *m_inner;
};

class Player
{
public:
	char m_pad[0x5C];
	int m_playerType;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva00488C48
{
public:
	float rva00488C48();
};

float Rva00488C48::rva00488C48()
{
	Object *volatile *slot = (Object *volatile *)((char *)this - 0x3DC);
	if ((*slot)->getControllingPlayer() != 0 && (*slot)->getControllingPlayer()->m_playerType == 1)
	{
		float v = *(float *)(*(char **)((char *)this - 0x3E0) + 0x6C);
		Rva00488C48Outer *outer = *(Rva00488C48Outer **)&TheAI;
		return v * outer->m_inner->m_scale;
	}
	float v = *(float *)(*(char **)((char *)this - 0x3E0) + 0x6C);
	return v;
}
