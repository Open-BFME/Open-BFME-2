// cl: /O1 /DNDEBUG /MD
// ?rva002C5D8B@Rva002C5D8B@@QAEXPAVObject@@M@Z @0x002C5D8B 27B: forwards Object+0x38 position plus float plus Object+0x74 to 0x002C5CF7. Evidence pin REL32 at 0x005739CE in AITargetHeuristicBaseDefense slot 1 with 200.0 plus neighbours Rva002C589BXfer Dtor share flags.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_38;
	char m_pad44[0x30];
	int m_74;
};

class Rva002C5D8B
{
public:
	void rva002C5CF7(const struct Coord3D *pos, float radius, int id);
	void rva002C5D8B(Object *obj, float value);
};

void Rva002C5D8B::rva002C5D8B(Object *obj, float value)
{
	rva002C5CF7(&obj->m_38, value, obj->m_74);
}
