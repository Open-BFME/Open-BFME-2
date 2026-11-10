// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Split from SceneSpatialRescale.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// 0x141F90 197B bounds-rescale. Donor guide BFME1 6583b3c1 scene.cpp:610
// BfmeSceneVector::rva00943FF0 (recovery name, NOT retail).
// Target: SEH body calling rowed clear 0x141EF0, copying 6 floats to +0x00,
// scale = g_bfmeDefaultBU / max(dx,dy) to +0x20 via comiss+divss, calling
// rowed process 0x141C40, scope-end dtor pushing to 0xDB4254.
// 197-vs-201B 4B delta = EH + unordered-max/div shape under /arch:SSE /G7.
// Layout 0x28 TU-local matching canonical (actual header included).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#include <new.h>
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
// Preserve the placement operators already declared above and by always.h.
#define __PLACEMENT_NEW_INLINE
#define __PLACEMENT_VEC_NEW_INLINE
// stlport
#include <slist>
// bfme link decl-only begin
namespace _STL { template <> _Slist_node_base * _Slist_base<int, allocator<int> >::_M_erase_after(_Slist_node_base *, _Slist_node_base *); }
// bfme link decl-only end

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);
	void *rva00141800();

	int m_00; // +0x00 retail 0x80
	void *m_04; // +0x04 retail 0
	void *m_head; // +0x08 VA 0xDB4254 (.data RVA 0x9B4254, free-list head)
	void *(__cdecl *m_alloc)(int size, int arg); // +0x0C retail 0x42FFC0 (Rva0002FFC0Alloc pinned)
	void (__cdecl *m_free)(void *ptr, int arg); // +0x10 retail 0x42FFE0 (Rva0002FFE0Free pinned)
	int m_14; // +0x14 retail 0
};

extern Rva0006EFC8 g_BfmeSceneNodePool; // VA 0xDB424C (.data RVA 0x9B424C), 24B pool
typedef char Rva0006EFC8PoolSize24[(sizeof(Rva0006EFC8) == 0x18) ? 1 : -1];

class Gen_00943CF0
{
public:
	void process(Gen_00943CF0_Node **list);
};

struct Rva00141F90Bounds
{
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
};

// Retail divisor VA 0xBBB8D8 is .rdata (RVA 0x7BB8D8, float=1, 1684 refs),
// NOT .data: AudioManagerFocusVolume.cpp `float g_Va00BBB8D8 = 1.0f;`
// is section-wrong (.data VA 0xDAxxxx, cannot be at 0xBBB8D8) and
// T_009F4FB0.cpp `static float g_bfmeDefaultBU;` is TU-local (invisible).
// Correct provider is compiler literal 1.0f -> __real@3f800000 COMDAT in
// .rdata, folded by /OPT:ICF to the single retail 0xBBB8D8 (same mechanism
// as Rva00263653Ctor/Rva002DB311Ctor which use literals, not externs).
// Extern g_bfmeDefaultBU removed (was undefined link hazard); literal keeps
// identical movss/divss shape (DIR32-masked per-TU, link-correct via COMDAT).

// The rowed 141CA0 destructor proves the scene list lives at element +4.
// Retail's array constructor callback at 141830 initializes the same 28 bytes.
class BfmeNonRefSceneList
{
public:
	virtual ~BfmeNonRefSceneList();
private:
	char m_pad[0x14];
};

class Rva00141D00
{
public:
	Rva00141D00();
	~Rva00141D00();
private:
	int m_pad;
	BfmeNonRefSceneList m_list;
};

struct Rva0006FB50List
{
	Gen_00943CF0_Node *head;
	// 6FB50 -> 6FABF only relinks and recycles nodes, without throwing calls.
	~Rva0006FB50List() throw();
};

class BfmeSceneVector
{
public:
	BfmeSceneVector();
	void rva00141EF0(Gen_00943CF0_Node **objects);
	void rva00141F90(const Rva00141F90Bounds &newBounds);
	void Set_Level(unsigned int level);

	Rva00141F90Bounds bounds;
	Rva00141D00 *vector;
	int vector_max;
	float scale;
	unsigned int level_mask;
};

typedef char BfmeSceneRescaleSizeMatchesCanonical[(sizeof(BfmeSceneVector) == 0x28) ? 1 : -1];
typedef char BfmeSceneRescaleMatchesIndex[(sizeof(BfmeSceneVector) == sizeof(BFME2SceneSpatialIndex)) ? 1 : -1];



void *bfmeAnchorBfmeSceneVectorCtor(void *where);

// Native6FB50..6FB59 RET0 and the verified Set_Level caller establish this
// one-head list destructor. It calls the existing erase provider6FABF with
// the head address and a null end; no payload method is called. STLport gives
// the reference structure; int is the existing provider's ABI carrier, not
// evidence for the original scene-node payload type or list spelling.
// The pool erase body is visible for rescale inlining. Its retail /O1 /Ob0
// provider and the outlined list destructor live in SceneNodeListProviders.cpp.
// Forced inline below, so this /O2 unit emits no copy that differs from those rows.
namespace _STL {
template <> _Slist_node_base *
_Slist_base<int,allocator<int> >::_M_erase_after(_Slist_node_base*,_Slist_node_base*);
}

namespace _STL {
template <> __declspec(dllimport) __forceinline _Slist_node_base *
_Slist_base<int,allocator<int> >::_M_erase_after(_Slist_node_base* head,_Slist_node_base* stop)
{
 _Slist_node_base* current=head->_M_next;
 while(current!=stop) {
  _Slist_node_base* old=current;
  current=current->_M_next;
  _Slist_node_base* freeHead=(_Slist_node_base*)g_BfmeSceneNodePool.m_head;
  old->_M_next=freeHead;
  g_BfmeSceneNodePool.m_head=old;
 }
 return head->_M_next=stop;
}
}

// STLport's base constructor, forced inline so this unit emits no /O2 copy of row 0x6FA99.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Slist_base<int,allocator<int> >::_Slist_base(const allocator<int>& __a) :
 _M_head(_STLP_CONVERT_ALLOCATOR(__a, _Slist_node<int>), _Slist_node_base())
{ _M_head._M_data._M_next = 0; }
}

void BfmeSceneVector::rva00141F90(const Rva00141F90Bounds &newBounds)
{
	typedef _STL::_Slist_base<int,_STL::allocator<int> > NodeList;
	NodeList objects((_STL::allocator<int>()));
	typedef char OneWordList[(sizeof(NodeList)==4)?1:-1];
	rva00141EF0((Gen_00943CF0_Node **)&objects);
	bounds = newBounds;
	float dx = bounds.m_0C - bounds.m_00;
	float dy = bounds.m_10 - bounds.m_04;
	float greater = dx > dy ? dx : dy;
	scale = 1.0f / greater;
	((Gen_00943CF0 *)this)->process((Gen_00943CF0_Node **)&objects);
}
