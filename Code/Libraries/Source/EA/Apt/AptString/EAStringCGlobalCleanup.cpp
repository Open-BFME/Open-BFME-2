// cl: /DNDEBUG /MD
// Target-only reconstruction. The names of the static strings are unknown.
// Ghidra proves the complete 10B boundary at 0x007B9C30. Its registered
// atexit callback (pushed at 0x007B676A) releases the EAStringC at VA
// 0x00E177D4 through the independently matched destructor 0x006D3010.
// The one-pointer value layout is shared with EAStringCRefCount.cpp.
class EAStringC
{
    class StringDataC;
    StringDataC *m_pData;
public:
    ~EAStringC();
    EAStringC &clear();
};

extern EAStringC g_eaStringAtE177D4;
extern EAStringC g_eaStringAtE18060;

// g_eaStringAtE177D4: VA 0x00E177D4 (.data BSS), one zero-filled pointer.
// The EAStringC layout is one pointer; keep raw storage so its matched
// initializer's explicit atexit callback remains the sole cleanup registration.
void *g_eaStringAtE177D4Storage;
#pragma comment(linker, "/alternatename:?g_eaStringAtE177D4@@3VEAStringC@@A=?g_eaStringAtE177D4Storage@@3PAXA")
// g_eaStringAtE18060: VA 0x00E18060 (.data BSS), one zero-filled pointer.
void *g_eaStringAtE18060Storage;
#pragma comment(linker, "/alternatename:?g_eaStringAtE18060@@3VEAStringC@@A=?g_eaStringAtE18060Storage@@3PAXA")

void rva007B9C30()
{
    g_eaStringAtE177D4.~EAStringC();
}

// Complete 10B Ghidra boundary; independently registered at 0x007B678A.
// The adjacent initializer calls the matched empty-string reset on VA E18060,
// then registers this same object's destructor callback.
void rva007B9C40()
{
    g_eaStringAtE18060.~EAStringC();
}

extern "C" int __cdecl atexit(void (__cdecl *callback)());

// Complete 22B initializer at 0x007B6760. The known reset stores the empty
// singleton and increments its refcount, then CRT owns the cleanup callback.
void rva007B6760()
{
    g_eaStringAtE177D4.clear();
    atexit(rva007B9C30);
}

// Independent 22B boundary at 0x007B6780; same initialization sequence,
// independently checked global VA E18060 and callback RVA 007B9C40.
void rva007B6780()
{
    g_eaStringAtE18060.clear();
    atexit(rva007B9C40);
}
