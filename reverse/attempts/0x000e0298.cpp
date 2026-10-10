// ?rva000E0298@Rva000E01B0@@QAE?AUNativeInsertResult@@ABURva000E007DPair@@@Z
// partial score=0.9565 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct Rva000E007DPair {unsigned a,b;};
int __stdcall Rva000E007DEqual(const Rva000E007DPair*,const Rva000E007DPair*);
class NameKeyGenerator {public:class KeyToBucketMap {public:struct value_type{int first;void*second;};void*storageNode(const Rva000E007DPair&k){return allocateNode(*(const value_type*)&k);}private:void*allocateNode(const value_type&);};};
struct NativeNode {NativeNode*next;Rva000E007DPair key;};
class NativeHashEqual {public:bool equal(const Rva000E007DPair*a,const Rva000E007DPair*b){union Call{int(__stdcall*fn)(const Rva000E007DPair*,const Rva000E007DPair*);bool(NativeHashEqual::*mem)(const Rva000E007DPair*,const Rva000E007DPair*);}c;c.fn=&Rva000E007DEqual;return (this->*c.mem)(a,b);}};
class Rva000E01B0;struct NativeInsertResult {NativeNode*node;Rva000E01B0*owner;bool inserted;NativeInsertResult(NativeNode*n,Rva000E01B0*o,bool i):node(n),owner(o),inserted(i){}};
class Rva000E01B0 {public:NativeInsertResult rva000E0298(const Rva000E007DPair&key);NativeNode*rva000E01B0(const Rva000E007DPair*key);private:char hash;NativeHashEqual eq;char pad[2];NativeNode**begin,**end,**capacity;unsigned count;};
NativeNode*Rva000E01B0::rva000E01B0(const Rva000E007DPair*key){unsigned n=end-begin;unsigned index=(key->a^key->b)%n;_ReadWriteBarrier();NativeNode*p=begin[index];while(p&&!eq.equal(&p->key,key))p=p->next;return p;}

NativeInsertResult Rva000E01B0::rva000E0298(const Rva000E007DPair&key){unsigned n=end-begin;unsigned i=(key.a^key.b)%n;_ReadWriteBarrier();NativeNode*first=begin[i];for(NativeNode*p=first;p;p=p->next)if(eq.equal(&p->key,&key))return NativeInsertResult(p,this,false);NativeNode*p=(NativeNode*)((NameKeyGenerator::KeyToBucketMap*)this)->storageNode(key);p->next=first;begin[i]=p;++count;return NativeInsertResult(p,this,true);}
