// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva001DEE3CInput;
struct Rva001DEE3COutput;
struct Rva001DEE3CIteratorTag {};
Rva001DEE3COutput* __cdecl Rva001DEE3CRangeCallee(Rva001DEE3CInput*first,Rva001DEE3CInput*last,Rva001DEE3COutput*result,const Rva001DEE3CIteratorTag&,int*);

Rva001DEE3COutput* __cdecl Rva001DEE3CRangeForward(Rva001DEE3CInput*first,Rva001DEE3CInput*last,Rva001DEE3COutput*result,const Rva001DEE3CIteratorTag&)
{
    Rva001DEE3CIteratorTag category;
    return Rva001DEE3CRangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva001DEE3CRangeCallee@@YAPAURva001DEE3COutput@@PAURva001DEE3CInput@@0PAU1@ABURva001DEE3CIteratorTag@@PAH@Z=?Rva001DE938CopyBackward@@YAPAVRva001DE727@@PAV1@00@Z")
