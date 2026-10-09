// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// stlport
#include <vector>

// Native 35B456/495/4D4 are three indexed 8-byte value returns, bounded by
// the vector size and common selection word at +FC. The source identity of
// this owner is unresolved. The established native copy/default providers
// (2390CB / 4CEE6E) determine the return-value ABI; no donor type name inferred.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva002390CB
{
public:
    Rva002390CB();
    Rva002390CB(const Rva002390CB &other);
    ~Rva002390CB();
    void *m_00;
    void *m_04;
};
class Rva0035B456Owner
{
public:
    Rva002390CB rva0035B456();
    Rva002390CB rva0035B495();
    Rva002390CB rva0035B4D4();
    char pad[0xC8];
    _STL::vector<Rva002390CB> a, b, c;
    void *padEC[4];
    unsigned selected;
};
Rva002390CB Rva0035B456Owner::rva0035B456()
{
    _STL::vector<Rva002390CB> *v = &a;
    unsigned count = v->size();
    unsigned index = selected;
    if (count > index) {
        _ReadWriteBarrier();
        return (*v)[index];
    }
    return Rva002390CB();
}
Rva002390CB Rva0035B456Owner::rva0035B495()
{
    _STL::vector<Rva002390CB> *v = &b;
    unsigned count = v->size();
    unsigned index = selected;
    if (count > index) {
        _ReadWriteBarrier();
        return (*v)[index];
    }
    return Rva002390CB();
}
Rva002390CB Rva0035B456Owner::rva0035B4D4()
{
    _STL::vector<Rva002390CB> *v = &c;
    unsigned count = v->size();
    unsigned index = selected;
    if (count > index) {
        _ReadWriteBarrier();
        return (*v)[index];
    }
    return Rva002390CB();
}
