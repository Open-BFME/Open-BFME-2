// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; the link alias preserves
// its existing provider instead of introducing another range-loop definition.
struct Rva000ADF1BInput;
struct Rva000ADF1BOutput;
struct Rva000ADF1BIteratorTag {};
Rva000ADF1BOutput* __cdecl Rva000ADF1BRangeCallee(Rva000ADF1BInput*first,Rva000ADF1BInput*last,Rva000ADF1BOutput*result,const Rva000ADF1BIteratorTag&,int*);

Rva000ADF1BOutput* __cdecl Rva000ADF1BRangeForward(Rva000ADF1BInput*first,Rva000ADF1BInput*last,Rva000ADF1BOutput*result,const Rva000ADF1BIteratorTag&)
{
    Rva000ADF1BIteratorTag category;
    return Rva000ADF1BRangeCallee(first,last,result,category,0);
}

#pragma comment(linker, "/alternatename:?Rva000ADF1BRangeCallee@@YAPAURva000ADF1BOutput@@PAURva000ADF1BInput@@0PAU1@ABURva000ADF1BIteratorTag@@PAH@Z=?Rva000AD8EBCopy@@YAPAHPAF0PAH@Z")
