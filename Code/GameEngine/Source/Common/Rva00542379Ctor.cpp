// cl: /O1 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00541EB8@@QAE@XZ @0x00542379 67B. Default ctor storing vtable
// 0x00869514 after rowed pin base Rva0053FADE 0x0053FAB7 then members at
// +0x24 (rowed Rva00542225 0x00542225) and +0x44 (rowed Rva005422CF
// 0x005422CF). Evidence: vtable store, rowed/pinned callees, unlocks
// 0x0033082F, caller 0x00330892, neighbours share flags.
class Rva0053FADE
{
public:
	Rva0053FADE();
	virtual ~Rva0053FADE();
private:
	char m_pad[0x20];
};

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00330757Member
{
public:
	Rva00330757Member();

private:
	_STL::vector<BfmeE16> m_items;
	int m_flags;
};

class Rva00542225
{
public:
	Rva00542225();
	void rva00542067();
private:
	Rva00330757Member m_head;
	_STL::vector<BfmeE16> m_vec10;
	int m_1C;
};

class Rva005422CF
{
public:
	Rva005422CF();
	void rva00542148();
private:
	Rva00330757Member m_head;
	_STL::vector<BfmeE16> m_vec10;
	int m_1C;
};

class Rva00541EB8 : public Rva0053FADE
{
public:
	Rva00541EB8();
	virtual ~Rva00541EB8();
private:
	Rva00542225 m_24;
	Rva005422CF m_44;
};

Rva00541EB8::Rva00541EB8() : Rva0053FADE(), m_24(), m_44()
{
}
