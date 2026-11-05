// stlport
// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva005C8FBD@@QAE@XZ @0x005C8FBD 94B
// Dtor: call HostClass rva005C8F17 then free +0x38 via _free then tree dtor
// at +0x2c (rowed ??1Rva005C8C73) then pool release at +8 via inline dtor.
// Evidence: chain from 0x005C8F17 landing callees 0x5C8F17 0x30830 0x5C8D2E
// 0x50ED3 callers deleting dtor 0x005C80B8 and STL destroy_aux.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#include <stdlib.h>

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct BfmePoolHolder
{
	char m_pad00[0x0c];
	unsigned int m_audioHandle0C; // +0x0c
	char m_pad10[0x1c];
	float m_float2C; // +0x2c
	char m_pad30[0x58];
	OpaqueRefCounted m_ref; // +0x88
};

#include "../../Include/Common/BfmePoolRef10.h"

// Use the lookup owner's tree view. The extra four bytes replace the
// opaque +0x34 padding below; the holder remains at +0x38.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
typedef _STL::pair<const int, void *> TreeValue005530A8;
typedef _STL::_Rb_tree<int, TreeValue005530A8, _STL::_Select1st<TreeValue005530A8>, _STL::less<int>, _STL::allocator<TreeValue005530A8> > Tree005530A8;

class Rva005C8C73 : public Tree005530A8
{
public:
	void *rva005C8CA0(const void *key);
	~Rva005C8C73();
};

struct Holder38FBD
{
	void *m_ptr;
	__forceinline ~Holder38FBD() { if (m_ptr != 0) free(m_ptr); }
};

class BfmePoolRef10;
struct Element005C8E0A;
class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	void method_005C9069();
	void rva005C8F17();
	BfmePoolRef10 rva005C8E2C();
	char m_pad00[0x8];
private:
	BfmePoolRef10 m_pool08; // +0x08
	char m_pad0C[0x2C];
public:
	Element005C8E0A *m_start; // +0x38
	Element005C8E0A *m_finish; // +0x3C
	char m_pad40[0x6];
private:
	unsigned char m_byte46; // +0x46
	char m_pad47[0x1];
};

class Rva005C8FBD
{
public:
	~Rva005C8FBD();
private:
	char m_pad00[8];
	BfmePoolRef10 m_pool08;
	char m_pad0C[0x20];
	Rva005C8C73 m_tree2C;
	Holder38FBD m_holder38;
	void *m_finish3C;
	char m_pad40[6];
	unsigned char m_byte46;
	unsigned char m_byte47;
};

Rva005C8FBD::~Rva005C8FBD()
{
	((HostClass005C8E0A *)this)->rva005C8F17();
}
