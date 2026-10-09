// cl: /O1 /G7 /MD /EHsc
// Native5EFD8F..5EFDDB76B; WB1618180 same allocation/member-store flow.
// Class owner from existing destructor5EFDDB and vtableC78964. Impl64B
// allocation and constructor5EF92D proven by this caller; implementation identity unresolved.
class Rva005EF92D {public:Rva005EF92D(unsigned, const void *,int);private:char storage[0x40];};
class Rva005EFDDB {public:Rva005EFDDB(unsigned,const void *,int);virtual ~Rva005EFDDB();private:Rva005EF92D *impl;};
Rva005EFDDB::Rva005EFDDB(unsigned level,const void *name,int color):impl(new Rva005EF92D(level,name,color)){}
