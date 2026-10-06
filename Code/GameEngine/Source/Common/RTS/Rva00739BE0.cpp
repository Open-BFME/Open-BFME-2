// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva00739BE0@Rva00739BE0@@QAEXPAUPair00739BE0@@MH@Z @0x00739BE0 179B
// Evidence: world-to-cell via ceil then 2x floor with Gen originX@+4 originY@+8 scale@+0x20 and rowed Gen wrapper shape; callers at 0x00357955 0x003BB942 pass (ptr float mask) with this=TheShroudManager PartitionManager; callee pinned 0x0073CCC0 ShroudManagerImpl; siblings 0x00739AF0 0x00739CA0 same Gen layout.
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline float fast_ceil(float f)
{
	return (float)ceil((double)f);
}

static __forceinline long fast_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct Pair00739BE0
{
	float x;
	float y;
};

struct FloatRect0073CE30
{
	float x1;
	float y1;
	float x2;
	float y2;
};

class Rva00739BE0;

class ShroudManagerImpl
{
	friend class Rva00739BE0;
private:
	void rva0073CCC0(int x1, int x2, void *arr, int zero, int mask);
public:
	float m_pad00;
	float m_originX;
	float m_originY;
	char m_pad0C[20];
	float m_scale;
};

class Rva00739BE0
{
public:
	void rva00739BE0(Pair00739BE0 *p, float f, int mask);
private:
	char m_pad00[16];
	ShroudManagerImpl *m_gen10;
};

void Rva00739BE0::rva00739BE0(Pair00739BE0 *p, float f, int mask)
{
	int ic = fast_round(fast_ceil(f * m_gen10->m_scale));
	int arr[3];
	arr[2] = ic;
	arr[1] = ic;
	arr[0] = ic;
	int iy = fast_round(fast_floor((p->y - m_gen10->m_originY) * m_gen10->m_scale));
	int ix = fast_round(fast_floor((p->x - m_gen10->m_originX) * m_gen10->m_scale));
	m_gen10->rva0073CCC0(ix, iy, arr, 0, mask);
}
