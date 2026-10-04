// cl: /O1 /MD /GX /arch:SSE
//
// WallUpgradeUpdate members that query the partition manager through a
// filter chain (layout as WallUpgradeUpdateBehaviorCtor.cpp: +0x08 the
// object; +0x28 an ObjectID).
//
//   0x004AB415  while +0x28 is unset, the closest object within 200 of ours
//               (2D centre) that passes the 0x002614DF filter and has kinds
//               7 and 60; its id goes to +0x28 (caller 0x004AB4F2)
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
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

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// A KindOfMaskType with two kinds set (0x0006EE7A).
struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int bit1, int bit2);
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00C07190, allow 0x002614DF.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class WallUpgradeUpdate
{
public:
	void rva004AB415();
private:
	const void *m_vtable;
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	char m_pad0C[0x28 - 0x0C];
	ObjectID m_28;			// +0x28
};

void WallUpgradeUpdate::rva004AB415()
{
	if (m_28 != INVALID_ID)
		return;
	Object *obj = m_object;
	const Coord3D *pos = &obj->m_pos;
	Object *found = ThePartitionManager->getClosestObject(pos, 200.0f, 1,
		Rva002614DFFilter(obj).link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 7, 60),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)));
	if (found)
		m_28 = found->m_id;
}
