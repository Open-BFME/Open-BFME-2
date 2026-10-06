// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva001DF057@@UAE@XZ @0x001DF057 154B.
// Virtual dtor with primary vtable 0x00BDC5B8 and secondary 0x00BDC5A8.
// Primary base GameEngineDeletingBase at +0 (size 0xC rowed 0x001B4E74).
// Secondary Snapshot at +0xC restored to g_00BBB554 inline (no call).
// Members in reverse destroy order: list<int> at +0x68 via rowed List_base
// 0x004EC395 then ptr at +0x5C via inline null-guarded free 0x00030830 then
// two hash tables at +0x48/+0x34 via dup 0x001DDBF3 (same bytes as rowed
// ??1Rva000427195 0x001FDEDB) then two vectors of Rva001DEF38Element at
// +0x28/+0x1C via rowed 0x001DEEF9 then tree Rva001DD70F at +0x10 via rowed
// 0x001DD9BB. Caller is ??_G at 0x001DF3D5 in OpaqueScalarDeletingDtorsB03.
#include <vector>
#include <list>

extern "C" void __cdecl free(void *block);

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[0x0C - 0x04];
};

extern const void *const g_00BBB554[];

class SnapBase
{
public:
	virtual ~SnapBase() { *(const void **)this = g_00BBB554; }
};

class Rva001DD70F
{
public:
	~Rva001DD70F();
private:
	void *m_header;
	int m_flag;
};

struct Rva001DEF38Element
{
	~Rva001DEF38Element();
};

void __cdecl dup_001ddbf3(void);

struct Rva000427195Hash
{
	~Rva000427195Hash()
	{
		((void (__fastcall *)(void *))&dup_001ddbf3)(this);
	}
	char m_pad[20];
};

struct Rva001DF057Buf
{
	~Rva001DF057Buf()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
	void *m_ptr;
};

class Rva001DF057 : public GameEngineDeletingBase, public SnapBase
{
public:
	virtual ~Rva001DF057();
private:
	Rva001DD70F m_tree10;
	char m_pad18[0x1C - 0x10 - sizeof(Rva001DD70F)];
	_STL::vector<Rva001DEF38Element, _STL::allocator<Rva001DEF38Element> > m_vec1C;
	_STL::vector<Rva001DEF38Element, _STL::allocator<Rva001DEF38Element> > m_vec28;
	Rva000427195Hash m_hash34;
	Rva000427195Hash m_hash48;
	Rva001DF057Buf m_buf5C;
	char m_pad60[0x68 - 0x5C - sizeof(Rva001DF057Buf)];
	_STL::_List_base<int, _STL::allocator<int> > m_list68;
};

Rva001DF057::~Rva001DF057()
{
}
