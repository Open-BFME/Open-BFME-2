// cl: /MD /GX
//
// ActiveBody's slot 22 (0x004BF9ED, vftable 0x0085B038 and ten more body
// vftables that inherit it): when the module data's +0x4C radius is positive,
// optionally draw it (TheGlobalData +0xE9C: TheTerrainLogic's ground height
// under the object, then TheTacticalView slot 12 with colour 0xFFFF8000), then
// hand every alive object other than this one passing the relationship-1
// filter within that radius to 0x0028EC68 (1, the object, 10).
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	void rva0028EC68(int a, void *b, int c);	// 0x0028EC68
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
};
extern TerrainLogic *TheTerrainLogic;

class View
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void rvaSlot12(const Coord3D *pos, float radius, int color);
};
extern View *TheTacticalView;

class GlobalData
{
public:
	char m_pad000[0xE9C];
	bool m_E9C;		// +0xE9C
};
extern class GlobalData *TheWritableGlobalData;

class ActiveBodyModuleData
{
public:
	char m_pad00[0x4C];
	float m_4C;		// +0x4C the radius
};

class ActiveBody
{
public:
	virtual void rva004BF9ED();
protected:
	const ActiveBodyModuleData *getActiveBodyModuleData() const
	{
		return (const ActiveBodyModuleData *)m_moduleData;
	}
	Object *getObject() const { return m_object; }
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

void ActiveBody::rva004BF9ED()
{
	const ActiveBodyModuleData *data = getActiveBodyModuleData();
	if (data->m_4C <= 0.0f)
		return;
	{
		Object *obj = getObject();
		if (TheWritableGlobalData->m_E9C) {
			Coord3D pos;
			pos.x = obj->getPosition()->x;
			pos.y = obj->getPosition()->y;
			pos.z = obj->getPosition()->z;
			pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
			TheTacticalView->rvaSlot12(&pos, data->m_4C, 0xFFFF8000);
		}
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), data->m_4C, 0,
			Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 0);
		Object *other;
		while ((other = hits.next()) != 0)
			other->rva0028EC68(1, obj, 10);
	}
}
