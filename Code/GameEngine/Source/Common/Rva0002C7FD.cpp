// ?resize@Rva0002C7FD@@QAEXI@Z
// partial score=0.99 date=2026-10-13
// ?resize@Rva0002C7FD@@QAEXI@Z
// partial score=0.99 date=2026-10-10
// ?resize@Rva0002C7FD@@QAEXI@Z
// partial score=0.99
// 214B; no volatile hacks (plain tmp[newBucket]). Only difference: retail loads newBucket ([ebp-0x1c]) into ECX before tmp.start ([ebp-0x28]) into EAX; cl loads the base first (2 lines). 14 operand-order forms of the address (k+p, p[k], k[p], char* arithmetic, begin()+k) are canonicalized to the same code.
// ?resize@Rva0002C7FD@@QAEXI@Z
// partial score=0.985981308411215 date=2026-10-10
// ?resize@Rva0002C7FD@@QAEXI@Z
// partial score=0.9813 date=2026-10-09
// ?resize@Rva0002C7FD@@QAEXI@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// R1 template_visibility closure (W8-T4LEAD): dropping the three explicit vector<void*> specialization declarations removes a mov-swap wall; exact 214B. Dedicated TU.
// stlport
// Successive local union members reuse the native zero-value/counter home;
// this records temporary lifetime, not a recovered class or payload type.
// The full native214B shape now agrees except the two independent MOVs
// at2C881/2C884 are exchanged. Every direct callee resolves.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_LOWER_BOUND_EXTERN  // bind the prime-list search to its shared retail provider
// STLport frees through the game's plain _free at 0x00030830, not the CRT import.
#define free BfmeCrtImportedFree
#include <stdlib.h>
#include <malloc.h>
#undef free
extern "C" void __cdecl free(void *) throw(...);
#include "ascii_string.h"
#include <hash_map>

namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
	template <class T> struct equal_to
	{
	};
	template <> struct equal_to<AsciiString>
	{
		// Expanded in place; the file emits no out-of-line copy of this functor.
		__declspec(dllimport) __forceinline bool operator()(const AsciiString &a, const AsciiString &b) const
		{
			return a.compareNoCase(b) == 0;
		}
	};
}

// Keep the inline bucket-vector access while binding outlined copies to
// the shared retail helpers instead of emitting this unit's /O1 variants.
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const
{ return this->_M_start; }
template <> __declspec(dllimport) __forceinline
vector<void *>::size_type vector<void *>::size() const
{ return size_type(this->_M_finish - this->_M_start); }
// The bucket lookup in hashtable::_M_find<AsciiString> inlines this too; left out of
// line, this unit's _M_find copy differs from retail's 0x0002C9E7 and, first in link
// order, would be the one the link keeps.
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const
{ return *(begin() + __n); }
}

// The rehash and teardown code expand the bucket access in place.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }

namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}

namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }

// bfme link decl-only end
class Rva0002C7FD;
enum NameKeyType { RvaRehashNameKeyWidth = 0x7fffffff };
class ArmorTemplate;
typedef _STL::pair<const NameKeyType, ArmorTemplate> RvaRehashPrimePair;
namespace _STL {
// Only the receiver-independent prime chooser of this table is viewed.
template <>
class hashtable<RvaRehashPrimePair,NameKeyType,rts::hash<NameKeyType>,
 _Select1st<RvaRehashPrimePair>,rts::equal_to<NameKeyType>,
 allocator<RvaRehashPrimePair> > {
  friend class ::Rva0002C7FD;
  unsigned int _M_next_size(unsigned int) const;
};
}
typedef _STL::hashtable<RvaRehashPrimePair,NameKeyType,rts::hash<NameKeyType>,
 _STL::_Select1st<RvaRehashPrimePair>,rts::equal_to<NameKeyType>,
 _STL::allocator<RvaRehashPrimePair> > RvaRehashPrimeProvider;

// Only the node prefix is viewed. This function never allocates a node,
// computes its full size, or reads the unnamed payload following the key.
struct Rva0002C7FDNodePrefix { Rva0002C7FDNodePrefix *next; AsciiString key; };
class Rva0002C7FD
{
public:
	void resize(unsigned int);
private:
	unsigned int bucketForKey(const AsciiString &key,unsigned int bucketCount) const { return hash(key)%bucketCount; }
	rts::hash<AsciiString> hash; // +0x00
	char m_pad01[0x3];
	_STL::vector<void*> buckets; // +0x04
	unsigned int count; // +0x10
};
void Rva0002C7FD::resize(unsigned int hint) {
 const unsigned int oldCount=buckets.size();
 if(hint>oldCount) {
  // Reuse the existing receiver-independent prime chooser. Its48B target
  // body never reads ECX; this projection claims neither Armor payload nor
  // original container specialization, and introduces no alias pin.
  const unsigned int newBucketCount=reinterpret_cast<const RvaRehashPrimeProvider*>(this)->_M_next_size(hint);
  if(newBucketCount>oldCount) {
   union BucketConstructionScratch { void *empty; unsigned int bucket; } scratch;
   scratch.empty = 0;
   _STL::vector<void*> tmp(newBucketCount,scratch.empty,buckets.get_allocator());
   {
   for(scratch.bucket=0;scratch.bucket<oldCount;++scratch.bucket) {
    Rva0002C7FDNodePrefix *first=static_cast<Rva0002C7FDNodePrefix*>(buckets[scratch.bucket]);
    while(first) {
     unsigned int newBucket=bucketForKey(first->key,newBucketCount);
     buckets[scratch.bucket]=first->next;
     void *&newHead=tmp[newBucket];
     first->next=static_cast<Rva0002C7FDNodePrefix*>(newHead);
     newHead=first;
     first=static_cast<Rva0002C7FDNodePrefix*>(buckets[scratch.bucket]);
    }
   }
   buckets.swap(tmp);
   }
  }
 }
}
