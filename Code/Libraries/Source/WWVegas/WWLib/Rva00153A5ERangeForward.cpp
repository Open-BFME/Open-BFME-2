// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva00153A5EInput;
struct Rva00153A5EOutput;
struct Rva00153A5EIteratorTag {};
Rva00153A5EOutput* __cdecl Rva00153A5ERangeCallee(Rva00153A5EInput*first,Rva00153A5EInput*last,Rva00153A5EOutput*result,const Rva00153A5EIteratorTag&,int*);

Rva00153A5EOutput* __cdecl Rva00153A5ERangeForward(Rva00153A5EInput*first,Rva00153A5EInput*last,Rva00153A5EOutput*result,const Rva00153A5EIteratorTag&)
{
    Rva00153A5EIteratorTag category;
    return Rva00153A5ERangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva00153A5ERangeCallee@@YAPAURva00153A5EOutput@@PAURva00153A5EInput@@0PAU1@ABURva00153A5EIteratorTag@@PAH@Z=?Rva001539ECCopyBackward@@YAPAVRva001539BC@@PAV1@00@Z")
