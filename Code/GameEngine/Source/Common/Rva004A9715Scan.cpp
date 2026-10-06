// cl: /DNDEBUG /MD
//
// ?rva004A9715@Rva004A9715@@QAEMXZ @0x004A9715 38B.
// Supply-side this. Object at this-0x3E0, module data at this-0x3E4, float
// at module+0x7C. Computer players (player+0x5C == 1) get the value doubled
// with fadd st, st. getControllingPlayer is the rowed 18B Object method.

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

class Rva004A9715
{
public:
	float rva004A9715();
};

float Rva004A9715::rva004A9715()
{
	Object *obj = *(Object **)((char *)this - 0x3E0);
	Player *player = obj->getControllingPlayer();
	if (player->m_playerType == 1)
	{
		float v = *(float *)(*(char **)((char *)this - 0x3E4) + 0x7C);
		return v + v;
	}
	float v = *(float *)(*(char **)((char *)this - 0x3E4) + 0x7C);
	return v;
}
