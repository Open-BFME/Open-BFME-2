// cl: /MD
// ?Rva0041C9C4Check@@YG_NPAVObject@@PBUCoord3D@@PBVOverridable@@@Z, retail 0x0041C9C4, 52 bytes.
// Evidence: free stdcall 3 args ret 0xC; a3 via rowed Overridable::friend_getFinalOverride 0x00288609 tests bit6 of +0x18; AI global TheAI +0x10 Pathfinder pinned QuickDoesPathExist with obj a1 pos+0x38 coord a2 zero.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	void *m_vptr00;
	Overridable *m_next04;
	unsigned char m_alloc08;
	char m_pad09[0x18 - 0x09];
	unsigned int m_18;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos38;
};

class Pathfinder;

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_path10;
};

extern AI *TheAI;

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *a, const Coord3D *b, int c);
};

bool __stdcall Rva0041C9C4Check(Object *obj, const Coord3D *coord, const Overridable *over)
{
	const Overridable *final = over->friend_getFinalOverride();
	if ((((unsigned char)(final->m_18 >> 6)) & 1) == 0)
		return true;
	Pathfinder *pf = TheAI->m_path10;
	return pf->QuickDoesPathExist(obj, &obj->m_pos38, coord, 0);
}
