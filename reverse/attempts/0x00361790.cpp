// ?Rva00361790@@YAHPAVRva00360F55@@@Z
// partial score=0.96 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00361790@@YAHPAVRva00360F55@@@Z at 0x00361790 (135 bytes).
// Dedup-register for the 0x94-byte validity-table record (ctor 0x360F55):
// count is (g_validityEnd-g_validityBegin)/0x94 via signed idiv, linear scan
// via rowed 0x360E64 equality, hit increments dword at +0x8C and returns the
// index, miss sets the input's +0x8C to 1, appends via rowed 0x361756
// vector<BfmePod148>::push_back on the table at 0xE01E68 and returns the new
// index ((end-begin)/0x94-1). Evidence: callers at 0x362411 0x3620FA 0x36224B
// plus iniParseObjectFilter; same globals/size/flags as siblings
// ObjectFilterRelease.cpp and Rva00360E64Equal.cpp; all callees rowed.
struct BfmePod148
{
	int a[37];
};
namespace _STL
{
	template <class _Tp> class allocator;
	template <class _Tp, class _Alloc> class vector
	{
	public:
		void push_back(const _Tp &x);
	};
}
class Rva00360F55
{
public:
	bool rva00360E64(const Rva00360F55 &other);
	char m_pad00[0x8C];
	int m_refCount8C;
	int m_tail90;
};
extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;
int Rva00361790(Rva00360F55 *record)
{
	int count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55);
	for (int i = 0; i < count; ++i)
	{
		Rva00360F55 *cur = (Rva00360F55 *)(i * (int)sizeof(Rva00360F55) + g_validityBegin);
		if (cur->rva00360E64(*record))
		{
			((Rva00360F55 *)g_validityBegin)[i].m_refCount8C++;
			return i;
		}
	}
	record->m_refCount8C = 1;
	((_STL::vector<BfmePod148, _STL::allocator<BfmePod148> > *)&g_validityBegin)->push_back((const BfmePod148 &)*record);
	return (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55) - 1;
}
