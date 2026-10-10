// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// ReplaceSelfUpgrade::upgradeImplementation; retail [004B74CB 004B790B), 1088B.
// Identity: the rowed ctor 004B7045 installs UpgradeMux table 00858AC8;
// this is its slot10 override, with the same secondary receiver as check004B7110.
// WorldBuilder twin0123FE70 establishes replacement-template iteration, teardown,
// buildObjectNow, delay propagation and container reassignment. ZH upgrade-module
// purpose and the matched BFME2 check provide reference guidance; native bytes
// independently establish data118, object ID74/name88/next8C/delay324 and filters.
// Facing uses the matched sibling's copy, t=-y, y=x, x=t idiom. Inline object,
// pathfinder and ID accessors preserve native argument-evaluation register homes.
// All calls use existing owners; no new pins or shared-header changes.

#include "ascii_string.h"
#include "Coord3D.h"
#include <math.h>
#include "../../../Common/PartitionRangeQueryCallView.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	vector(const vector &other);
	~vector();
	unsigned int size() const { return _M_finish - _M_start; }
	T &operator[](unsigned int n) { return *(_M_start + n); }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}
typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > AsciiStringVector;

enum DamageType { DAMAGE_NONE = 0 };
enum DeathType { DEATH_NONE = 0 };
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class ThingTemplate
{
public:
	int isKindOf28() const { return m_kindOf[0] & 0x10000000; }
	const class GeometryInfo &getTemplateGeometryInfo() const { return *(const GeometryInfo *)m_geometry; }
	Real getB0() const { return m_b0; }
	Real getC8() const { return m_c8; }
private:
	unsigned char m_pad000[0xA0];
	unsigned char m_geometry[0x10];			// +0xA0 GeometryInfo
	Real m_b0;					// +0xB0
	unsigned char m_padB4[0xC8 - 0xB4];
	Real m_c8;					// +0xC8
	unsigned char m_padCC[0x118 - 0xCC];
	unsigned int m_kindOf[7];			// +0x118
};

class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
	const Coord3D *getUnitDirectionVector2D() const;
};

class Object : public Thing
{
public:
	void rva0028BAC0(); // 0x0028BAC0
	Bool testStatus(ObjectStatusTypes bit) const;
	void leaveGroup();
 unsigned getID() const { return id; }
	class Player *getControllingPlayer() const;
	void *rva0028BD17() const;
	void teleportTo(const Coord3D *, Bool);
	void kill(enum DamageType, enum DeathType);
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;					// +0x38
	Real m_orientation;				// +0x44
	unsigned char pad48[0x74-0x48];
public:
	unsigned int id;
	unsigned char pad78[0x88-0x78];
	AsciiString name;
	Object *next;
	unsigned char pad90[0x324-0x90];
	float delay;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// slot 6
};
extern TerrainLogic *TheTerrainLogic;

class GlobalData
{
public:
	unsigned char m_pad000[0xA70];
	Real m_a70;					// +0xA70
};
extern GlobalData *TheWritableGlobalData;

// Footprint shapes of a GeometryInfo (0x24-byte records at +0x2C..+0x30).
struct Rva0087E900Coord
{
	Real x;
	Real y;
	Real z;
};
class Rva0087E900Shape
{
public:
	void rva006BE220(const Rva0087E900Coord *pos, Real angle, Rva0087E900Coord *result);
};
struct BfmeShapeE15;
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int index);
};
class GeometryInfo
{
public:
	Int getShapeCount() const { return (m_shapesLast - m_shapesFirst) / 0x24; }
	BfmeShapeE15 *getShape(Int index) const { return ((BfmeObjE15 *)this)->bfmeAtE15(index); }
private:
	unsigned char m_pad00[0x2C];
	const char *m_shapesFirst;			// +0x2C
	const char *m_shapesLast;			// +0x30
};

class BfmeFixedStorage0004543D			// KindOfMaskType
{
public:
	BfmeFixedStorage0004543D(Int init, Int bit1, Int bit2);
	BfmeFixedStorage0004543D(Int init, Int bit);
private:
	unsigned int m_bits[7];
};

// The (init, bit) ctor 0x00045411 is rowed as Rva00045411BitSet; a no-member
// view of the mask type so the temporary is built through that row.
struct Rva00045411BitSet : BfmeFixedStorage0004543D { Rva00045411BitSet(Int init, Int bit); };

// The partition filter base (ctor 0x000421C8, vtable 0x007C26E0).
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

class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &kindOf);
	virtual bool allow(Object *obj);
private:
	unsigned int m_kindOf[7];
};

class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool flag) throw();
	virtual bool allow(Object *obj);
private:
	Coord3D m_pos;
	const GeometryInfo *m_geom;
	Real m_angle;
	Bool m_flag;
};

extern PartitionManager *ThePartitionManager;

class Rva00406F9C;

class ReplaceSelfUpgradeModuleData
{
public:
	unsigned char m_pad000[0x118];
	AsciiStringVector m_replaceWith;		// +0x118
};

class Rva004B7110ModuleBase
{
public:
	virtual void b0();
 Object *getObject() const { return m_object; }
protected:
	const ReplaceSelfUpgradeModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};

class Rva004B7110UpgradeInterface
{
public:
	virtual void u0();
};

class UpgradeMux
{
public:
	virtual void m0();
	virtual void m1();
	virtual Bool rva004CE2B0(Rva00406F9C *mask);	// slot 2
	virtual void m3();virtual void m4();virtual void m5();virtual void m6();virtual void m7();virtual void m8();
	virtual void upgradeImplementation();
};

class ReplaceSelfUpgrade : public Rva004B7110ModuleBase, public Rva004B7110UpgradeInterface, public UpgradeMux
{
public:
	virtual Bool rva004CE2B0(Rva00406F9C *mask);
	virtual void upgradeImplementation();
};

static __forceinline void copyCoord(Coord3D &c, const Coord3D *a)
{
	c.x = a->x;
	c.y = a->y;
	c.z = a->z;
}

static __forceinline void scaleCoord(Coord3D &c, Real scale)
{
	c.x *= scale;
	c.y *= scale;
	c.z *= scale;
}

static __forceinline void addCoord(Coord3D &c, const Coord3D *a)
{
	c.x += a->x;
	c.y += a->y;
	c.z += a->z;
}

template<int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva0004584D : public Rva000421C8 {
public:
 Rva0004584D(const BfmeFixedStorage0004543D &, const BfmeFixedStorage0004543D &);
 virtual ~Rva0004584D() {}
 virtual bool allow(Object *);
 BfmeFixedStorage0004543D m_accept,m_reject;
};
class Drawable {public:void setDrawableHidden(bool hidden);};
class Rva0026F0F0 {public:void *rva0026F0F0(const void *);};
class UpgradeCenter;extern UpgradeCenter *TheUpgradeCenter;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Pathfinder {public:void RemoveObjectFromPathfindMap(Object *);};
class AI {public:char pad[0x10];Pathfinder *pathfinder; Pathfinder *getPathfinder() { return pathfinder; }};extern AI *TheAI;
template<int N>class ReplaceSlots:public ReplaceSlots<N-1>{public:virtual void slot(char(*)[N]);};template<>class ReplaceSlots<0>{};
class BuildAssistant:public ReplaceSlots<14>{public:virtual Object *buildObjectNow(Object *,const ThingTemplate *,const Coord3D *,Real,class Player *);};extern BuildAssistant *TheBuildAssistant;
class ReplaceContain:public ReplaceSlots<18>{public:virtual void addToContain(Object *);virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual Bool isContained(unsigned);};
struct ReplaceInfo {char pad[0x34];Int delay;};
void ReplaceSelfUpgrade::upgradeImplementation()
{
 const ReplaceSelfUpgradeModuleData *data=m_moduleData;
 if(!data)return;
 AsciiStringVector names=data->m_replaceWith;
 Int count=names.size();if(!count)return;
 Coord3D pos;copyCoord(pos,m_object->getPosition());Real angle=m_object->getOrientation();
 AsciiString name=m_object->name;
 m_object->rva0028BAC0();
 m_object->leaveGroup();
 if(m_object->getDrawable())m_object->getDrawable()->setDrawableHidden(true);
 if(TheAI)TheAI->getPathfinder()->RemoveObjectFromPathfindMap(getObject());
 TheGameLogic->destroyObject(m_object);
 Real totalLength=0;
 for(Int i=0;i<count;++i){const ThingTemplate *tmpl=TheThingFactory->findTemplate(names[i]);if(!tmpl)return;totalLength+=tmpl->getC8();}
 Coord3D perp;const Coord3D *direction=m_object->getUnitDirectionVector2D();
 copyCoord(perp,direction);Real t=-perp.y;perp.y=perp.x;perp.x=t;
 Coord3D cur;copyCoord(cur,&perp);scaleCoord(cur,totalLength);const Object *owner=m_object;addCoord(cur,owner->getPosition());
 for(Int j=0;j<count;++j){
  const ThingTemplate *tmpl=TheThingFactory->findTemplate(names[j]);
  Coord3D step;copyCoord(step,&perp);scaleCoord(step,-tmpl->getC8());addCoord(cur,&step);
  BfmeWideResult iter=ThePartitionManager->iterateObjectsInRange(&pos,tmpl->getB0()*0.5f,1,Rva00261603Filter(pos,tmpl->getTemplateGeometryInfo(),angle,true).link(&Rva0004584D(Rva00045411BitSet(0,0xBD),*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)),0);
  for(Object *other=iter.next();other;other=iter.next())other->kill((DamageType)8,(DeathType)0);
  Object *constructor=m_object;
  Object *created=TheBuildAssistant->buildObjectNow(constructor,tmpl,&cur,angle,constructor->getControllingPlayer());
  if(!created)return;
  created->teleportTo(&cur,false);created->name=name;addCoord(cur,&step);
  ReplaceInfo *info=(ReplaceInfo*)((Rva0026F0F0*)TheUpgradeCenter)->rva0026F0F0((const char*)data+8);
  if(info)created->delay=(float)info->delay;
  unsigned oldID=m_object->id;
  for(Object *other=TheGameLogic->getFirstObject();other;other=other->next){
   const unsigned char *kind=(const unsigned char*)other->getTemplate();
   if(!(kind[0x11b]&0x10) && !(kind[0x11a]&0x40) && !(kind[0x11f]&0x20))continue;
   ReplaceContain *contain=(ReplaceContain*)other->rva0028BD17();
   if(contain && contain->isContained(oldID))contain->addToContain(created);
   ReplaceContain *oldContain=(ReplaceContain*)m_object->rva0028BD17();
   if(oldContain && oldContain->isContained(other->getID())){
    ReplaceContain *newContain=(ReplaceContain*)created->rva0028BD17();if(newContain)newContain->addToContain(other);
   }
  }
 }
}
