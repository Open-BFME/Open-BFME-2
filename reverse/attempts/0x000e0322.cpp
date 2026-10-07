// ?rva000E0322@Rva000E0322@@QAEXI@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /MD /EHs- /EHc-
// ?Rva000E007DEqual@@YGHPBURva000E007DPair@@0@Z recurring, retail 0x000E007D, 32B.
// Equality on two-int pairs via two dword compares returning int 0/1.
// Callers 0x000E01DD (tests al) 0x000E02D1. Honest free-function name.
// __stdcall for ret 8 (callee pops 8, no add esp in callers).
struct Rva000E007DPair
{
	int m00;
	int m04;
};

int __stdcall Rva000E007DEqual(const Rva000E007DPair *a, const Rva000E007DPair *b)
{
	if (a->m00 != b->m00 || a->m04 != b->m04)
		return 0;
	return 1;
}

// Native E0322..E03DD: STLport4.5.3 resize from BF1 ba7dd _hashtable.c.
// Nodes link at0; two-word XOR key at4/8 is independently established by
// hash E0197/E01F4 and lookup E01B0 calling this unit's equality E007D.
// Element size and original table identity remain unknown. The next-size
// routine accesses no receiver fields; reuse its established Armor provider
// spelling without identifying this table as Armor. Vector/free spellings
// name their verified providers; new-head reference preserves native stores.
void __cdecl free(void*);
class Rva000E0322;
namespace _STL {
template<class T>class allocator {public:allocator(){} allocator(const allocator&){} };
template<class T,class A>class vector {
public:T*first,*last,*end;
vector(unsigned int,const T&,const A&);
A get_allocator()const;
void swap(vector&);
~vector(){if(first)free(first);}
unsigned int size()const{return last-first;}
T&operator[](unsigned int i){return first[i];}
};
template<class A,class B>struct pair;
template<class P>struct _Select1st;
template<class T>struct equal_to;
template<class V,class K,class H,class E,class Eq,class A>class hashtable {friend class ::Rva000E0322;private:unsigned int _M_next_size(unsigned int)const;};
}
enum NameKeyType;
class ArmorTemplate;
namespace rts {template<class T>struct hash;template<class T>struct equal_to;}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorValue;
typedef _STL::hashtable<ArmorValue,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorValue>,rts::equal_to<NameKeyType>,_STL::allocator<ArmorValue> > NextSizeProvider;
struct Rva000E0322Node {Rva000E0322Node*next;unsigned int key0,key1;};
class Rva000E0322 {
public:void rva000E0322(unsigned int hint);
private:unsigned int word0;_STL::vector<void*,_STL::allocator<void*> > buckets;
};
void Rva000E0322::rva000E0322(unsigned int hint){
 unsigned int oldSize=buckets.size();
 if(hint>oldSize){
  unsigned int newSize=((const NextSizeProvider*)this)->_M_next_size(hint);
  if(newSize>oldSize){
   _STL::vector<void*,_STL::allocator<void*> > tmp(newSize,(void*)0,buckets.get_allocator());
   for(unsigned int bucket=0;bucket<oldSize;++bucket){
    Rva000E0322Node*first=(Rva000E0322Node*)buckets[bucket];
    while(first){
     unsigned int newBucket=(first->key0^first->key1)%newSize;
     buckets[bucket]=first->next;
     void*& newHead=tmp[newBucket];
     first->next=(Rva000E0322Node*)newHead;
     newHead=first;
     first=(Rva000E0322Node*)buckets[bucket];
    }
   }
   buckets.swap(tmp);
  }
 }
}
