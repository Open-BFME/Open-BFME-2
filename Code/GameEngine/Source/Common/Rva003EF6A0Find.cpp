// cl: /DNDEBUG /MD /EHsc
// ?Rva003EF6A0Find@@YGPAURva003EF6A0Entry@@PAURva003EF6A0Span@@H@Z, retail 0x003EF6A0, 54 bytes.
// Free __stdcall search of a two-pointer span of entry pointers for the entry
// whose +0 key equals the int arg; returns the entry pointer or null. Callees
// none. Callers 0x003EFA76 0x003EFA86 0x003EFB6E 0x003EFC39 unblock 0x003EFA0A.
// Honest address name; entry and span roles unproven.
struct Rva003EF6A0Entry
{
    int key;
};
struct Rva003EF6A0Span
{
    Rva003EF6A0Entry **begin;
    Rva003EF6A0Entry **end;
};

Rva003EF6A0Entry *__stdcall Rva003EF6A0Find(Rva003EF6A0Span *span, int value)
{
    unsigned i = 0;
    unsigned count = (unsigned)(span->end - span->begin);
    for (; i < count; ++i) {
        if (value == span->begin[i]->key)
            return span->begin[i];
    }
    return 0;
}
