// cl: /DNDEBUG /MD /EHsc
// ?Rva003EF648Index@@YGHPAURva003EF648Span@@H@Z, retail 0x003EF648, 46 bytes.
// Free __stdcall index lookup over a two-pointer span of record pointers;
// compares the value against the first dword of each pointed-to record and
// returns the index or -1. Neighbour of indexOf at 0x003EF676. Caller
// 0x003EF7E9 unblocks 0x003EF7DF. Honest address name; element type unproven.
struct Rva003EF648Item
{
    int id;
};

struct Rva003EF648Span
{
    Rva003EF648Item **begin;
    Rva003EF648Item **end;
};

int __stdcall Rva003EF648Index(Rva003EF648Span *span, int value)
{
    unsigned i = 0;
    unsigned count = (unsigned)(span->end - span->begin);
    for (; i < count; ++i) {
        if (value == span->begin[i]->id)
            return (int)i;
    }
    return -1;
}
