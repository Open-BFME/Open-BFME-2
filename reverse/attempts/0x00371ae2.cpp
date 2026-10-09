// ?moveVehicleToPos@AIGroup@@QAE_NPBUCoord3D@@W4CommandSourceType@@@Z
// partial score=0.5 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?moveVehicleToPos@AIGroup@@QAE_NPBUCoord3D@@W4CommandSourceType@@@Z,
// retail 0x00371AE2..0x003724B8 (2518 bytes) thiscall RET 8.
//
// Donor: Zero Hour AIGroup.cpp AIGroup::friend_moveVehicleToPos (column
// group pathfind for vehicles; two and three columns); sibling of
// moveInfantryToPos 0x00370795 with the same BFME 2 deltas. BFME 2 deltas read from the bytes: the
// iterators are plain new / ::delete (no MemoryPoolObjectHolder), goal removal
// and the ground goal update go through Object (0x0028AD32 / 0x0028ACEE), the
// minimum-vehicle gate, the controlling-player map clamp and the locomotor
// priority passes are gone (one column-balancing pass, no priority offsets),
// and the ground path is destroyed with delete. Layouts: AIGroup member list
// +0x04 and ground path +0x14; Path first / last node +0x04 / +0x08; PathNode
// next optimized +0x08 and position +0x0C; Object disabled mask +0x1C8,
// template kind-of byte +0x109 (vehicle), AI +0x258 (ground movement test
// at vtable slot 137);
// AI tmp value +0x23C, locomotor set +0x1CC and command interface +0x20.
// WorldBuilder twin 0x00EE20A0 is AIGroup::moveVehicleToPos (assert at
// AIGroup.cpp:1399).

#include "Coord2D.h"
#include "Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef short Short;

void __cdecl free(void *);

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1,
	ITER_SORTED_FAR_TO_NEAR = 2
};

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	vector(const A &a = A()) : _Vector_base<T, A>(a) {}
	~vector()
	{
		if (this->_M_start)
			free(this->_M_start);
	}
	unsigned int size() const { return this->_M_finish - this->_M_start; }
	T &operator[](unsigned int n) { return *(this->_M_start + n); }
	void push_back(const T &x);
	void pop_back() { --this->_M_finish; }
};
}

class Rva0035149F;
class LocomotorSet;
class Object;

class PathNode
{
public:
	PathNode *getNextOptimized() const { return m_nextOpti; }
	const Coord3D *getPosition() const { return &m_pos; }
private:
	char m_pad00[0x08];
	PathNode *m_nextOpti;			// +0x08
	Coord3D m_pos;				// +0x0C
};

class Path
{
public:
	~Path();
	PathNode *getFirstNode() const { return m_path; }
	PathNode *getLastNode() const { return m_pathTail; }
private:
	char m_pad00[0x04];
	PathNode *m_path;			// +0x04
	PathNode *m_pathTail;			// +0x08
};

class AICommandInterface
{
public:
	void rva0036EE16(const Rva0035149F *path, Object *ignoreObject, CommandSourceType cmdSource);	// aiFollowPath
};

#define PAD_VIRTUALS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AIUpdateInterface
{
public:
	PAD_VIRTUALS10(a0) PAD_VIRTUALS10(a1) PAD_VIRTUALS10(a2) PAD_VIRTUALS10(a3) PAD_VIRTUALS10(a4)
	PAD_VIRTUALS10(a5) PAD_VIRTUALS10(a6) PAD_VIRTUALS10(a7) PAD_VIRTUALS10(a8) PAD_VIRTUALS10(a9)
	PAD_VIRTUALS10(b0) PAD_VIRTUALS10(b1) PAD_VIRTUALS10(b2)
	virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6();
	virtual Bool isDoingGroundMovement() const;	// slot 137
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)m_command; }
	Int getTmpValue() const { return m_tmpInt; }
	void setTmpValue(Int val) { m_tmpInt = val; }
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_locomotorSet; }
private:
	char m_pad004[0x20 - 0x04];
	char m_command[0x04];			// +0x20 AICommandInterface
	char m_pad024[0x1CC - 0x24];
	char m_locomotorSet[0x04];		// +0x1CC
	char m_pad1D0[0x23C - 0x1D0];
	Int m_tmpInt;				// +0x23C
};

class ThingTemplate
{
public:
	Int isVehicle() const { return m_kindOf109 & 0x02; }
private:
	char m_pad000[0x109];
	unsigned char m_kindOf109;		// +0x109
	char m_pad10A[3];
	unsigned char m_kindOf10D;		// +0x10D
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Int isDisabledHeld() const { return m_disabled1C8 & 0x08; }
	void rva0028AD32();					// remove the pathfind goal
	void rva0028ACEE(const Coord3D *pos, Int layer);	// update the pathfind goal
private:
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	char m_pad044[0x1C8 - 0x44];
	unsigned char m_disabled1C8;		// +0x1C8
	char m_pad1C9[0x258 - 0x1C9];
	AIUpdateInterface *m_ai;		// +0x258
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, Real data = 0.0f);
	void rva0054B414();			// makeEmpty
	void sort(IterOrderType order);
private:
	char m_pad04[0x3C - 0x04];
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
};
class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;		// +0x10
};
extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip);	// slot 7
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct BfmeListNode
{
	BfmeListNode *m_next;
	BfmeListNode *m_prev;
	Object *m_data;
};

class AIGroup
{
public:
	Bool moveVehicleToPos(const Coord3D *pos, CommandSourceType cmdSource);
	Bool getCenter(Coord3D *center);
private:
	char m_pad00[0x04];
	BfmeListNode *m_memberList;		// +0x04 list header
	char m_pad08[0x14 - 0x08];
	Path *m_groundPath;			// +0x14
};

static __forceinline void copyCoord(Coord3D &c, const Coord3D *p)
{
	c.x = p->x;
	c.y = p->y;
	c.z = p->z;
}

#define PATHFIND_CELL_SIZE_F 10.0f
#define PATH_DIAMETER_IN_CELLS 4

Bool AIGroup::moveVehicleToPos(const Coord3D *pos, CommandSourceType cmdSource)
{
	if (m_groundPath == 0) return false;

	Real dx, dy;
	Coord3D center;
	if (!getCenter(&center)) return false;

	if (!m_groundPath)
		return false;

	Int numColumns = 2;

	// Get the start & end vectors for the path.
	Coord3D startPoint;
	copyCoord(startPoint, m_groundPath->getFirstNode()->getPosition());
	Real farEnoughSqr = (PATH_DIAMETER_IN_CELLS * PATHFIND_CELL_SIZE_F) * (PATH_DIAMETER_IN_CELLS * PATHFIND_CELL_SIZE_F);
	PathNode *startNode = 0;
	PathNode *node;
	for (node = m_groundPath->getFirstNode(); node; node = node->getNextOptimized())
	{
		Real dx = node->getPosition()->x - startPoint.x;
		Real dy = node->getPosition()->y - startPoint.y;
		if (dx * dx + dy * dy > farEnoughSqr)
		{
			startNode = node;
			break;
		}
	}
	Coord3D endPoint;
	copyCoord(endPoint, m_groundPath->getLastNode()->getPosition());
	PathNode *endNode = 0;
	for (node = m_groundPath->getFirstNode(); node; node = node->getNextOptimized())
	{
		Real dx = node->getPosition()->x - endPoint.x;
		Real dy = node->getPosition()->y - endPoint.y;
		if (dx * dx + dy * dy > farEnoughSqr)
			endNode = node;
	}
	if (endNode == m_groundPath->getFirstNode())
		endNode = 0;
	if (startNode == 0 || endNode == 0)
	{
		delete m_groundPath;
		m_groundPath = 0;
		return false;
	}

	Coord2D startVector;
	startVector.x = startNode->getPosition()->x - startPoint.x;
	startVector.y = startNode->getPosition()->y - startPoint.y;
	startVector.normalize();

	Coord2D endVector;
	endVector.x = endPoint.x - endNode->getPosition()->x;
	endVector.y = endPoint.y - endNode->getPosition()->y;
	endVector.normalize();

	Coord2D startVectorNormal;
	startVectorNormal.x = -startVector.y;
	startVectorNormal.y = startVector.x;
	startVectorNormal.normalize();

	Coord2D endVectorNormal;
	endVectorNormal.x = -endVector.y;
	endVectorNormal.y = endVector.x;
	endVectorNormal.normalize();

	Int unitsToPath = 0;
	Bool useEndVector = false;
	// Move.
	SimpleObjectIterator *iter = new SimpleObjectIterator;
	SimpleObjectIterator *iter2 = new SimpleObjectIterator;
	BfmeListNode *i;
	for (i = m_memberList->m_next; i != m_memberList; i = i->m_next)
	{
		if (i->m_data->isDisabledHeld())
			continue; // don't bother telling the occupants to move.
		if (!i->m_data->getTemplate()->isVehicle())
			continue;
		if (i->m_data->getAI() == 0)
			continue;
		if (!i->m_data->getAI()->isDoingGroundMovement())
			continue;
		Coord3D unitPos;
		copyCoord(unitPos, i->m_data->getPosition());
		i->m_data->rva0028AD32();
		Real dx, dy;
		dx = unitPos.x - center.x;
		dy = unitPos.y - center.y;
		// Sort by the dot product of normal.
		iter->insert(i->m_data, dx * startVectorNormal.x + dy * startVectorNormal.y);
		unitsToPath++;

		// If units are closer to the end vector than the start vector, use the end vector.
		Real distToEndSqr;
		Real distToStartSqr;
		dx = unitPos.x - endPoint.x;
		dy = unitPos.y - endPoint.y;
		distToEndSqr = dx * dx + dy * dy;
		dx = unitPos.x - startPoint.x;
		dy = unitPos.y - startPoint.y;
		distToStartSqr = dx * dx + dy * dy;
		if (distToStartSqr > distToEndSqr)
			useEndVector = true;
	}

	Object *theUnit;
	if (useEndVector)
	{
		// resort unsing the end vector.
		startVector = endVector;
		startVectorNormal = endVectorNormal;
		for (theUnit = iter->first(); theUnit; theUnit = iter->next())
			iter2->insert(theUnit);
		iter->rva0054B414();
		for (theUnit = iter2->first(); theUnit; theUnit = iter2->next())
		{
			Coord3D unitPos;
			copyCoord(unitPos, theUnit->getPosition());
			dx = unitPos.x - center.x;
			dy = unitPos.y - center.y;
			// Sort by the dot product of normal.
			iter->insert(theUnit, dx * startVectorNormal.x + dy * startVectorNormal.y);
		}
		iter2->rva0054B414();
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);
	Int curIndex = 0;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		AIUpdateInterface *ai = theUnit->getAI();
		Int divisor = ((unitsToPath + 1) / numColumns);
		if (divisor < 1) divisor = 1;
		Int columnDelta = 1 - (curIndex / divisor);  // 0, 1 from left to right across column.
		if (columnDelta == 0) columnDelta = -1;
		divisor = ((unitsToPath + 1) / 3);
		if (divisor < 1) divisor = 1;
		Int threeColumnDelta = (curIndex / divisor);  // 0, 1, 2 from left to right across column.
		threeColumnDelta = 1 - threeColumnDelta; // 1, 0, -1
		if (threeColumnDelta < -1) threeColumnDelta = -1;
		if (unitsToPath < 5)
			threeColumnDelta = columnDelta;

		ai->setTmpValue((threeColumnDelta << 16) | (columnDelta & 0x00ffff));
		// Sort next pass by the dot product of start vector.
		Real dx, dy;
		dx = theUnit->getPosition()->x - center.x;
		dy = theUnit->getPosition()->y - center.y;
		iter2->insert(theUnit, dx * startVector.x + dy * startVector.y);
		curIndex++;
	}

	iter2->sort(ITER_SORTED_FAR_TO_NEAR);
	// Even out columns.
	Int column2[3] = {0, 0, 0};
	Int column3[3] = {0, 0, 0};
	for (theUnit = iter2->first(); theUnit; theUnit = iter2->next())
	{
		AIUpdateInterface *ai = theUnit->getAI();
		Int tmp = ai->getTmpValue();
		Int threeColumnDelta = tmp >> 16;
		Int columnDelta = (Short)(tmp & 0xFFFF);

		Int i;
		Int min2 = 10000;
		Int min3 = 10000;
		for (i = 0; i < 3; i += 2) if (column2[i] < min2) min2 = column2[i];
		for (i = 0; i < 3; i++) if (column3[i] < min3) min3 = column3[i];
		Int delta = 10000;
		Int best = -1;
		for (i = 0; i < 3; i += 2)
		{
			if (column2[i] == min2)
			{
				Int dx = (1 + columnDelta) - i;
				if (dx < 0) dx = -dx;
				if (dx < delta)
				{
					delta = dx;
					best = i;
				}
			}
		}
		if (best >= 0)
		{
			column2[best]++;
			columnDelta = best - 1;
		}

		delta = 10000;
		best = -1;
		for (i = 0; i < 3; i++)
		{
			if (column3[i] == min3)
			{
				Int dx = (1 + threeColumnDelta) - i;
				if (dx < 0) dx = -dx;
				if (dx < delta)
				{
					delta = dx;
					best = i;
				}
			}
		}
		if (best >= 0)
		{
			column3[best]++;
			threeColumnDelta = best - 1;
		}

		if (unitsToPath < 5)
			threeColumnDelta = columnDelta;
		ai->setTmpValue((threeColumnDelta << 16) | (columnDelta & 0x00ffff));
	}

	curIndex = 0;
	Int columnFactor[5] = {0, 0, 0, 0, 0};
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, pos);
	for (theUnit = iter2->first(); theUnit; theUnit = iter2->next())
	{
		AIUpdateInterface *ai = theUnit->getAI();
		Int tmp = ai->getTmpValue();
		Int threeColumnDelta = tmp >> 16;
		Int columnDelta = (Short)(tmp & 0xFFFF);
		Int factor = columnFactor[threeColumnDelta + 2];
		columnFactor[threeColumnDelta + 2] = factor + 1;

		_STL::vector<Coord3D> path;
		PathNode *node = startNode;
		PathNode *previousNode = m_groundPath->getFirstNode();
		Coord3D prevPos;
		copyCoord(prevPos, theUnit->getPosition());
		while (node)
		{
			Coord3D dest;
			copyCoord(dest, node->getPosition());
			PathNode *tmpNode;
			PathNode *nextNode = 0;
			for (tmpNode = node->getNextOptimized(); tmpNode; tmpNode = tmpNode->getNextOptimized())
			{
				Real dx = tmpNode->getPosition()->x - dest.x;
				Real dy = tmpNode->getPosition()->y - dest.y;
				if (dx * dx + dy * dy > farEnoughSqr)
				{
					nextNode = tmpNode;
					break;
				}
			}
			if (nextNode == 0) break;
			Coord2D cornerVectorNormal;
			cornerVectorNormal.y = nextNode->getPosition()->x - previousNode->getPosition()->x;
			cornerVectorNormal.x = -(nextNode->getPosition()->y - previousNode->getPosition()->y);
			cornerVectorNormal.normalize();

			Coord2D cornerVector;
			cornerVector.x = nextNode->getPosition()->x - previousNode->getPosition()->x;
			cornerVector.y = nextNode->getPosition()->y - previousNode->getPosition()->y;

			Real offset = PATHFIND_CELL_SIZE_F * 1.5f;
			dest.x += offset * columnDelta * cornerVectorNormal.x;
			dest.y += offset * columnDelta * cornerVectorNormal.y;
			if (factor & 1)
			{
				dest.x += 0.5f * PATHFIND_CELL_SIZE_F * cornerVectorNormal.x;
				dest.y += 0.5f * PATHFIND_CELL_SIZE_F * cornerVectorNormal.y;
			}
			else
			{
				dest.x -= 0.5f * PATHFIND_CELL_SIZE_F * cornerVectorNormal.x;
				dest.y -= 0.5f * PATHFIND_CELL_SIZE_F * cornerVectorNormal.y;
			}

			Coord2D curVector;
			curVector.x = dest.x - prevPos.x;
			curVector.y = dest.y - prevPos.y;

			// Make sure that this dest is going in the same direction as the vector.
			if (cornerVector.x * curVector.x + cornerVector.y * curVector.y > 0)
			{
				path.push_back(dest);
				prevPos = dest;
			}
			node = node->getNextOptimized();

			for (tmpNode = previousNode->getNextOptimized(); tmpNode && tmpNode != node; tmpNode = tmpNode->getNextOptimized())
			{
				Real dx = tmpNode->getPosition()->x - node->getPosition()->x;
				Real dy = tmpNode->getPosition()->y - node->getPosition()->y;
				if (dx * dx + dy * dy > farEnoughSqr)
					previousNode = tmpNode;
			}
		}

		Coord3D dest;
		copyCoord(dest, pos);
		if (threeColumnDelta < -3) threeColumnDelta = -3;
		if (threeColumnDelta > 3) threeColumnDelta = 3;
		Real offset = PATHFIND_CELL_SIZE_F * 3.2f;
		if (unitsToPath < 5)
			offset = PATHFIND_CELL_SIZE_F * 1.5f;
		dest.x += offset * threeColumnDelta * endVectorNormal.x;
		dest.y += offset * threeColumnDelta * endVectorNormal.y;
		if (factor & 1)
		{
			dest.x += PATHFIND_CELL_SIZE_F * endVectorNormal.x;
			dest.y += PATHFIND_CELL_SIZE_F * endVectorNormal.y;
		}

		dest.x -= factor * offset * endVector.x;
		dest.y -= factor * offset * endVector.y;
		dest.z = TheTerrainLogic->getLayerHeight(dest.x, dest.y, layer, 0, true);

		while (path.size() > 0)
		{
			Coord2D curVector;
			prevPos = path[path.size() - 1];
			curVector.x = dest.x - prevPos.x;
			curVector.y = dest.y - prevPos.y;

			// Make sure that this dest is going in the same direction as the vector.
			if (endVector.x * curVector.x + endVector.y * curVector.y <= 0)
				path.pop_back();
			else
				break;
		}
		TheAI->pathfinder()->adjustDestination(theUnit, ai->getLocomotorSet(), &dest, 0);
		theUnit->rva0028ACEE(&dest, LAYER_GROUND);
		path.push_back(dest);
		ai->getCommandInterface()->rva0036EE16((const Rva0035149F *)&path, 0, cmdSource);
	}
	::delete iter;
	::delete iter2;
	return true;
}
