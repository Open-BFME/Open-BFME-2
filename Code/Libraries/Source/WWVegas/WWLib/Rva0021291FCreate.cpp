// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// ?rva0021291F@Rva0021291F@@QAEXPBX@Z, retail 0x0021291F, 43 bytes.
// Audio-driven ModuleData push_back: fetch const ModuleData* from TheAudio
// virtual slot 0x64 with the key then push_back into vector at this+0x2CC
// via rowed 0x004DFCB0. Reuses arg slot for fetched pointer. Caller
// 0x003FD476 in 0x003FD43B. Flags from next.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end

#include "../../../../GameEngine/Include/Common/ModuleData.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> ModuleData const * * allocator<ModuleData const *>::allocate(unsigned int,void const *)const ; }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<ModuleData const *,allocator<ModuleData const *> >::_M_clear(); }

// Call the rowed 0x004DFCB0 append instead of instantiating a growth chain.
namespace _STL { template <> void vector<ModuleData const *>::push_back(ModuleData const * const &); }

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
