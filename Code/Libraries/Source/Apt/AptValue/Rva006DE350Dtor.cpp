// cl: /O2 /DNDEBUG /MD
// ??_GRva006DE350@@UAEPAXI@Z @0x006DE820 (75 bytes, vslot slot 14 of vtable 0x008EAED0).
// Scalar deleting destructor inlining ??1Rva006DE350@@UAE@XZ @0x006DE350 (51 bytes).
// Both store vtable 0x00CEAED0 and assert IsDestroyedGC()==true (AptValue.inl line 0x91)
// via the shared Apt assert pointer at 0x00A17734 and break flag at 0x009DC01C.
// Class is the AptValue owner of ctor 0x006DCD20 (same vtable, same +4 flag word,
// bit 3 = destroyed-GC via shr 3). Original class name unknown; honest Rva name
// reuses the existing ??1 pin (5 derived dtors tail-call it). No donor; retail-shaped.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DE350
{
public:
    virtual ~Rva006DE350();
private:
    unsigned int m_flags;
};
// ??1Rva006DE350@@UAE@XZ present-unmatched
Rva006DE350::~Rva006DE350()
{
    unsigned int f = m_flags;
    bool destroyed = ((f >> 3) & 1) != 0;
    if (!destroyed) {
        g_bfmeAptAssertAtE17734("IsDestroyedGC() == true", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValue.inl", 0x91);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
}
