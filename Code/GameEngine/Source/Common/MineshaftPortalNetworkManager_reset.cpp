// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?reset@MineshaftPortalNetworkManager@@UAEXXZ @0x003734C0 (61B).
// Slot 9 (reset) of the MineshaftPortalNetworkManager table (update
// 0x003734FD in slot 10); ~MineshaftPortalNetworkManager 0x0037381C calls it.
// Map-values delete-then-clear over Tree00372FF4 at +0x10: walk nodes via
// header at [map] and begin at [header+8] with rowed _M_increment 0x00024250,
// for each value pointer at [node+0x14] call rowed rva00373357 0x00373357
// then rowed operator delete 0x0002FD60, tail-jmp rowed clear 0x00372F2D.
// Caller dtor 0x0037381C destroys map at +0x10 right after. Flags from prev.
#include <vector>
#include <map>

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;

enum ScienceType
{
	SCIENCE_Dummy0
};
class Rva00373357
{
public:
	void rva00373357();
	void *rva0037341F(bool b);
private:
	_STL::vector<ScienceType> m_vec; // +0x00
};

struct RvaNodeBase
{
	RvaNodeBase *m_parent;
	RvaNodeBase *m_left;
	RvaNodeBase *m_right;
	int m_color;
};

class MineshaftPortalNetworkManager
{
public:
	virtual void reset();
private:
	char m_pad04[0xC];
	Tree00372FF4 m_map;
};

// ?reset@MineshaftPortalNetworkManager@@UAEXXZ
void MineshaftPortalNetworkManager::reset()
{
	char *base = (char *)this + 0x10;
	RvaNodeBase *header = *(RvaNodeBase **)base;
	RvaNodeBase *cur = *(RvaNodeBase **)((char *)header + 8);
	while (cur != (RvaNodeBase *)header) {
		void *p = *(void **)((char *)cur + 0x14);
		if (p != 0) {
			((Rva00373357 *)p)->rva00373357();
			::operator delete(p);
		}
		cur = (RvaNodeBase *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)cur);
	}
	((Tree00372FF4 *)base)->clear();
}
