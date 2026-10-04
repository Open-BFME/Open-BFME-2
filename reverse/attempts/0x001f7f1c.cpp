// ?Rva001F7F1CGet@@YAXPAXH@Z
// partial score=0.94 date=2026-10-05
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
// The smart pointer is a 12-byte list element: 0x004CBC0, the callee retail
// calls for its destructor, is an intrusive doubly-linked-list node unlink that
// rewrites both neighbour slots (or the owner's +0x9C/+0xA0 sentinel pair when
// this is the first node) and then clears +4 and +8. That fixes the field order
// as prev at +0, next at +4, owner at +8.
class RvaSmartPtr12 {
public:
    RvaSmartPtr12(const RvaSmartPtr12 &that);
    ~RvaSmartPtr12();
    void *m_prev;
    void *m_next;
    void *m_owner;
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
    if (TheParticleSystemManager != 0 && ((Rva001F6C54SmartField *)TheParticleSystemManager)->get().m_prev != 0) {
        RvaSmartPtr12 tmp2 = ((Rva001F6C54SmartField *)TheParticleSystemManager)->get();
        ParticleSystem *sys = (ParticleSystem *)tmp2.m_next;
        if (sys == 0)
            sys = Make001FCBD7();
        Vec2001F529D v;
        ((Rva001F529D *)sys)->rva001F529D(&v);
        dest[0] = v.x;
        dest[1] = v.y;
        dest[2] = 0.0f;
        dest[3] = 0.0f;
    }
    FinalObj *o = (FinalObj *)obj;
    o->vtbl->slot(obj, arg, dest);
}
