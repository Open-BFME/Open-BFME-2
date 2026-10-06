// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ??1Rva00220C17@@QAE@XZ, retail 0x00220C17 63B.
// Vector-like holder dtor stride 0xC: derived calls rowed 0x00220AEB then
// base frees via rowed free 0x00030830. Chain from destroy landing; caller
// 0x00220CD4. Base-dtor split gives retail EH state 0. No vtable.
class LocomotorStore;
void __cdecl Rva00220AEBDestroy(LocomotorStore *first, LocomotorStore *last);

extern "C" void __cdecl free(void *block);

template <class T> struct RvaVectorBuffer
{
    ~RvaVectorBuffer()
    {
        if (m_begin)
            free(m_begin);
    }
    T *m_begin;
    T *m_finish;
};

struct Rva00220C17 : RvaVectorBuffer<LocomotorStore>
{
    ~Rva00220C17();
};

Rva00220C17::~Rva00220C17()
{
    Rva00220AEBDestroy(m_begin, m_finish);
}
