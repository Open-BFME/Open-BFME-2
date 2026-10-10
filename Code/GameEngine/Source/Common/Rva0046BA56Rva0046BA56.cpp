// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
//
// ?rva0046BA56@Rva0046BA56@@QAEXPAVObject@@H@Z, retail 0x0046ba56, 119 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// +0x20 iface slot (REF tables 0x00844FD0 0x00845BC8 0x00846CB8): for each
// contained Object (pair via -0x20 base rowed 0x0046247D, second = +0x34
// list-head address) plus the live Object of every +0x150 rb-header key,
// the pinned Object::rva00298979(arg, false).
// Evidence: neighbours get/Rva00462CD3Sub plus FUN Clone siblings; callers none;
// second arg unread (ret 8); TheGameLogic real name; header+8 = leftmost and
// node+0x10 = key per rowed _M_increment TU.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "GameLogicObjectLookupView.h"
class Object
{
public:
	void rva00298979(Object *obj, bool flag);
};
extern GameLogic *TheGameLogic;
struct Rva0046247DPair
{
	void *m00;
	void *m04;
};
class Rva0046247D
{
public:
	void rva0046247D(Rva0046247DPair &p);
};
namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *node);
};
}
class Rva0046BA56
{
public:
	void rva0046BA56(Object *obj, int unused);
private:
	char m_pad0[0x34];
	void *m_34list; // +0x34 list head object address (pair second = &this field)
	char m_pad38[0x150 - 0x38];
	_STL::_Rb_tree_node_base *m_150head; // +0x150 rb header (= set object address)
};
void Rva0046BA56::rva0046BA56(Object *obj, int)
{
	Rva0046247DPair p;
	((Rva0046247D *)((char *)this - 0x20))->rva0046247D(p);
	void *addr = p.m04;
	// Codegen: this barrier fixes the native statement/schedule order (found by a per-statement barrier sweep).
	_ReadWriteBarrier();
	for (void *node = *(void **)*(void **)addr; node != *(void **)addr; node = *(void **)node) {
		Object *contained = *(Object **)((char *)node + 8);
		contained->rva00298979(obj, false);
	}
	for (_STL::_Rb_tree_node_base *node = m_150head->_M_left; node != m_150head; node = _STL::_Rb_global<bool>::_M_increment(node)) {
		Object *found = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)node + 0x10));
		if (found)
			found->rva00298979(obj, false);
	}
}
