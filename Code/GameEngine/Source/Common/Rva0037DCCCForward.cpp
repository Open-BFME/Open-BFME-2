// cl: /MD
//
// ?rva0037DCCC@@YAXPAVObject@@H@Z @0x0037DCCC 28B
// Free __cdecl forwarder (no this: entry ecx discarded; tail jmp leaves
// the 8 stack bytes to the cdecl caller): calls the rowed
// Object::updateUpgradeModules callee chain on the Object* through its
// +0x284 member (unproven member, positional), then tail-jumps to the
// rowed Object::updateUpgradeModules. The +0x284 call needs one new pin
// read from the retail REL32.

class Object;

// The callee is the rowed STLport _Base_bitset<32>::_M_do_or.
namespace _STL
{
template <unsigned int N> struct _Base_bitset
{
	void _M_do_or(const _Base_bitset<N> &other);
};
}
class Rva0037DCCC284
{
};

class Object
{
public:
	void updateUpgradeModules();
	unsigned char m_pad00[0x284];
	Rva0037DCCC284 m_284; // +0x284 inline subobject (lea address taken; unproven)
};

// ?rva0037DCCC@@YAXPAVObject@@H@Z, retail 0x0037DCCC, 28 bytes.
void __cdecl rva0037DCCC(Object *o, int b)
{
	((_STL::_Base_bitset<32> *)&o->m_284)->_M_do_or(*(const _STL::_Base_bitset<32> *)b);
	o->updateUpgradeModules();
}
