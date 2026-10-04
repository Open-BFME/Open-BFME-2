// ?Rva0041BA61Get@@YG_NPAVObject@@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /arch:SSE /MD
// ?Rva0041BA61Get@@YG_NPAVObject@@@Z @0x0041BA61 113B. Free stdcall bool
// (Object *): AI global present, obj and its +0x258 AIUpdateInterface
// present and rva00262BEC true, then Pathfinder (AI +0x10) rva002E9871 on
// (pos + (0,0,g_00BC7A54)) >= 0x11. Evidence: callers 0x0041CD08
// 0x0041D0C4 0x0041D658; prev/next Rva0041B94A/Rva0041BB26 share /O1 /MD;
// callees rowed rva00262BEC and pinned rva002E9871; globals g_Va009FF0F8
// (AI *) and g_00BC7A54 (500.0f in Rva00404D70Init).
struct Coord3D
{
	float x;
	float y;
	float z;
};

class AIUpdateInterface
{
public:
	bool rva00262BEC();
};

class Pathfinder
{
public:
	int rva002E9871(const Coord3D *pos);
};

class AI
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;               // +0x10
};

extern AI *g_Va009FF0F8;
extern float g_00BC7A54;

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;                          // +0x38
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai;                // +0x258
};

// ?Rva0041BA61Get@@YG_NPAVObject@@@Z present-unmatched
bool __stdcall Rva0041BA61Get(Object *obj)
{
	if (g_Va009FF0F8 == 0 || obj == 0)
		return false;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return false;
	if (!ai->rva00262BEC())
		return false;
	float x = obj->m_pos.x;
	Pathfinder *pf = g_Va009FF0F8->m_pathfinder;
	Coord3D pos;
	pos.x = x;
	pos.y = obj->m_pos.y;
	pos.z = obj->m_pos.z + g_00BC7A54;
	int r = pf->rva002E9871(&pos);
	if (r < 0x11)
		return false;
	return true;
}
