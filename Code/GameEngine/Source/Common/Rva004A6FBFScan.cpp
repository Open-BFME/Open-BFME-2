// cl: /DNDEBUG /MD
//
// ?rva004A6FBF@Rva004A6FBF@@QAEMXZ @0x004A6FBF 38B.
// Dozer-side twin of 0x004A9715. Object at this-0x3DC, module data at
// this-0x3E0, float at module+0x70. Same computer-player doubling.

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

class Rva004A6FBF
{
public:
	float rva004A6FBF();
};

float Rva004A6FBF::rva004A6FBF()
{
	Object *obj = *(Object **)((char *)this - 0x3DC);
	Player *player = obj->getControllingPlayer();
	if (player->m_playerType == 1)
	{
		float v = *(float *)(*(char **)((char *)this - 0x3E0) + 0x70);
		return v + v;
	}
	float v = *(float *)(*(char **)((char *)this - 0x3E0) + 0x70);
	return v;
}
