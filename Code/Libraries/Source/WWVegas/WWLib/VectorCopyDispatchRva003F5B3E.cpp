// cl: /O1 /G7 /MD /DNDEBUG
// Target Ghidra [3F5B3E,3F5B5B),29B. The native51B range erase
// 3F5EC4 passes three pointers plus an empty const-reference dispatch arg.
// The dispatcher ignores that arg and calls full50B countedcopy3F58F8
// with a local empty iterator tag and null distance pointer. The 50B
// provider reads the first three arguments; both additional dispatch
// arguments are unused at this instantiated call ABI. Native strides
// and assignment calls establish48B records; fields/application unknown.
// This is the STLport __copy_ptrs dispatch algorithm. Original empty tag
// and application record names remain unproved; scoped views below bind
// a verified full provider without claiming its original full signature.
struct Rva003F5B3ERecord {char consumed[48];};
struct Rva003F5B3EEmpty {};
// ?Rva003F5B3ETag::Rva003F5B3ETag absent-from-retail
// The empty dispatch tag constructor is inlined in the native wrapper.
struct Rva003F5B3ETag {Rva003F5B3ETag(){}};
Rva003F5B3ERecord *copyDeep(Rva003F5B3ERecord*,Rva003F5B3ERecord*,Rva003F5B3ERecord*,const Rva003F5B3ETag&,int*);
Rva003F5B3ERecord *backwardDeep(Rva003F5B3ERecord*,Rva003F5B3ERecord*,Rva003F5B3ERecord*,const Rva003F5B3ETag&,int*);
__declspec(noinline) Rva003F5B3ERecord *copyDispatchRva003F5B3E(Rva003F5B3ERecord *first,Rva003F5B3ERecord *last,Rva003F5B3ERecord *out,const Rva003F5B3EEmpty&){return copyDeep(first,last,out,Rva003F5B3ETag(),0);}

#pragma comment(linker, "/alternatename:?copyDeep@@YAPAURva003F5B3ERecord@@PAU1@00ABURva003F5B3ETag@@PAH@Z=?Rva003F58F8Copy@@YAPADPAD00@Z")
