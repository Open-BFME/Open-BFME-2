// cl: /O2 /Oy /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z, retail 0x00620C70, 39 bytes.
//
// Unsigned-key containment test over the signed-key stlport map<int,void*>.
// Lifted from the banked attempt at score 0.96; two corrections took it to an
// exact match, and both are visible in the retail bytes:
//
// 1. /Oy, NOT /Oy-. Retail opens `push ecx / push esi / mov esi,ecx` with no
//    `push ebp`, so it was built with frame-pointer omission. The bank carried
//    /Oy-, which forces `push ebp / mov ebp,esp` and put a frame-pointer diff
//    at +0 -- the sole reason the bank never reached zero.
//
// 2. THE KEY IS PASSED BY ADDRESS, NEVER COPIED. Retail computes
//    `lea eax,[esp+0xc]` -- the address of its OWN argument slot -- and pushes
//    that, so find receives a pointer into the caller's frame and the key is
//    never loaded. Binding a reference first (`const int &k = (const int&)key`)
//    makes MSVC materialise the argument into a register or stack slot and the
//    copy shows up in the body. Taking the address at the point of use keeps
//    the key where the caller put it.
//
// The tree is the signed-key _Rb_tree<int,...,less<int>>: its find@H thunk is
// the 20B body placed at 0x004D7546 by WWVegas/WWLib/stlport_map_int_ptr_o1.cpp,
// and that thunk tails the unsigned _M_find@I at 0x357180, so retail's call
// resolves against the rowed address rather than self-referencing the way an
// unplaced unsigned thunk would.
//
// Evidence: call target 0x4D7546 is rowed and its bytes are the
// `mov ecx,[esp+4] / mov [ecx],eax / mov eax,ecx / ret 8` out-parameter thunk;
// the body is 0x00620C70..0x00620C97 with `ret 4` at 0x00620C96 and 0xCC
// padding after.
#include <map>

class BfmeUnsignedKeyTree620C70
{
public:
	bool contains(unsigned int key);

private:
	_STL::map<int, void *> m_map;
};

bool BfmeUnsignedKeyTree620C70::contains(unsigned int key)
{
	return m_map.find(*(const int *)&key) != m_map.end();
}
