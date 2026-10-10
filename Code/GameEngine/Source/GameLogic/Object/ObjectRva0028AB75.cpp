// cl: /DNDEBUG /MD
// ?rva0028AB75@Object@@QAEX_N@Z @0x0028AB75 135B lane=unlock
// Evidence: rowed makeDirty 0x0073A0F0 init 0x007584C0 rva00625840 0x00625840 rva002710EC 0x002710EC shim 0x002E718A 0x002E7178 twins 0x00287C39 0x00287C21; globals TheAI and g_00DFEC68; callers 0x00298970 0x004992BB; prev 0x0028AB4E next 0x0028AC34 Object TUs /O1 /DNDEBUG /MD.
class PartitionData
{
public:
	void makeDirty();
};

class Rva009A2350
{
public:
	void init();
};

class Rva00625840
{
public:
	void rva00625840();
};

class Rva002710EC
{
public:
	void rva002710EC();
};

class Object;

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *object);
	void AddObjectToPathfindMap(Object *object);
};

struct Rva00287C21Other
{
	unsigned char m_pad[0x49C];
	int m_49C;
};

class FireLogicSystem
{
public:
	void RegisterObject(Rva00287C21Other *o);
	void UnregisterObject(Rva00287C21Other *o);
};

class AI
{
public:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

extern FireLogicSystem *g_00DFEC68;

class Object
{
public:
	void rva0028AB75(bool flag);
private:
	char _00[0x84];
	Rva002710EC *m_84;
	char _88[0x49C - 0x88];
	int m_49C;
	char _4A0[0x4C4 - 0x4A0];
	PartitionData *m_4C4;
	Rva00625840 *m_4C8;
	Rva009A2350 *m_4CC;
};

void Object::rva0028AB75(bool flag)
{
	if (m_4C4 != 0)
		m_4C4->makeDirty();
	if (m_4CC != 0)
		m_4CC->init();
	if (m_4C8 != 0)
		m_4C8->rva00625840();
	Rva002710EC *q = m_84;
	if (q != 0)
		q->rva002710EC();
	if (flag)
	{
		TheAI->m_pathfinder->RemoveObjectFromPathfindMap(this);
		TheAI->m_pathfinder->AddObjectToPathfindMap(this);
	}
	if (m_49C < 0)
		return;
	g_00DFEC68->UnregisterObject((Rva00287C21Other *)this);
	g_00DFEC68->RegisterObject((Rva00287C21Other *)this);
}
