// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva0032DD66Input;
struct Rva0032DD66Output;
struct Rva0032DD66IteratorTag {};
Rva0032DD66Output* __cdecl Rva0032DD66RangeCallee(Rva0032DD66Input*first,Rva0032DD66Input*last,Rva0032DD66Output*result,const Rva0032DD66IteratorTag&);

Rva0032DD66Output* __cdecl Rva0032DD66RangeForward(Rva0032DD66Input*first,Rva0032DD66Input*last,Rva0032DD66Output*result)
{
    Rva0032DD66IteratorTag category;
    return Rva0032DD66RangeCallee(first,last,result,category);
}

#pragma comment(linker, "/alternatename:?Rva0032DD66RangeCallee@@YAPAURva0032DD66Output@@PAURva0032DD66Input@@0PAU1@ABURva0032DD66IteratorTag@@@Z=??$__copy_ptrs@PAURva0032CD3BRecord@@PAU1@@_STL@@YAPAURva0032CD3BRecord@@PAU1@00ABU__false_type@0@@Z")
