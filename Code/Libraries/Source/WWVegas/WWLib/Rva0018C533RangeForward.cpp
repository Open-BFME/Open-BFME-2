// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva0018C533Input;
struct Rva0018C533Output;
struct Rva0018C533IteratorTag {};
Rva0018C533Output* __cdecl Rva0018C533RangeCallee(Rva0018C533Input*first,Rva0018C533Input*last,Rva0018C533Output*result,const Rva0018C533IteratorTag&);

Rva0018C533Output* __cdecl Rva0018C533RangeForward(Rva0018C533Input*first,Rva0018C533Input*last,Rva0018C533Output*result)
{
    Rva0018C533IteratorTag category;
    return Rva0018C533RangeCallee(first,last,result,category);
}

#pragma comment(linker, "/alternatename:?Rva0018C533RangeCallee@@YAPAURva0018C533Output@@PAURva0018C533Input@@0PAU1@ABURva0018C533IteratorTag@@@Z=?Rva0018C3C9Copy@@YAPAFPAURva0018C2E7Node@@0PAF@Z")
