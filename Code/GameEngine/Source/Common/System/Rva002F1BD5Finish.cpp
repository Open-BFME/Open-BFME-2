// cl: /MD
//
// ?rva002F1BD5@Rva002F1BD5@@QAEHHPAURva002F1BD5Arg@@HH@Z, retail 0x002F1BD5, 80 bytes.
// Evidence: caller 0x002F203F; callee findObjectByID rowed 0x00049DC5 via global
// TheGameLogic 0x009FE78C; arg tag at +0xC low nibble 4 with payload ptr at +0
// and ObjectID at +0x28; Object +4 -> flag byte at +0x110 bit 2 and +0x74 vs this+4.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

class GameLogic
{
	char pad[0xB4];
	ObjectIdMap m_map;

public:
	Object *findObjectByID(ObjectID id);
};

extern class GameLogic *TheGameLogic;

struct Rva002F1BD5Data
{
	char m_pad[0x28];
	int m_28;
};

struct Rva002F1BD5Arg
{
	Rva002F1BD5Data *m_00;
	char m_04[8];
	int m_0C;
};

struct Rva002F1BD5Mid
{
	unsigned char m_pad[0x110];
	unsigned char m_110;
};

class Object
{
public:
	char m_00[4];
	Rva002F1BD5Mid *m_04;
	char m_08[0x6C];
	int m_74;
};

class Rva002F1BD5
{
	Object *m_00;
	int m_04;

public:
	int rva002F1BD5(int a1, Rva002F1BD5Arg *a2, int a3, int a4);
};

int Rva002F1BD5::rva002F1BD5(int a1, Rva002F1BD5Arg *a2, int a3, int a4)
{
	if ((a2->m_0C & 15) != 4)
		return 0;
	Rva002F1BD5Data *p = a2->m_00;
	int id = p ? p->m_28 : 0;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj == 0)
		return 0;
	if ((obj->m_04->m_110 & 4) == 0)
		return 0;
	if (obj->m_74 != m_04) {
		m_00 = obj;
		return 1;
	}
	return 0;
}
