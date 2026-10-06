// cl: /O1 /MD /EHs
// ??1Rva005C8FBD@@QAE@XZ @0x005C8FBD 94B
// Dtor: call HostClass rva005C8F17 then free +0x38 via _free then tree dtor
// at +0x2c (rowed ??1Rva005C8C73) then pool release at +8 via inline dtor.
// Evidence: chain from 0x005C8F17 landing callees 0x5C8F17 0x30830 0x5C8D2E
// 0x50ED3 callers deleting dtor 0x005C80B8 and STL destroy_aux.

extern "C" void __cdecl free(void *block);

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BfmePoolHolder
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef10
{
public:
	BfmePoolHolder *m_target;
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
};

class Rva005C8C73
{
public:
	~Rva005C8C73();
private:
	char m_data[8];
};

struct Holder38FBD
{
	void *m_ptr;
	__forceinline ~Holder38FBD() { if (m_ptr != 0) free(m_ptr); }
};

class HostClass005C8E0A
{
public:
	void rva005C8F17();
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
	char m_pad34[4];
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
