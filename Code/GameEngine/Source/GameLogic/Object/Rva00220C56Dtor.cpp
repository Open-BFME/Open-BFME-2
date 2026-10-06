// cl: /MD /EHsc
// ??1Rva00220C56@@QAE@XZ, retail 0x00220C56 30B.
// Frameless holder dtor: destroys [begin,end) via rowed 0x00220AEB then
// frees begin via rowed free 0x00030830. Sibling of EH holder 0x00220C17
// but no SEH frame. Caller 0x00220EBA. No vtable.
class LocomotorStore;
void __cdecl Rva00220AEBDestroy(LocomotorStore *first, LocomotorStore *last);
extern "C" void __cdecl free(void *block);

class Rva00220C56
{
public:
    ~Rva00220C56();

private:
    LocomotorStore *m_begin;
    LocomotorStore *m_end;
};

Rva00220C56::~Rva00220C56()
{
    Rva00220AEBDestroy(m_begin, m_end);
    if (m_begin)
        free(m_begin);
}
