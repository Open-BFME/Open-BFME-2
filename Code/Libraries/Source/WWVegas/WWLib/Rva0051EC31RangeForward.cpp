// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva0051EC31Input;
struct Rva0051EC31Output;
struct Rva0051EC31IteratorTag {};
Rva0051EC31Output* __cdecl Rva0051EC31RangeCallee(Rva0051EC31Input*first,Rva0051EC31Input*last,Rva0051EC31Output*result,const Rva0051EC31IteratorTag&,int*);

Rva0051EC31Output* __cdecl Rva0051EC31RangeForward(Rva0051EC31Input*first,Rva0051EC31Input*last,Rva0051EC31Output*result,const Rva0051EC31IteratorTag&)
{
    Rva0051EC31IteratorTag category;
    return Rva0051EC31RangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva0051EC31RangeCallee@@YAPAURva0051EC31Output@@PAURva0051EC31Input@@0PAU1@ABURva0051EC31IteratorTag@@PAH@Z=?Rva0051E939Copy@@YAPAVRva0051E437@@PAV1@00@Z")
