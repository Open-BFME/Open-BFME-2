// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Path::DoXfer, retail [0x003661FC,0x003664DD) RET4, 737 bytes. WorldBuilder
// F1F180 names Path::DoXfer (pathfinder_path.cpp lines 1039..1073). Zero
// Hour's Path::xfer supplies the serialization order (version, node count,
// nodes written tail first, optimized link by node id); the target replaces
// ZH's PathNode::m_id with a node->id map on save and an id->node map on load,
// adds the per-node waypoint word and the current-node id, and skips the
// whole transfer for a light CRC. Layouts and slots come from the native body.
//
// The save map is a genuine STLport map<unsigned,int> instantiation: its
// operator[] and the helpers it drives compile to the shared retail map
// bodies (0x2077D6 subscript, 0x4FF3B6 lower bound, 0x358211 hinted insert,
// 0x20673B/0x4D795B insert_unique, 0x4D9C49 _M_insert, 0x382B7F create node,
// 0x60C9D9 construct). With the template bodies visible, cl sees that the
// subscript does not retain the key reference, which is what lets the loop
// key, the optimized-link key and the load-side waypoint share one frame slot.
#include <map>
#include <new>
#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

namespace _STL {
template<class V,class L,class R> __declspec(dllimport) __forceinline bool operator!=(const _Rb_tree_iterator<V,L>&a,const _Rb_tree_iterator<V,R>&b){return a._M_node!=b._M_node;}
template<> __declspec(dllimport) __forceinline bool less<int>::operator()(const int&a,const int&b)const{return a<b;}
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

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
class Xfer::Version { public: unsigned char value, current; Version() : value(1), current(1) {} };
Xfer *XferPathfindLayerEnum(Xfer *, int *);
enum PathfindLayerEnum { LAYER_INVALID = 0 };

#include "../../../Include/GameLogic/PathNode.h"
class Rva0026E4A0 { public: Rva0026E4A0 &set(Rva0026E4A0 *) throw(); };
class Rva00065964ObjectPool { public: void *rva002635C2() throw(); };
extern Rva00065964ObjectPool g_pathNodePool;

// Save-side node -> id map (rowed out-of-line destructor 0x36528F).
class Rva00364A37
{
public:
	~Rva00364A37();
	_STL::map<int, void *> map;
	__forceinline int &idOf(const unsigned &key) { return ((_STL::map<unsigned, int> *)this)->operator[](key); }
	__forceinline int &idOf(PathNode *const &node) { return ((_STL::map<unsigned, int> *)this)->operator[]((const unsigned &)node); }
};

// Load-side id -> node map (rowed out-of-line destructor 0x3652C7).
class Rva00364A60
{
public:
	~Rva00364A60();
	_STL::map<int, void *> map;
	__forceinline PathNode *&get(const int &key) { return (PathNode *&)((_STL::map<int, int> *)this)->operator[](key); }
	__forceinline void find(const int &key, PathNode *&result)
	{
		_STL::map<int, int> *m = (_STL::map<int, int> *)this;
		_STL::map<int, int>::iterator i = m->find(key);
		if (i != m->end())
			result = (PathNode *)i->second;
	}
};

class Path
{
public:
	void DoXfer(Xfer *);
	int unknown00;
	PathNode *head, *tail;
	bool optimized, blocked;
	PathNode *current;
	float distance;
	Coord3D goal;
	int unknown24;
};

void Path::DoXfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version;
	xfer->operator==(version);
	int count = 0;
	for (PathNode *node = head; node; node = node->m_next)
		++count;
	xfer->operator==(count);
	if (xfer->IsStoring()) {
		Rva00364A37 ids;
		unsigned key;
		PathNode *node = tail;
		while ((key = (unsigned)node), node) {
			ids.idOf(key) = count;
			xfer->operator==(count);
			Coord3D position;
			position.x = node->m_pos.x; position.y = node->m_pos.y; position.z = node->m_pos.z;
			xfer->operator==(asBase(position));
			int layer = node->m_layer;
			XferPathfindLayerEnum(xfer, &layer);
			bool canOpt = node->m_canOptimize;
			xfer->operator==(canOpt);
			int optID = -1;
			if (node->m_nextOpti)
				optID = ids.idOf((unsigned)node->m_nextOpti);
			xfer->operator==(optID);
			unsigned waypoint = node->m_portalID;
			xfer->operator==(waypoint);
			--count;
			node = node->m_prev;
		}
		int currentID = 0;
		if (current)
			currentID = ids.idOf(current);
		xfer->operator==(currentID);
	} else {
		Rva00364A60 nodes;
		while (count) {
			int nodeID;
			xfer->operator==(nodeID);
			Coord3D position; position.x = 0; position.y = 0; position.z = 0;
			xfer->operator==(asBase(position));
			int layer;
			XferPathfindLayerEnum(xfer, &layer);
			bool canOpt;
			xfer->operator==(canOpt);
			int optID = -1;
			xfer->operator==(optID);
			unsigned waypoint = 0x7fffffff;
			xfer->operator==(waypoint);
			void *storage = g_pathNodePool.rva002635C2();
			PathNode *node = storage ? new (storage) PathNode(&position, (PathfindLayerEnum)layer) : 0;
			nodes.get(nodeID) = node;
			node->m_canOptimize = canOpt; node->m_portalID = waypoint;
			PathNode *optNode = 0;
			if (optID > 0)
				nodes.find(optID, optNode);
			head = (PathNode *)&((Rva0026E4A0 *)node)->set((Rva0026E4A0 *)head);
			if (!tail)
				tail = node;
			if (optNode)
				node->m_nextOpti = optNode;
			--count;
		}
		int currentID;
		xfer->operator==(currentID);
		PathNode *curNode = 0;
		if (currentID)
			curNode = nodes.get(currentID);
		current = curNode;
		unknown24 = -1;
	}
	xfer->operator==(optimized).operator==(blocked).operator==(asBase(goal)).operator==(distance);
	xfer->operator==(unknown00);
}
