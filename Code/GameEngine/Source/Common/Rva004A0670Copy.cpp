// cl: /O1 /DNDEBUG /MD
//
// ?rva004A0670@Rva004A0670@@QAEXPAVObject@@0@Z @0x004A0670 153B ret 8.
// Copy src pose onto dst, or the owner at this-0x18 when src is null.
// Then face dst at its position and consume one count.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(float angle);
};

// Zero Hour's AICommandInterface takes a CommandSourceType (row 0x0026C26D).
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI, CMD_FROM_DOZER, CMD_DEFAULT_SWITCH_WEAPON };
class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	int rva0028B511() const;
	void rva0028B4CE(PathfindLayerEnum layer);
	char m_beforePos[0x38];
	Coord3D m_pos;
	float m_orient;
	char m_beforeAi[0x210];
	AIUpdateInterface *m_ai;
};

struct Rva004A0670Holder
{
	char m_pad[0x20];
	int m_20;
};

class Rva004A0670
{
public:
	void rva004A0670(Object *dst, Object *src);
	char m_pad[4];
	int m_4;
	char m_pad2[0x14];
	int m_count;
};

void Rva004A0670::rva004A0670(Object *dst, Object *src)
{
	if (src != 0)
	{
		float orient = src->m_orient;
		int layer = src->rva0028B511();
		((Thing *)dst)->setPosition(&src->m_pos);
		((Thing *)dst)->setOrientation(orient);
		dst->rva0028B4CE((PathfindLayerEnum)layer);
	}
	else
	{
		((Thing *)dst)->setPosition(&(*(Object **)((char *)this - 0x18))->m_pos);
		((Thing *)dst)->setOrientation((*(Object **)((char *)this - 0x18))->m_orient);
	}
	if (dst->m_ai != 0)
		dst->m_ai->m_commands.aiMoveToPosition(&dst->m_pos, (CommandSourceType)2);
	m_4 = (*(Rva004A0670Holder **)((char *)this - 0x1C))->m_20;
	if (m_count != 0)
		--m_count;
}
