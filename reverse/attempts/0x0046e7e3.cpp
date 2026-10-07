// ?rva0046E7E3@HordeContain@@UAEXPBX_N@Z
// partial score=0.91 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0046E7E3@HordeContain@@QAEXPBX_N@Z @ 0x0046E7E3 (267B).
// Identity: three table slots share HordeContain neighbours at -8; target
// iterates its pair/list view and contained-object map. Parameters follow the
// Object update call and byte comparison in target code.
#include <list>

namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

typedef _STL::list<int, _STL::allocator<int> > IntList;

struct Rva0046247DPair { void *m00; void *m04; };
class Rva0046247D { public: void *rva0046247D(Rva0046247DPair &p); };
class Rva0036AE51ListView { public: IntList rva0036AE51(); };

struct RGBColor { float r, g, b; };
class Drawable { public: void rva0027541E(const RGBColor &, unsigned, unsigned, unsigned); };
class Object
{
public:
	void rva00293077(const void *);
	Drawable *getDrawable() const;
	int getID() const { return m_id; }
	char pad00[0x74];
	int m_id;
};
class BfmeArg985 { public: unsigned char bfmeHas985C(unsigned); };
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheGameLogic;
extern float g_00BCF3E4;

namespace _STL {
struct _Rb_tree_node_base;
template <class T> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
struct _Rb_tree_node_base { char pad[0x10]; int key; };
}

class HordeContain
{
public:
	virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
	virtual void h04(); virtual void h05(); virtual void h06(); virtual void h07();
	virtual void h08(); virtual void h09(); virtual void h10(); virtual void h11();
	virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
	virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
	virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23();
	virtual void h24(); virtual void h25(); virtual void h26(); virtual void h27();
	virtual void rva0046E7E3(const void *, bool);
};

void HordeContain::rva0046E7E3(const void *data, bool includeAll)
{
	Rva0046247DPair pair;
	IntList members = ((Rva0036AE51ListView *)((Rva0046247D *)((char *)this - 0x11c))->rva0046247D(pair))->rva0036AE51();
	RGBColor color = { g_00BCF3E4, g_00BCF3E4, g_00BCF3E4 };
	(*(Object **)((char *)this - 0x114))->rva00293077(data);
	for (IntList::iterator it = members.begin(); it != members.end(); ++it)
	{
		Object *obj = (Object *)*it;
		if (includeAll || ((BfmeArg985 *)obj)->bfmeHas985C((int)data))
		{
			obj->rva00293077(data);
			Drawable *drawable = obj->getDrawable();
			if (drawable)
				drawable->rva0027541E(color, 4, 4, 15);
		}
	}
	_STL::_Rb_tree_node_base *end = *(_STL::_Rb_tree_node_base **)((char *)this + 0x54);
	for (_STL::_Rb_tree_node_base *node = *(_STL::_Rb_tree_node_base **)((char *)end + 8); node != end;
	     node = _STL::_Rb_global<bool>::_M_increment(node))
	{
		Object *obj = TheGameLogic->findObjectByID(node->key);
		obj->rva00293077(data);
		Drawable *drawable = obj->getDrawable();
		if (drawable)
			drawable->rva0027541E(color, 4, 4, 15);
	}
}
