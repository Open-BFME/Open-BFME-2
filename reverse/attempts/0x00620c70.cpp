// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z
// partial score=0.95 date=2026-10-05
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?contains@BfmeUnsignedKeyTree620C70@@QAE_NI@Z @0x00620C70 39B.
// contains() is `find(key) != end()`: find is the 20B out-of-line thunk at
// 0x4D7546 that tails unsigned _M_find 0x357180 through a hidden-return node
// pointer, and end() is the tree sentinel at this+0, so the whole body is the
// single `cmp ecx,edx / setne al` pair plus the two pushes the thunk takes.
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
	// The map is signed-key _Rb_tree<int,...,less<int>>: its out-of-line find@H
	// thunk is the 20B body placed at 0x4D7546 (it tails unsigned _M_find@I
	// 0x357180, so the runtime key is unsigned even though the tree key is int).
	// Taking the key through a signed reference avoids a converted temp, which
	// is what gives retail's plain `lea eax,[esp+0xc]` key slot.
	const int &k = (const int &)key;
	return m_map.find(k) != m_map.end();
}