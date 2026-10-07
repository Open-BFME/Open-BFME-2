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
 friend class Rva00739A30;
private:
	void rva0073CCC0(int x1, int x2, void *arr, int zero, int mask);
 void rva0073CAF0(int x1, int x2, void *arr, float rotation, int mask);
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

// Native739A30..739AE3 thiscall179B RET0C. The rowed
// ScriptEngine::doNamedMapReveal3577DA calls this with a waypoint location
// and radius through TheShroudManager; undo calls the existing739BE0.
// Both wrappers independently consume impl+4/+8 origins and +20 scale.
// Native callee73CAF0 is a complete362B RET14 routine: it consumes two
// cell coordinates, three integer radii, a float rotation and player mask.
// It is called with zero rotation here; its original method name remains
// unknown. Unlike the undo sibling it dispatches the native reveal walker.
// BFME1 donor1399ad37 Common/RTS/ShroudManagerImpl008FBA40.cpp supplies
// a related world-to-cell semantic guide; target receiver+10 comes from
// retail, not BFME1's different manager layout. The existing FISTP helper
// preserves the native x87 conversion instead of introducing CRT _ftol.
class Rva00739A30
{
public:
 void rva00739A30(Pair00739BE0 *p, float f, int mask);
private:
 char m_pad00[16];
 ShroudManagerImpl *m_gen10;
};
void Rva00739A30::rva00739A30(Pair00739BE0 *p, float f, int mask)
{
	int ic = fast_round(fast_ceil(f * m_gen10->m_scale));
	int arr[3];
	arr[2] = ic;
	arr[1] = ic;
	arr[0] = ic;
	int iy = fast_round(fast_floor((p->y - m_gen10->m_originY) * m_gen10->m_scale));
	int ix = fast_round(fast_floor((p->x - m_gen10->m_originX) * m_gen10->m_scale));
	m_gen10->rva0073CAF0(ix, iy, arr, 0.0f, mask);
}
