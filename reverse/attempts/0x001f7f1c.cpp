// ?Rva001F7F1CGet@@YAXPAXH@Z
// partial score=0.6703 date=2026-10-05
// ?Rva001F7F1CGet@@YAXPAXH@Z
// partial score=0.6703 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva001F7F1CGet@@YAXPAXH@Z, retail 0x001F7F1C (237B).
// Fills a caller-supplied Float4 from the live particle system: zero the
// destination, then when TheParticleSystemManager is non-null and its
// RvaSmartPtr12 (get@Rva001F6C54SmartField, member at +0x68) holds a system,
// reuse it or build the null system via Make001FCBD7, read the +4/+8 pair
// through rowed rva001F529D into the first two lanes and zero the rest, then
// hand the four floats to the object's slot-34 vtable entry.
// This build uses /O1 /DNDEBUG /MD /GX /arch:SSE; retail's xorps confirms SSE.
// Dropping /Oy- and swapping the final zero stores raised the search score only
// from 0.6694 to 0.6703; the frame and body still do not match.
// The inline smart-pointer destructor guards m_ptr and calls the rowed handle
// unlink at 0x004CBC0; retail calls that body for both getter temporaries.
// ?Rva001F7F1CGet@@YAXPAXH@Z present-unmatched
class ParticleSystem;
extern ParticleSystem *Make001FCBD7();
struct Vec2001F529D { float x; float y; };
class Rva001F529D { public: void rva001F529D(Vec2001F529D *out); };
struct BfmeParticleSystemHandle { ~BfmeParticleSystemHandle(); void *m_system; void *m_prev; void *m_next; };
// The 12-byte handle stores its system pointer at +0 and list links at +4/+8.
// The 0x004CBC0 unlink updates both neighbours (or the system's +0x9C/+0xA0
// sentinel pair) and clears +4/+8, consistent with the matched getter's m_ptr
// at +0 and the copy constructor's same layout.
class RvaSmartPtr12 {
public:
    RvaSmartPtr12(const RvaSmartPtr12 &that);
    ~RvaSmartPtr12()
    {
        if (m_ptr != 0)
            ((BfmeParticleSystemHandle *)this)->~BfmeParticleSystemHandle();
    }
    // The matched getter and copy constructor both prove the held pointer at +0.
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
    Float4 dest = { 0.0f, 0.0f, 0.0f, 0.0f };
    if (TheParticleSystemManager != 0 &&
        ((Rva001F6C54SmartField *)TheParticleSystemManager)->get().m_ptr != 0) {
        RvaSmartPtr12 tmp = ((Rva001F6C54SmartField *)TheParticleSystemManager)->get();
        ParticleSystem *sys = (ParticleSystem *)tmp.m_ptr;
        if (sys == 0)
            sys = Make001FCBD7();
        Vec2001F529D value;
        ((Rva001F529D *)sys)->rva001F529D(&value);
        dest.a = value.x;
        dest.b = value.y;
        dest.d = 0.0f;
        dest.c = 0.0f;
    }
    FinalObj *o = (FinalObj *)obj;
    o->vtbl->slot(obj, arg, &dest);
}
