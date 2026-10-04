// cl: /DNDEBUG /MD /EHs-c-

extern "C" int sprintf(char *buffer, const char *format, ...);

struct Rva00891FA0Record
{
    int value;
    int kind;
};

extern int g_rva00891FA0Ready;
// g_rva00891FA0Ready: matched references place it at VA 0xe17708 (zero-filled .bss).
int g_rva00891FA0Ready;
extern int g_rva00891FA0Value;
// g_rva00891FA0Value: matched references place it at VA 0xe176f0 (zero-filled .bss).
int g_rva00891FA0Value;
// Retail slots 0x00E17740/44 are not PE imports (no import-table entry), so
// these are .data function pointers, not dllimport functions. Both emit an
// indirect call through the slot; only the symbol identity differs.
// Matched DIR32 witnesses place these runtime-filled callback cells in the
// zero-filled .data tail; vanilla retail initializes both to NULL.
extern "C" void (__cdecl *Rva00891FA0SendRecord)(
    Rva00891FA0Record *record, int count) = 0; // VA 0x00E17740
extern "C" void (__cdecl *Rva00891FA0SendText)(const char *text) = 0; // VA 0x00E17744

// ?d_00891fa0@@YAXXZ
void d_00891fa0(void)
{
    if (!g_rva00891FA0Ready)
        return;

    char text[16];
    Rva00891FA0Record record;
    sprintf(text, "%06d", g_rva00891FA0Value);
    Rva00891FA0SendText(text);
    record.value = g_rva00891FA0Value;
    record.kind = 3;
    Rva00891FA0SendRecord(&record, 5);
}

// BFME1 lead: 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/Common/Rva00891FA0Diagnostics.cpp,
// Rva00892150SetReady; the original target name remains unproven.
// Native 0x006CD010 reads one stack word, stores it to the same Ready cell
// used by the rowed diagnostics consumer, and zeroes that consumer's Value
// cell. The complete 20-byte entry follows RET/padding and ends with RET.
// No entry references were found. int/cdecl here is a word-transport view;
// original formal count, parameter type and ABI spelling remain unknown.
void rva006CD010SetDiagnosticWord(int word)
{
    g_rva00891FA0Ready = word;
    g_rva00891FA0Value = 0;
}
