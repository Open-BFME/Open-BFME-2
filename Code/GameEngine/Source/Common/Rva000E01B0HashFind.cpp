// cl: /O1 /G7 /MD /EHsc
// Native E01B0..E01F4 and caller E0584: two-word key, bucket pointers at
// +4/+8, link at node+0 and key at node+4. STLport hashtable::_M_find is
// the structural guide; the concrete container/key identity is unproven.
// Owned E007D returns 0/1 in EAX and pops both arguments; this call site
// supplies the otherwise unused empty-predicate receiver at this+1 and
// tests AL. The member-call view preserves that witnessed ABI without a
// new pin or a different name for the equality body. The scheduling fence
// reloads the bucket pointer after modulus, matching the native registers.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct Rva000E007DPair {int m00,m04;};
int __stdcall Rva000E007DEqual(const Rva000E007DPair*,const Rva000E007DPair*);
struct NativeNode {NativeNode*next;Rva000E007DPair key;};
class NativeHashEqual {public:bool equal(const Rva000E007DPair*a,const Rva000E007DPair*b){union Call{int(__stdcall*fn)(const Rva000E007DPair*,const Rva000E007DPair*);bool(NativeHashEqual::*mem)(const Rva000E007DPair*,const Rva000E007DPair*);}c;c.fn=&Rva000E007DEqual;return (this->*c.mem)(a,b);}};
class Rva000E01B0 {public:NativeNode*rva000E01B0(const Rva000E007DPair*key);private:char hash;NativeHashEqual eq;char pad[2];NativeNode**begin,**end;};
NativeNode*Rva000E01B0::rva000E01B0(const Rva000E007DPair*key){unsigned n=end-begin;unsigned index=(unsigned)(key->m00^key->m04)%n;_ReadWriteBarrier();NativeNode*p=begin[index];while(p&&!eq.equal(&p->key,key))p=p->next;return p;}
