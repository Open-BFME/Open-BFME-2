// cl: /DNDEBUG /MD /EHsc
// ?Rva003EF6D6Contains@@YG_NPAURva003EF6D6Span@@PAURva003EF6D6Entry@@@Z, retail 0x003EF6D6, 45 bytes.
// Free __stdcall contains check over a two-pointer span of entry pointers;
// compares each element pointer to the value arg and returns true on hit
// else false. Callees none. Callers 0x003EF955 0x003EF965 in 0x003EF8E1.
// Neighbour of 0x003EF6A0 find-by-key and 0x003EF728 dtor. Honest address
// name; entry and span roles unproven.
struct Rva003EF6D6Entry
{
    int unused00;
};
struct Rva003EF6D6Span
{
    Rva003EF6D6Entry **begin;
    Rva003EF6D6Entry **end;
};

bool __stdcall Rva003EF6D6Contains(Rva003EF6D6Span *span, Rva003EF6D6Entry *value)
{
    unsigned i = 0;
    unsigned count = (unsigned)(span->end - span->begin);
    for (; i < count; ++i) {
        if (span->begin[i] == value)
            return true;
    }
    return false;
}
