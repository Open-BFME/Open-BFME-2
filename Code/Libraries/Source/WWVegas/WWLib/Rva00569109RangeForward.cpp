// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva00569109Input;
struct Rva00569109Output;
struct Rva00569109IteratorTag {};
Rva00569109Output* __cdecl Rva00569109RangeCallee(Rva00569109Input*first,Rva00569109Input*last,Rva00569109Output*result,const Rva00569109IteratorTag&,int*);

Rva00569109Output* __cdecl Rva00569109RangeForward(Rva00569109Input*first,Rva00569109Input*last,Rva00569109Output*result,const Rva00569109IteratorTag&)
{
    Rva00569109IteratorTag category;
    return Rva00569109RangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva00569109RangeCallee@@YAPAURva00569109Output@@PAURva00569109Input@@0PAU1@ABURva00569109IteratorTag@@PAH@Z=?Rva00568EB4Copy@@YAPAVRva00568B4E@@PAV1@00@Z")
