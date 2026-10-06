// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva004ABEAE@Rva00E03CE0@@QAEXPAURva001408C0Target@@@Z, retail 0x004ABEAE, 42 bytes.
// Registry at 0x00E03CE0 with set<Rva001408C0Target*> at +4: if set empty
// (size at +8) register itself via rowed Rva0020DFFBRegister 0x0020DFFB then
// insert the key via rowed set::insert 0x00080691. Called from 0x004ABED8
// and 0x004ABF47 with global 0x00E03CE0 as this. Flags match stlport neighbours.
#include <set>
class ModuleData { public: int x; };
struct Rva001408C0Target { int x; };
void __cdecl Rva0020DFFBRegister(const ModuleData* md);
struct Rva00E03CE0 {
    void* m_unk00;
    _STL::set<Rva001408C0Target*, _STL::less<Rva001408C0Target*>, _STL::allocator<Rva001408C0Target*> > m_set;
    void Rva004ABEAE(Rva001408C0Target* md);
};
void Rva00E03CE0::Rva004ABEAE(Rva001408C0Target* md)
{
    if (m_set.size() == 0)
        Rva0020DFFBRegister((const ModuleData*)this);
    m_set.insert(md);
}
