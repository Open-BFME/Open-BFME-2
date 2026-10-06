// ?removeSelection@@YAXPAU_ListboxData@@H@Z @0x00323FD9 40B.
// Static listbox selection compactor called by the GadgetListBox message
// handler: memcpy selections[i+1 ..] down one slot and write the -1 sentinel
// at selections[listLength-1]. Retail body decodes as
//   movsx edx,[esi]; mov eax,[esi+0x38]; sub edx,ecx; lea eax,[eax+ecx*4];
//   shl edx,2; push edx; lea ecx,[eax+4]; push ecx; push eax; call memcpy;
//   movsx eax,[esi]; mov ecx,[esi+0x38]; or [ecx+eax*4-4],-1; add esp,0xc; ret
// so the helper uses the compiler-private static convention: list in ESI,
// index in ECX, no stack arguments. Target proves the Short listLength at +0
// and the Int* selections at +0x38; memcpy binds to the named thunk 0x6291A8.
// A translation unit that defines the helper alone dead-strips it, and giving
// it external linkage forces plain cdecl; MSVC 7.1 only emits the ESI/ECX form
// when a caller in the same TU references it, so the free function below is a
// codegen scaffold (it has no retail address and is never rowed).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/displaystring /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
typedef int Int;
typedef short Short;

struct _ListboxData
{
    Short listLength;    // +0x00
    char m_pad02[0x36];  // +0x02..+0x37
    Int *selections;     // +0x38
};

extern "C" void *memcpy(void *dst, const void *src, unsigned size);

static void removeSelection( _ListboxData *list, Int i )
{
    memcpy( &(*(Int **)((char *)list + 0x38))[i],
            &(*(Int **)((char *)list + 0x38))[(i+1)],
            ((list->listLength - i) * sizeof(Int)) );
    (*(Int **)((char *)list + 0x38))[(list->listLength - 1)] = -1;
}

// Codegen scaffold: forces emission of removeSelection under the compiler's
// private static calling convention. Not a retail body and not ledgered.
void Rva00323FD9Emit( _ListboxData *list, Int i )
{
    removeSelection( list, i );
}
