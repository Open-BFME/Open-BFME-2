// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva002B5944Input;
struct Rva002B5944Output;
struct Rva002B5944IteratorTag {};
Rva002B5944Output* __cdecl Rva002B5944RangeCallee(Rva002B5944Input*first,Rva002B5944Input*last,Rva002B5944Output*result,const Rva002B5944IteratorTag&);

Rva002B5944Output* __cdecl Rva002B5944RangeForward(Rva002B5944Input*first,Rva002B5944Input*last,Rva002B5944Output*result)
{
    Rva002B5944IteratorTag category;
    return Rva002B5944RangeCallee(first,last,result,category);
}

#pragma comment(linker, "/alternatename:?Rva002B5944RangeCallee@@YAPAURva002B5944Output@@PAURva002B5944Input@@0PAU1@ABURva002B5944IteratorTag@@@Z=??$__copy_backward_ptrs@PAURva002B3049Record@@PAU1@@_STL@@YAPAURva002B3049Record@@PAU1@00ABU__false_type@0@@Z")
