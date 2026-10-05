// ??1Rva005C67C0@@QAE@XZ
// partial score=0.84 date=2026-10-05
// cl: /O1 /MD
// Native 001F8167..001F81BF: destroy four-byte owning-pointer elements,
// then free the allocation. 001F9025 passes its second base at +4;
// the existing BigChainBaseDtors donor establishes Rva005C67C0's role.
// SGI/STLport vector teardown is the structural guide (three-pointer storage
// and reverse base cleanup). Original container and element names are unknown.
void __cdecl operator delete(void *);
void __cdecl free(void *);
struct BigChainVectorVictim
{
    virtual ~BigChainVectorVictim();
};
struct BigChainVectorElement
{
    BigChainVectorVictim *m_pointer;

};
class BigChainVectorStorage
{
public:
    BigChainVectorElement *m_begin;
    BigChainVectorElement *m_end;
    BigChainVectorElement *m_capacity;
    ~BigChainVectorStorage();
};
// ?BigChainVectorStorage::~BigChainVectorStorage present-unmatched
inline BigChainVectorStorage::~BigChainVectorStorage()
{
    if (m_begin)
        free(m_begin);
}
__forceinline void destroyChainRange(BigChainVectorElement *first, BigChainVectorElement *const &last)
{
    for (; first != last; ++first)
        ::delete first->m_pointer;
}
// ?destroyChainRange present-unmatched
class Rva005C67C0 : public BigChainVectorStorage
{
public:
    ~Rva005C67C0();
};
// ??1Rva005C67C0@@QAE@XZ present-unmatched
Rva005C67C0::~Rva005C67C0()
{
    destroyChainRange(m_begin, m_end);
}
