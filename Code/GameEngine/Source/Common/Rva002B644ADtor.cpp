// ??1Rva002B644A@@EAE@XZ
// cl: /MD /EHs /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// 0x004FC05C 81B private virtual dtor (pin EAE) slot? caller ??_G at 0x002B647F.
// Derived vtable 0x007FE280 then host release of +0x18 via rowed 0x00212655
// then vector +0x8 frees via _free 0x00030830 then Snapshot base restores BBB554.
// Layout from rowed ctor 0x002B644A (vtable 0x7FE280, BfmeE16 vector +8,
// ints +4/-1 +0x14/0 +0x18/-1 +0x1C/0). Evidence: vtable stores, pin, caller,
// callees all rowed or pinned.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0021294A;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

class Rva00DFE1C8Host
{
public:
	void rva00212655(int value);	// 0x00212655
};

extern "C" void __cdecl free(void *);

extern const void *const g_00BBB554[];

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = (const void *)g_00BBB554;
}

class Rva002B644A : public Snapshot
{
	virtual ~Rva002B644A();
	int m_4;	// +0x04
	_STL::vector<BfmeE16> m_vec8;	// +0x08
	int m_14;	// +0x14
	int m_18;	// +0x18
	unsigned char m_1C;	// +0x1C
public:
	Rva002B644A();
};

Rva002B644A::~Rva002B644A()
{
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(m_18);
}
