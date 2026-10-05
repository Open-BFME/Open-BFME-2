// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z
// partial score=0.96 date=2026-10-05
// cl: /O2 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z, retail 0x00620C70, 39 bytes.
//
// 39B is reachable, but only with the key through a SIGNED reference and with
// /O2 /Oy-; the unsigned-key spelling emits a third argument (47B) and /O1 adds
// a frame pointer retail does not have.
//
// What is left is one instruction, and it is an ABI shape rather than a
// spelling. Retail does NOT read find's return value:
//
//   call 0x4D7546
//   mov ecx,[esi]           the tree header
//   mov edx,[esp+4]         <-- a CALLER STACK SLOT, not eax
//   xor eax,eax / cmp edx,ecx / setne al
//
// The thunk at 0x4D7546 ends `mov ecx,[esp+4] / mov [ecx],eax / mov eax,ecx
// / ret 8`: it writes the found node through a pointer the CALLER supplied on
// its own stack and retires 8 bytes of it. contains then compares that stored
// node against the header, so the call is made through a hidden-return
// convention rather than the ordinary one.
//
// `m_map.find(k) != m_map.end()` cannot produce it -- stlport returns the
// iterator in eax and the compare folds, which is the 18-instruction shape (an
// extra `mov al,dl` and a different setne target). Closing this needs the node
// to round-trip through the caller's stack, which ordinary stlport find never
// does. Declaring the out slot explicitly does not help either: it does not
// compile against this shim, whose find is the plain eax-returning member.
//
// So the body here is the best source produces -- 39B, retail's exact size and
// every byte but one matching -- and the residual is the ABI/linker binding the
// bank identified, now measured against the SIGNED map that makes the rest exact.
//
// The signed key is the point, and it took two rows to establish. Retail's call
// target 0x4D7546 is
//   ??$find@H@?$_Rb_tree@HU?$pair@$$CBHPAX@_STL@@...          key int
// which TAILS the unsigned worker:
//   0x357180  ??$_M_find@I@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@...  key unsigned
// The tree's key type is `int` (H) while the compare runs through a worker shared
// with the unsigned instantiations (I); the two thunks are byte-identical and
// ICF-shared onto 0x4D7546. Routing this body through the SIGNED find@H -- which
// IS rowed at that address -- is what removes the spurious third argument the
// unsigned spelling emitted (47B -> 39B).
#include <map>

class BfmeUnsignedKeyTree620C70
{
public:
	bool contains(unsigned int key);

private:
	_STL::map<int, void *> m_map;
};

// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z present-unmatched
bool BfmeUnsignedKeyTree620C70::contains(unsigned int key)
{
	// The map is the signed-key _Rb_tree<int,...,less<int>>: its out-of-line
	// find@H thunk is the 20B body placed at 0x4D7546 (it tails the unsigned
	// _M_find@I at 0x357180, so the runtime key is unsigned even though the
	// tree's key type is int). Taking the key through a signed reference avoids
	// a converted temp, which is what gives retail's plain `lea eax,[esp+0xc]`
	// key slot.
	const int &k = (const int &)key;
	return m_map.find(k) != m_map.end();
}
