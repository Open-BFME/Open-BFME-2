// ??0Rva000FB87B@@QAE@XZ @0x000FB87B 59B
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Ctor stores vtbl_00BCF2F8+0x1C zeroes 0x04-0x14 constructs vector<PlayerAITypeEntry> at 0x18 via rowed Vector_base 0x00211E58 then zeroes 0x24-0x30. Evidence: leaf lane caller 0x007AC945; prev 0x000FB86C next 0x000FB8EB; same vector-base row as PlayerAITypeSetCtor; vtable extern vtbl_00BCF2F8.
#include <vector>

extern "C" const void *const vtbl_00BCF2F8[];

struct PlayerAITypeEntry
{
	char m_pad[16];
};

typedef _STL::_Vector_base<PlayerAITypeEntry, _STL::allocator<PlayerAITypeEntry> > PlayerAITypeVecBase;

class Rva000FB87B
{
public:
	Rva000FB87B();
private:
	const void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
	unsigned char m_pad15[3];
	unsigned char m_vec18[0xC];
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
};

Rva000FB87B::Rva000FB87B()
{
	*(unsigned int *)this = (unsigned int)&vtbl_00BCF2F8[7];
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	((PlayerAITypeVecBase &)m_vec18)._STL::_Vector_base<PlayerAITypeEntry, _STL::allocator<PlayerAITypeEntry> >::_Vector_base(_STL::allocator<PlayerAITypeEntry>());
	m_24 = 0;
	m_2C = 0;
	m_28 = 0;
	m_30 = 0;
}

// ??0Rva000FB8B6@@QAE@XZ 53B @0x000FB8B6: leaf ctor storing vtbl_00BCF2F8+0x38
// zeroes 0x04-0x0C constructs vector<PlayerAITypeEntry> at 0x10 via rowed
// Vector_base 0x00211E58 then zeroes 0x1C-0x28. Evidence: leaf lane caller
// 0x007AC95B; prev 0x000FB87B next 0x000FB8EB; same vector-base row;
// vtable extern vtbl_00BCF2F8 at +0x38.
class Rva000FB8B6
{
public:
	Rva000FB8B6();
private:
	const void *m_vptr;
	int m_04;
	int m_08;
	unsigned char m_0C;
	unsigned char m_pad0D[3];
	unsigned char m_vec10[0xC];
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
};

Rva000FB8B6::Rva000FB8B6()
{
	*(unsigned int *)this = (unsigned int)&vtbl_00BCF2F8[14];
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	((PlayerAITypeVecBase &)m_vec10)._STL::_Vector_base<PlayerAITypeEntry, _STL::allocator<PlayerAITypeEntry> >::_Vector_base(_STL::allocator<PlayerAITypeEntry>());
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
}
