// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00472B54@Rva00472B54@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x00472B54, 314 bytes.
// Chain body that builds an AIGroup from a list snapshot and a map of ObjectIDs.
// Evidence: calls rowed createGroup 0x002FEC4B, AIGroup::add 0x0036E5F1,
// groupEnter 0x00370198, findObjectByID 0x00049DC5, aiBfmeObjectCommand3D
// 0x00470447, AI::destroyGroup 0x002FE712, list<int> push_back 0x0005548F,
// _M_increment 0x00024250; virtual slots 0x98/0x118/0xA8; map at +0x54;
// neighbours ContainModuleDeletingDtors/HordeContainRva00473125.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum ObjectID
{
	OBJID_INVALID = 0
};

class Object;
class AIGroup;
class AI;
class GameLogic;

class Object
{
public:
	unsigned char m_pad[0x250];
	void *m_250;
};

class AICommandInterface
{
public:
	void aiBfmeObjectCommand3D(Object *obj, CommandSourceType src);
};

class AIUpdate
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_cmd;
};

class AIGroup
{
public:
	void add(Object *obj);
	void groupEnter(Object *obj, CommandSourceType src);
};

class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *g);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern AI *g_Va009FF0F8;
extern GameLogic *TheGameLogic;

class Gate250
{
public:
	virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03();
	virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
	virtual void g08(); virtual void g09(); virtual void g10(); virtual void g11();
	virtual void g12(); virtual void g13(); virtual void g14(); virtual void g15();
	virtual void g16(); virtual void g17(); virtual void g18(); virtual void g19();
	virtual void g20(); virtual void g21(); virtual void g22(); virtual void g23();
	virtual void g24(); virtual void g25(); virtual void g26(); virtual void g27();
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37();
	virtual bool gate(void *a, int b, int c);
};

class GetterFC
{
public:
	virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
	virtual void h04(); virtual void h05(); virtual void h06(); virtual void h07();
	virtual void h08(); virtual void h09(); virtual void h10(); virtual void h11();
	virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
	virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
	virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23();
	virtual void h24(); virtual void h25(); virtual void h26(); virtual void h27();
	virtual void h28(); virtual void h29(); virtual void h30(); virtual void h31();
	virtual void h32(); virtual void h33(); virtual void h34(); virtual void h35();
	virtual void h36(); virtual void h37(); virtual void h38(); virtual void h39();
	virtual void h40(); virtual void h41(); virtual void h42(); virtual void h43();
	virtual void h44(); virtual void h45(); virtual void h46(); virtual void h47();
	virtual void h48(); virtual void h49(); virtual void h50(); virtual void h51();
	virtual void h52(); virtual void h53(); virtual void h54(); virtual void h55();
	virtual void h56(); virtual void h57(); virtual void h58(); virtual void h59();
	virtual void h60(); virtual void h61(); virtual void h62(); virtual void h63();
	virtual void h64(); virtual void h65(); virtual void h66(); virtual void h67();
	virtual void h68(); virtual void h69();
	virtual void get(void *out);
};

class Rva00472B54;
struct SnapOut
{
	int m_unused;
	_STL::list<int> **m_pp;
};

class Rva00472B54
{
public:
	void rva00472B54(Object *obj, CommandSourceType src);
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41();
	virtual void slotA8(int v);
	unsigned char m_pad[0x54 - 4];
	_STL::map<int, int> m_map;
};

void Rva00472B54::rva00472B54(Object *obj, CommandSourceType src)
{
	if (!obj)
		return;
	Gate250 *g = (Gate250 *)obj->m_250;
	if (!g)
		return;
	void *outer = *(void **)((char *)this - 0x114);
	if (!g->gate(outer, 1, 0))
		return;
	Object *outerObj = *(Object **)((char *)this - 0x114);
	AIUpdate *ai = *(AIUpdate **)((char *)outerObj + 0x258);
	if (!ai)
		return;
	ai->m_cmd.aiBfmeObjectCommand3D(obj, src);
	_STL::list<int> snap;
	GetterFC *gf = (GetterFC *)((char *)this - 0xFC);
	unsigned char buf[8];
	gf->get(buf);
	_STL::list<int> **ppsrclist = (_STL::list<int> **)&buf[4];
	for (_STL::list<int>::iterator it = (*ppsrclist)->begin(); it != (*ppsrclist)->end(); ++it)
		snap.push_back(*it);
	AIGroup *grp = g_Va009FF0F8->createGroup();
	for (_STL::list<int>::iterator it = snap.begin(); it != snap.end(); ++it)
		slotA8(*it);
	for (_STL::map<int, int>::iterator it = m_map.begin(); it != m_map.end(); ++it) {
		Object *o = TheGameLogic->findObjectByID((ObjectID)(*it).first);
		if (o)
			grp->add(o);
	}
	grp->groupEnter(obj, src);
	g_Va009FF0F8->destroyGroup(grp);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_Va009FF0F8@@3PAVAI@@A=?TheAI@@3PAVAI@@A")
