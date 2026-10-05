// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva00541231Input;
struct Rva00541231Output;
struct Rva00541231IteratorTag {};
Rva00541231Output* __cdecl Rva00541231RangeCallee(Rva00541231Input*first,Rva00541231Input*last,Rva00541231Output*result,const Rva00541231IteratorTag&,int*);

Rva00541231Output* __cdecl Rva00541231RangeForward(Rva00541231Input*first,Rva00541231Input*last,Rva00541231Output*result,const Rva00541231IteratorTag&)
{
    Rva00541231IteratorTag category;
    return Rva00541231RangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva00541231RangeCallee@@YAPAURva00541231Output@@PAURva00541231Input@@0PAU1@ABURva00541231IteratorTag@@PAH@Z=?Rva005410B1Copy@@YAPAVRva0054103E@@PAV1@00@Z")
