// ?Rva001F7F1CGet@@YAXPAXH@Z
// partial score=0.94 date=2026-10-04
// cl: /O1 /Oy- /DNDEBUG /MD /GX /arch:SSE
// ?Rva001F7F1CGet@@YAXPAXH@Z, retail 0x001F7F1C (237B).
// Fills a caller-supplied Float4 from the live particle system: zero the
// destination, then when TheParticleSystemManager is non-null and its
// RvaSmartPtr12 (get@Rva001F6C54SmartField, member at +0x68) holds a system,
// reuse it or build the null system via Make001FCBD7, read the +4/+8 pair
// through rowed rva001F529D into the first two lanes and zero the rest, then
// hand the four floats to the object's slot-34 vtable entry.
// Flags follow the matched RvaSmartPtr12 getter 0x001F6C54 (/O1 /Oy- /GX)
// with /arch:SSE, which retail's xorps-based zeroing proves.
// The RvaSmartPtr12 destructor is out of line here (retail calls 0x004CBC0
// twice; 0x001F6C54's own copy-ctor call fixes the same callee identity).
// ?Rva001F7F1CGet@@YAXPAXH@Z present-unmatched
class ParticleSystem;
extern ParticleSystem *Make001FCBD7();
struct Vec2001F529D { float x; float y; };
class Rva001F529D { public: void rva001F529D(Vec2001F529D *out); };
struct BfmeParticleSystemHandle { ~BfmeParticleSystemHandle(); void *m_system; void *m_prev; void *m_next; };
class RvaSmartPtr12 {
public:
    RvaSmartPtr12(const RvaSmartPtr12 &that);
    ~RvaSmartPtr12();
    void *m_ptr;
    int m_pad04;
    int m_pad08;
};
class Rva001F6C54SmartField { public: RvaSmartPtr12 get() const; };
class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;
struct FinalVtbl { void *slots[34]; void (__stdcall *slot)(void *, int, void *); };
struct FinalObj { FinalVtbl *vtbl; };
struct Float4 { float a; float b; float c; float d; };
void __cdecl Rva001F7F1CGet(void *obj, int arg)
{
    float dest[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    if (TheParticleSystemManager != 0 && ((Rva001F6C54SmartField *)TheParticleSystemManager)->get().m_ptr != 0) {
        RvaSmartPtr12 tmp2 = ((Rva001F6C54SmartField *)TheParticleSystemManager)->get();
        ParticleSystem *sys = (ParticleSystem *)tmp2.m_ptr;
        if (sys == 0)
            sys = Make001FCBD7();
        Vec2001F529D v;
        ((Rva001F529D *)sys)->rva001F529D(&v);
        Float4 tmpArr;
        tmpArr.a = v.x;
        tmpArr.b = v.y;
        tmpArr.c = 0.0f;
        tmpArr.d = 0.0f;
        *(Float4 *)dest = tmpArr;
    }
    FinalObj *o = (FinalObj *)obj;
    o->vtbl->slot(obj, arg, dest);
}
