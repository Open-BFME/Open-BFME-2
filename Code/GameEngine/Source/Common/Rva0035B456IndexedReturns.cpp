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
class Image { public: void rva002D937E(); };

class Rva0035B456Owner
{
public:
    Rva002390CB rva0035B456();
    Rva002390CB rva0035B495();
    Rva002390CB rva0035B4D4();
    void rva0035B3E7();
    char pad[0xC8];
    _STL::vector<Rva002390CB> a, b, c;
    _STL::vector<Image *> images;
    int padF8;
    unsigned selected;
    bool flag100, flag101, flag102;
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

// Native/WB control predicates and image vector stride establish this loop;
// the owner identity and flag names remain unresolved.
void Rva0035B456Owner::rva0035B3E7()
{
    if (flag101 || flag102 || *(int *)(pad + 0x14) == 0x19) {
        for (_STL::vector<Image *>::iterator i = images.begin(); i != images.end(); ++i) {
            if (*i) (*i)->rva002D937E();
        }
    }
}
