// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva001EBACFInput;
struct Rva001EBACFOutput;
struct Rva001EBACFIteratorTag {};
Rva001EBACFOutput* __cdecl Rva001EBACFRangeCallee(Rva001EBACFInput*first,Rva001EBACFInput*last,Rva001EBACFOutput*result,const Rva001EBACFIteratorTag&);

Rva001EBACFOutput* __cdecl Rva001EBACFRangeForward(Rva001EBACFInput*first,Rva001EBACFInput*last,Rva001EBACFOutput*result)
{
    Rva001EBACFIteratorTag category;
    return Rva001EBACFRangeCallee(first,last,result,category);
}

#pragma comment(linker, "/alternatename:?Rva001EBACFRangeCallee@@YAPAURva001EBACFOutput@@PAURva001EBACFInput@@0PAU1@ABURva001EBACFIteratorTag@@@Z=??$__copy_ptrs@PAUBfmeAssignRecord172@@PAU1@@_STL@@YAPAUBfmeAssignRecord172@@PAU1@00U__false_type@0@@Z")
