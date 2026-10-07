// cl: /MD /EHsc /DNDEBUG
// ?bfmeQueryRallyOverride@@YAPAVObject@@PAV1@PBUCoord3D@@@Z @0x004A0403 280B
// Evidence: BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateQueryRallyOverride.cpp; caller ?setRallyPoint@QueueProductionExitUpdate@@UAEXPBUCoord3D@@@Z at 0x004A051B; vtable slot 0x34 on +0x250 contain; ExitInterface slot06 at +0x18; BitSet bits 0x76/0x87.

extern "C" void *memset(void *dst, int val, unsigned size);

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int b1, int b2);
	unsigned m_bits[7];
};

class Rva00045411BitSet
{
public:
	Rva00045411BitSet(int a, int b, int c);
	Rva00045411BitSet(const Rva00045411BitSet &other);
private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void rva00362192(Rva00045411BitSet first, BfmeFixedStorage0004543D second);
private:
	unsigned m_record;
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(class Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class Object;
class ExitInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual bool slot06() = 0;
};

class ContainView
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual bool s13() = 0;
};

enum Relationship
{
	REL_0 = 0,
	REL_1 = 1,
	REL_2 = 2
};

class Object
{
public:
	ExitInterface *getObjectExitInterface() const;
	Relationship getRelationship(const Object *other) const;
	char m_pad38[0x38];
	float m_x;
	float m_y;
	char m_pad250[0x250 - 0x38 - 8];
	ContainView *m_contain250;
};

class Rva000CBA20Point
{
public:
	float x;
	float y;
};

#include "../../../../Common/RTS/XYDistanceCallView.h"


class Rva00265150RJFilter : public Rva000421C8
{
public:
	Rva00265150RJFilter(void *subobject, void *extra, bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual bool allow(Object *obj);
	void *m_subobject;
	void *m_extra;
	bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc, Rva000421C8 *filter);
};
extern PartitionManager *ThePartitionManager;

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

Object *bfmeQueryRallyOverride(Object *obj, const Coord3D *pos)
{
	if (obj == 0 || pos == 0)
		return 0;
	Rva003623E5Member handle;
	handle.rva00362192(Rva00045411BitSet(0, 0x76, 0x87), g_defaultStorage009FEFA4);
	Rva00265150RJFilter filter(&handle, 0, true);
	Object *found = ThePartitionManager->getClosestObject(pos, 1.0f, 1, &filter);
	if (found)
	{
		ContainView *contain = found->m_contain250;
		if (contain && contain->s13() &&
			obj->getObjectExitInterface() != 0 &&
			obj->getObjectExitInterface()->slot06() &&
			obj->getRelationship(found) == REL_2 &&
			225.0f > ((Rva000CBA20 *)found)->distSq((const Rva000CBA20Point *)pos))
			return found;
	}
	return 0;
}
