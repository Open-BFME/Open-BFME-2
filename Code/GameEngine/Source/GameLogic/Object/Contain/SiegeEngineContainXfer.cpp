// cl: /Ob2 /ICode/Libraries/Include /ICode/GameEngine/Source/Common /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?xfer@SiegeEngineContain@@MAEXPAVXfer@@@Z, retail 0x0047C322, 464 bytes.
// Slot 3 of ??_7SiegeEngineContain 0x00C470F8 (slot 0 the rowed ??_G
// 0x0047C2D6). The rowed TransportContain::xfer 0x00466DBC first, then the
// light-CRC out and Version(1,1). The rider list at +0x11C: saving writes
// the count kept at +0x120 and each rider's ObjectID (Object+0x74);
// loading first destroys any riders still listed (rowed list<int>::erase
// 0x00438539, GameLogic::destroyObject 0x00242C09, list clear 0x0023DAA5),
// then reads the count and queues the ids in the list at +0x134 (rowed
// push_back 0x0005548F). Then the bool at +0x124 and the map<int,int> at
// +0x128 as ObjectID/int pairs (rowed operator[] 0x0028932C on load).
// Layout per the rowed SiegeEngineContainDtor view; member names not
// recovered.

#define COORD3D_VIEW_DTOR
#include "Lib/Coord3DCtorView.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <list>
// Destroying an element through the inline empty ~Coord3D otherwise emits a
// ??_GCoord3D copy that skips retail's out-of-line destructor call (0x00225B7F).
namespace _STL { template <> inline void _Destroy<Coord3D>(Coord3D *) {} }

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>
namespace _STL {
}


namespace _STL {
typedef _Rb_tree_iterator<pair<const int,int>,_Nonconst_traits<pair<const int,int> > > CBIterator;
template<> __declspec(dllimport) __forceinline CBIterator& CBIterator::operator++(){_M_node=_Rb_global_inst::_M_increment(_M_node);return *this;}
template<> __declspec(dllimport) __forceinline CBIterator& CBIterator::operator--(){_M_node=_Rb_global_inst::_M_decrement(_M_node);return *this;}
template<> __declspec(dllimport) __forceinline CBIterator::_Rb_tree_iterator(const CBIterator&x){_M_node=x._M_node;}
}


namespace _STL {
typedef pair<CBIterator,bool> CBInsertResult;
template<> __declspec(dllimport) __forceinline CBInsertResult::pair(const CBIterator&a,const bool&b):first(a),second(b){}
}


namespace _STL {
typedef _Rb_tree<int,pair<const int,void*>,_Select1st<pair<const int,void*> >,less<int>,allocator<pair<const int,void*> > > CBPointerTree;
template<> CBPointerTree::~_Rb_tree();
}


namespace _STL {
typedef _Rb_tree_node<pair<const int,int> > CBNode;
typedef _STLP_alloc_proxy<CBNode*,CBNode,allocator<CBNode> > CBNodeProxy;
template<> __declspec(dllimport) __forceinline CBNode* allocator<CBNode>::allocate(size_type n,const void*)const {return n ? reinterpret_cast<CBNode*>(allocator<char>::allocate(n*sizeof(CBNode),0)) : 0;}
template<> __declspec(dllimport) __forceinline CBNode* CBNodeProxy::allocate(size_t n){return static_cast<allocator<CBNode>&>(*this).allocate(n,0);}
template<> __declspec(dllimport) __forceinline void CBNodeProxy::deallocate(CBNode*p,size_t n){static_cast<allocator<CBNode>&>(*this).deallocate(p,n);}
}

namespace _STL {
template<> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned&a,const unsigned&b)const{return a<b;}
template<> __declspec(dllimport) __forceinline pair<const int,int>::pair(const int&a,const int&b):first(a),second(b){}
}



// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
enum ExitDoorType { DOOR_1=0 };
enum CommandSourceType { CMD_FROM_AI=2 };
enum PathfindLayerEnum { LAYER_WALL=17 };
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../../Include/Common/Player.h"
class Module;
#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

class LocomotorSet;
class Rva0035149F;
void Rva00030830GameFree(void*);
struct BfmeE12
{
    float x, y, z;
};
class Rva000E016A
{
  public:
    BfmeE12 *rva000E016A(unsigned, Coord3D *, Coord3D *);
};
namespace _STL
{
template <> __declspec(noinline) inline void _Construct(Coord3D *p, const Coord3D &r)
{
    if (p)
    {
        p->x = r.x;
        p->y = r.y;
        p->z = r.z;
    }
}
} // namespace _STL
// The retail copy worker takes the empty tag by const reference.
// Select that overload explicitly; the general STLport header uses a value tag.
namespace _STL
{
template <class I, class O> O __copy_ptrs(I, I, O, const __false_type &);
// No __uninitialized_copy declaration: with the generic body visible, _M_insert_overflow
// (0x002CDF8A) leaves its __false_type tags uninitialized as retail does.
} // namespace _STL
class Rva0035149F
{
  public:
    BfmeE12 *start, *finish, *end;
    Rva0035149F &rva0035149F(const Rva0035149F &);
};

enum AICommandType { AICMD_PATH = 9 };
struct AICommandParms {
 AICommandParms(AICommandType,CommandSourceType);
 // C free under /EHs (throwing), as the rowed AICommandInterface copy of rva0036EE16 calls it.
 ~AICommandParms(){if(coords.start)free(coords.start);}
 int cmd,source;Coord3D pos;Object *target;char pad18[8];Rva0035149F coords;char pad2c[0xc0-0x2c];
};
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/Common/ThingTemplate.h"
class Rva004C5772CmpBoolField {public:bool get()const;};
class ModelConditionFlags {public:
 unsigned int test(unsigned int bit)const{return m_words[bit>>5]&(1U<<(bit&0x1f));}
 void clear(unsigned int bit){m_words[bit>>5]&=~(1U<<(bit&0x1f));}
 private:unsigned int m_words[19];};
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
struct SiegeExitData {char pad[0x18c];Rva2225E0Filter filter;char pad18d[3];int count;};
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
extern int BfmeLogicFramesPerSecond;
template<int N>class SiegeExitSlots:public SiegeExitSlots<N-1>{public:virtual void gap(char(*)[N]);};
template<>class SiegeExitSlots<0>{};
class SiegeExitRemove:public SiegeExitSlots<41>{public:virtual void remove(Object*,bool);};
class OpenContain {public:virtual void exitObjectViaDoor(Object*,ExitDoorType);};
void Rva00030830FreeAllocation(void*);

namespace _STL {
template<> __forceinline void allocator<Coord3D>::deallocate(Coord3D *p,unsigned)const {if(p)Rva00030830FreeAllocation(p);}
}

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

#include "GameLogicObjectLookupView.h"
// Suppress this TU's non-retail copy of ??$max@I@_STL@@YAABIABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &); }
extern GameLogic *TheGameLogic;

void XferObjectID(Xfer *xfer, ObjectID *id);

class Object:public Thing {public:
 Player *getControllingPlayer()const;
 protected: Module *findModule(NameKeyType)const; public:
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*)const;
 void rva0028AE6D();void rva0028D412(const Matrix3D*);void setLayer(PathfindLayerEnum);
 void teleportTo(const Coord3D*,bool);void rva0028ACDC(int);
 ObjectID getID()const{return m_id;}
 char pad60[0x74-0x60];ObjectID m_id;char pad78[0xcc-0x78];float radius;char padD0[0x10c-0xd0];ModelConditionFlags mcf;
 char pad158[0x258-0x158];AIUpdateInterface *ai;
 __forceinline void clearModelConditionState(unsigned int mc){if(mcf.test(mc)!=0){mcf.clear(mc);rva0028AE6D();}}
};


class ObjectModuleView:public Object {public:using Object::findModule;};

class TransportContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x11C - 0x04];
};

class SiegeEngineContain : public TransportContain
{
public:
 // The exit entry receives the +0x30 ExitInterface view; xfer receives the primary view.
 virtual void exitObjectViaDoor(Object*,ExitDoorType);
 Object *object()const{return *reinterpret_cast<Object *const*>(reinterpret_cast<const char*>(this)-0x28);}
 const SiegeExitData *data()const{return *reinterpret_cast<const SiegeExitData *const*>(reinterpret_cast<const char*>(this)-0x2c);}
 void remove(Object *object){reinterpret_cast<SiegeExitRemove*>(reinterpret_cast<char*>(this)-0x10)->remove(object,false);}
 const bool &exitClosed()const{return *(reinterpret_cast<const bool*>(this)+0xf4);}
protected:
	virtual void xfer(Xfer *xfer);

private:
	_STL::list<int> m_11C;
	unsigned int m_120;
	bool m_124;
	_STL::map<int, int> m_128;
	_STL::list<int> m_134;
};

// ?xfer@SiegeEngineContain@@MAEXPAVXfer@@@Z @0x0047C322
void SiegeEngineContain::xfer(Xfer *xfer)
{
	TransportContain::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	ObjectID id;
	if (xfer->IsStoring())
	{
		*xfer == m_120;
		for (_STL::list<int>::iterator it = m_11C.begin(); it != m_11C.end(); ++it)
		{
			id = ((Object *)*it)->getID();
			XferObjectID(xfer, &id);
		}
	}
	else
	{
		if (!m_11C.empty())
		{
			m_120 = 0;
			for (_STL::list<int>::iterator it = m_11C.begin(); it != m_11C.end(); )
			{
				Object *rider = (Object *)*it;
				it = m_11C.erase(it);
				TheGameLogic->destroyObject(rider);
			}
			m_11C.clear();
		}
		*xfer == m_120;
		for (unsigned int i = 0; i < m_120; ++i)
		{
			XferObjectID(xfer, &id);
			m_134.push_back(reinterpret_cast<const int &>(id));
		}
	}

	*xfer == m_124;

	if (xfer->IsStoring())
	{
		int count = m_128.size();
		*xfer == count;
		for (_STL::map<int, int>::iterator it = m_128.begin(); it != m_128.end(); ++it)
		{
			ObjectID key = (ObjectID)it->first;
			int value = it->second;
			XferObjectID(xfer, &key);
			*xfer == value;
		}
	}
	else
	{
		int count;
		*xfer == count;
		for (int i = 0; i < count; ++i)
		{
			ObjectID key;
			int value;
			XferObjectID(xfer, &key);
			*xfer == value;
			m_128[reinterpret_cast<const int &>(key)] = value;
		}
	}
}

// WB names this override; retail decodes the owner and data relative to ExitInterface.
void SiegeEngineContain::exitObjectViaDoor(Object *exitObj,ExitDoorType door)
{
 if(exitClosed())return;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
 Rva004C5772CmpBoolField *deploy=(Rva004C5772CmpBoolField*)((ObjectModuleView*)object())->findModule(key);
 Object *me=object();const SiegeExitData *md=data();
 if(const_cast<Rva2225E0Filter&>(md->filter).accepts(exitObj,me->getControllingPlayer()) && md->count>0){
   remove(exitObj);
   Coord3D pos;pos.x=exitObj->m_cachedPos.x;pos.y=exitObj->m_cachedPos.y;pos.z=exitObj->m_cachedPos.z;
   {Coord3D diff;diff.x=pos.x-me->m_cachedPos.x;diff.y=pos.y-me->m_cachedPos.y;diff.z=pos.z-me->m_cachedPos.z;
   diff.normalize();float dx=diff.x*50.0f,dy=diff.y*50.0f;pos.x+=dx;pos.y+=dy;pos.z=0;}
   AIUpdateInterface *ai=exitObj->ai;
   TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
   if(ai){
     ai->ignoreObstacle(0);ai->m_ignoreCollisionsUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;
     Pathfinder *pathfinder=TheAI->m_pathfinder;pathfinder->adjustToPossibleDestination(exitObj,ai->getLocomotorSet(),&pos);
     _STL::vector<Coord3D> path;path.push_back(pos);path.push_back(pos);
     ai->rva0036EE16(reinterpret_cast<const Rva0035149F*>(&path),me,CMD_FROM_AI);
     exitObj->rva0028ACDC((int)&pos);
   }
 }else if(deploy && deploy->get()){
   remove(exitObj);Object *me=object();Coord3D pos;
   if(me->m_template->m_kindof[4]&0x800){Matrix3D transform;
     me->getSingleLogicalBonePosition("Ladder04",&pos,&transform);
     exitObj->clearModelConditionState(3*32+0);
     exitObj->rva0028D412(&transform);exitObj->setLayer(LAYER_WALL);
     AIUpdateInterface *ai=exitObj->ai;TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
     if(ai){if(exitObj->getControllingPlayer()->m_playerType==1){ai->ignoreObstacle(0);ai->aiHunt(CMD_FROM_AI);}else ai->aiIdle(CMD_FROM_AI);}
   }else{
     Coord3D dest;{pos=me->m_cachedPos;Coord3D direction=*me->getUnitDirectionVector2D();
     float radius=me->radius;pos.x+=direction.x*radius;pos.y+=direction.y*radius;
     pos.z=(TheAI->m_pathfinder ? TheAI->m_pathfinder : TheAI->m_pathfinder)->GetWallHeight(LAYER_WALL,&pos,0);
     dest=pos;pos.x+=direction.x*20.0f;pos.y+=direction.y*20.0f;
     dest.x+=direction.x*40.0f;dest.y+=direction.y*40.0f;}
     exitObj->teleportTo(&pos,false);exitObj->setOrientation(me->m_cachedAngle);exitObj->setLayer(LAYER_WALL);
     AIUpdateInterface *ai=exitObj->ai;TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
     if(ai){ai->ignoreObstacle(0);ai->m_ignoreCollisionsUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;Pathfinder *pathfinder=TheAI->m_pathfinder;pathfinder->adjustToPossibleDestination(exitObj,ai->getLocomotorSet(),&dest);}
     {_STL::vector<Coord3D> path;path.push_back(dest);path.push_back(dest);
     if(ai){ai->rva0036EE16(reinterpret_cast<const Rva0035149F*>(&path),me,CMD_FROM_AI);exitObj->rva0028ACDC((int)&dest);}}
   }
 }else reinterpret_cast<OpenContain*>(this)->OpenContain::exitObjectViaDoor(exitObj,door);
}

inline Rva0035149F &Rva0035149F::rva0035149F(const Rva0035149F &other)
{
    _STL::__false_type tag;
    typedef BfmeE12 *(__cdecl * Copy)(const BfmeE12 *, const BfmeE12 *, BfmeE12 *,
                                      const _STL::__false_type &);
    Copy copy = &_STL::__copy_ptrs<const BfmeE12 *, BfmeE12 *>;
    if (&other == this)
        return *this;
    unsigned n = other.finish - other.start, cap = end - start;
    if (n > cap)
    {
        BfmeE12 *fresh =
            ((Rva000E016A *)this)->rva000E016A(n, (Coord3D *)other.start, (Coord3D *)other.finish);
        if (start)
            Rva00030830GameFree(start);
        start = fresh;
        end = fresh + n;
    }
    else
    {
        unsigned sz = finish - start;
        if (sz >= n)
        {
            copy((const BfmeE12 *)other.start, (const BfmeE12 *)other.finish, start, tag);
        }
        else
        {
            copy((const BfmeE12 *)other.start, (const BfmeE12 *)(other.start + sz), start, tag);
            _STL::__uninitialized_copy((Coord3D *)(other.start + (finish - start)),
                                       (Coord3D *)other.finish, (Coord3D *)finish, tag);
        }
    }
    finish = start + n;
    return *this;
}

__declspec(noinline) inline void AICommandInterface::rva0036EE16(const Rva0035149F *info,Object *target,CommandSourceType src)
{
 AICommandParms parms(AICMD_PATH,src);parms.coords.rva0035149F(*info);parms.target=target;aiDoCommand(&parms);
}
