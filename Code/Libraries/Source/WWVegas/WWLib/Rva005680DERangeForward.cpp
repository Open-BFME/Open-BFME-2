// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva005680DEInput;
struct Rva005680DEOutput;
struct Rva005680DEIteratorTag {};
Rva005680DEOutput* __cdecl Rva005680DERangeCallee(Rva005680DEOutput*first,unsigned int count,const Rva005680DEInput*value,const Rva005680DEIteratorTag&);

Rva005680DEOutput* __cdecl Rva005680DERangeForward(Rva005680DEOutput*first,unsigned int count,const Rva005680DEInput*value)
{
    Rva005680DEIteratorTag category;
    return Rva005680DERangeCallee(first,count,value,category);
}

#pragma comment(linker, "/alternatename:?Rva005680DERangeCallee@@YAPAURva005680DEOutput@@PAU1@IPBURva005680DEInput@@ABURva005680DEIteratorTag@@@Z=?Rva00567FFCFill@@YAPAVRva00567BD7@@PAV1@IPBV1@@Z")
