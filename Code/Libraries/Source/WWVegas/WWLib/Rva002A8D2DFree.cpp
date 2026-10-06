// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva002A8D2DFree@@YGXPAURva002A8D2DNode@@@Z @ 0x002A8D2D (28B).
// Opaque node deleter calling rowed dtor ??1CameraMarker@@QAE@XZ then rowed free.
// Evidence: sole caller is clear loop 0x002A8FE0; same 28B shape and flags as
// Rva00055864Free in this dir. Honest address name.
class CameraMarker
{
public:
	~CameraMarker() throw();
};

struct Rva002A8D2DNode
{
	void *m_next;
	CameraMarker m_val;
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva002A8D2DFree(Rva002A8D2DNode *p)
{
	p->m_val.CameraMarker::~CameraMarker();
	if (p) {
		free(p);
	}
}
