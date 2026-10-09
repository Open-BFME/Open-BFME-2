// ?rva0002C7FD@Rva0002C7FD@@QAEXI@Z
// partial score=0.92 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /G7
// stlport
#include <vector>
#include "ascii_string.h"
void Rva00030830FreeAllocation(void *);
template<> inline _STL::_Vector_base<void*,_STL::allocator<void*> >::~_Vector_base() {
 if(this->_M_start) Rva00030830FreeAllocation(this->_M_start);
}
class Rva0002C7FD;
enum NameKeyType { RvaRehashNameKeyWidth = 0x7fffffff };
class ArmorTemplate;
namespace rts {
 template<class T> struct hash;
 template<class T> struct equal_to;
 template<> struct hash<AsciiString> { unsigned int operator()(const AsciiString &) const; };
}
namespace _STL {
 template<class T> struct _Select1st;
 template<class V, class K, class H, class E, class Q, class A>
 class hashtable {
  friend class ::Rva0002C7FD;
  unsigned int _M_next_size(unsigned int) const;
 };
}
typedef _STL::pair<const NameKeyType, ArmorTemplate> RvaRehashPrimePair;
typedef _STL::hashtable<RvaRehashPrimePair,NameKeyType,rts::hash<NameKeyType>,
 _STL::_Select1st<RvaRehashPrimePair>,rts::equal_to<NameKeyType>,
 _STL::allocator<RvaRehashPrimePair> > RvaRehashPrimeProvider;
template<> _STL::vector<void*>::allocator_type _STL::vector<void*>::get_allocator() const;
template<> _STL::vector<void*>::vector(size_type, void * const &, const allocator_type &);
template<> void _STL::vector<void*>::swap(_STL::vector<void*> &);
// Only the node prefix is viewed. This function never allocates a node,
// computes its full size, or reads the unnamed payload following the key.
struct Rva0002C7FDNodePrefix { Rva0002C7FDNodePrefix *next; AsciiString key; };
class Rva0002C7FD {
public: void rva0002C7FD(unsigned int hint);
private:
 rts::hash<AsciiString> hash;
 _STL::vector<void*> buckets;
 unsigned int count;
 unsigned int bucketForKey(const AsciiString &key,unsigned int n) const { return hash(key)%n; }
};
void Rva0002C7FD::rva0002C7FD(unsigned int hint) {
 const unsigned int oldCount=buckets.size();
 if(hint>oldCount) {
  // Reuse the existing receiver-independent prime chooser. Its48B target
  // body never reads ECX; this projection claims neither Armor payload nor
  // original container specialization, and introduces no alias pin.
  const unsigned int n=reinterpret_cast<const RvaRehashPrimeProvider*>(this)->_M_next_size(hint);
  if(n>oldCount) {
   _STL::vector<void*> tmp(n,(void*)0,buckets.get_allocator());
   {
   for(unsigned int b=0;b<oldCount;++b) {
    Rva0002C7FDNodePrefix *first=static_cast<Rva0002C7FDNodePrefix*>(buckets[b]);
    while(first) {
     unsigned int newBucket=bucketForKey(first->key,n);
     buckets[b]=first->next;
     void *&newHead=*(newBucket+tmp.begin());
     first->next=static_cast<Rva0002C7FDNodePrefix*>(newHead);
     newHead=first;
     first=static_cast<Rva0002C7FDNodePrefix*>(buckets[b]);
    }
   }
   buckets.swap(tmp);
   }
  }
 }
}
