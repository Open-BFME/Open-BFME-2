// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0021291F@Rva0021291F@@QAEXPBX@Z, retail 0x0021291F, 43 bytes.
// Audio-driven ModuleData push_back: fetch const ModuleData* from TheAudio
// virtual slot 0x64 with the key then push_back into vector at this+0x2CC
// via rowed 0x004DFCB0. Reuses arg slot for fetched pointer. Caller
// 0x003FD476 in 0x003FD43B. Flags from next.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData
{
public:
    virtual ~ModuleData();
};

class AudioManager
{
public:
    virtual void dummy00();
    virtual void dummy01();
    virtual void dummy02();
    virtual void dummy03();
    virtual void dummy04();
    virtual void dummy05();
    virtual void dummy06();
    virtual void dummy07();
    virtual void dummy08();
    virtual void dummy09();
    virtual void dummy10();
    virtual void dummy11();
    virtual void dummy12();
    virtual void dummy13();
    virtual void dummy14();
    virtual void dummy15();
    virtual void dummy16();
    virtual void dummy17();
    virtual void dummy18();
    virtual void dummy19();
    virtual void dummy20();
    virtual void dummy21();
    virtual void dummy22();
    virtual void dummy23();
    virtual void dummy24();
    virtual const ModuleData *getModule(const void *key);
};

extern AudioManager *TheAudio;

class Rva0021291F
{
public:
    void rva0021291F(const void *key);

private:
    unsigned char m_pad[0x2CC];
    _STL::vector<const ModuleData *> m_vec;
};

void Rva0021291F::rva0021291F(const void *key)
{
    const ModuleData *mod = TheAudio->getModule(key);
    m_vec.push_back(mod);
}
