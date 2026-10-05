// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva0032E51BInput;
struct Rva0032E51BOutput;
struct Rva0032E51BIteratorTag {};
Rva0032E51BOutput* __cdecl Rva0032E51BRangeCallee(Rva0032E51BInput*first,Rva0032E51BInput*last,Rva0032E51BOutput*result,const Rva0032E51BIteratorTag&,int*);

Rva0032E51BOutput* __cdecl Rva0032E51BRangeForward(Rva0032E51BInput*first,Rva0032E51BInput*last,Rva0032E51BOutput*result,const Rva0032E51BIteratorTag&)
{
    Rva0032E51BIteratorTag category;
    return Rva0032E51BRangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva0032E51BRangeCallee@@YAPAURva0032E51BOutput@@PAURva0032E51BInput@@0PAU1@ABURva0032E51BIteratorTag@@PAH@Z=?Rva0032DD81Copy@@YAPAVSidesInfo@@PAV1@00@Z")
