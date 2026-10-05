// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva000C24CDInput;
struct Rva000C24CDOutput;
struct Rva000C24CDIteratorTag {};
Rva000C24CDOutput* __cdecl Rva000C24CDRangeCallee(Rva000C24CDInput*first,Rva000C24CDInput*last,Rva000C24CDOutput*result,const Rva000C24CDIteratorTag&,int*);

Rva000C24CDOutput* __cdecl Rva000C24CDRangeForward(Rva000C24CDInput*first,Rva000C24CDInput*last,Rva000C24CDOutput*result,const Rva000C24CDIteratorTag&)
{
    Rva000C24CDIteratorTag category;
    return Rva000C24CDRangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva000C24CDRangeCallee@@YAPAURva000C24CDOutput@@PAURva000C24CDInput@@0PAU1@ABURva000C24CDIteratorTag@@PAH@Z=?Rva000C0D13Copy@@YAPAUBfmeVectorRecord000BDF17@@PAU1@00@Z")
