// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0046D4BD@HordeContain@@UAEXPAUCoord3D@@0@Z, retail 0x0046D4BD (630
// bytes). Slot 100 of the interface HordeContain carries at +0x11C (vtables
// 0x00C44C58 HordeContain; 0x00C45838 and 0x00C46930 for the derived
// hordes), compiled with that subobject's this as the rowed slots in
// HordeContainIface11CSlots.cpp are. Writes the average position of the
// horde to the first argument:
// every contained Object (the list the +0x20 contain interface's slot 70
// fills) and every Object keyed in the +0x170 ID tree (rowed
// GameLogic::findObjectByID 0x00049DC5) that has a Drawable (rowed
// Thing::getDrawable 0x005508E2) adds its transform translation (pinned
// Drawable::getTransformMatrix 0x0027628E) and counts; any member with status
// bit 6 set makes the result follow the terrain: z from TheTerrainLogic's
// slot 7 height at the rowed getLayerForDestination 0x002802FE layer (with
// the optional normal); without it the normal alone is still filled.
// WorldBuilder twin 0x010CAF30 (callgraph evidence) has the same loops; its
// contained-list loop also skips a null entry without advancing. The result
// is stored field by field (retail movss per field) and eax still holds the
// out pointer at exit, so a Coord3D return by value is not ruled out.

#include <list>
#include <set>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

extern GameLogic *TheGameLogic;

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	Vector4 Row[3];
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	// Status bit 6 of the bit flags at +0x94.
	Bool testStatusBit6() const { return (m_status94 >> 6) & 1; }
private:
	unsigned char m_pad000[0x94];
	UnsignedInt m_status94; // +0x94
};

template <int N> class HordeAverageSlots : public HordeAverageSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class HordeAverageSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class TerrainLogic : public HordeAverageSlots<7>
{
public:
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip) = 0; // slot 7
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};

class ModuleData;

class HordeContainModuleBase
{
public:
	virtual ~HordeContainModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};

// The +0x20 contain interface: slot 70 fills the contained-items pair.
class ContainModuleInterface : public HordeAverageSlots<70>
{
public:
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
};

class HordeContainBase : public HordeContainModuleBase, public ContainModuleInterface
{
private:
	unsigned char m_pad024[0x11C - 0x24];
};

// The +0x11C interface (only the slot defined here is declared).
class HordeContainIface11C
{
public:
	virtual void rva0046D4BD(Coord3D *out, Coord3D *normal) = 0;
};

class HordeContain : public HordeContainBase, public HordeContainIface11C
{
public:
	virtual void rva0046D4BD(Coord3D *out, Coord3D *normal);
private:
	unsigned char m_pad120[0x170 - 0x120];
	_STL::set<int> m_170; // +0x170 (Object IDs)
};

void HordeContain::rva0046D4BD(Coord3D *out, Coord3D *normal)
{
	UnsignedInt count = 0;
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	Coord3D sum;
	sum.z = 0.0f;
	sum.y = 0.0f;
	sum.x = 0.0f;
	Coord3D tmp;
	Coord3D pos;
	Bool onTerrain = false;
	while (it != p.m04->end())
	{
		Object *obj = *it;
		if (obj == 0)
			continue;
		Drawable *draw = obj->getDrawable();
		if (draw)
		{
			const Matrix3D *mtx = draw->getTransformMatrix();
			tmp.x = mtx->Row[0].W;
			tmp.y = mtx->Row[1].W;
			tmp.z = mtx->Row[2].W;
			pos = tmp;
			sum.x += pos.x;
			sum.y += pos.y;
			sum.z += pos.z;
			++count;
		}
		onTerrain = onTerrain || obj->testStatusBit6();
		++it;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			Drawable *draw = obj->getDrawable();
			if (draw)
			{
				const Matrix3D *mtx = draw->getTransformMatrix();
				tmp.x = mtx->Row[0].W;
				tmp.y = mtx->Row[1].W;
				tmp.z = mtx->Row[2].W;
				pos = tmp;
				sum.x += pos.x;
				sum.y += pos.y;
				sum.z += pos.z;
				++count;
			}
			onTerrain = onTerrain || obj->testStatusBit6();
		}
	}
	Real scale = 1.0f / (Real)count;
	sum.x *= scale;
	sum.y *= scale;
	sum.z *= scale;
	if (onTerrain)
	{
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, &sum);
		sum.z = TheTerrainLogic->getLayerHeight(sum.x, sum.y, layer, normal, true);
	}
	else if (normal)
	{
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, &sum);
		TheTerrainLogic->getLayerHeight(sum.x, sum.y, layer, normal, true);
	}
	out->x = sum.x;
	out->y = sum.y;
	out->z = sum.z;
}
