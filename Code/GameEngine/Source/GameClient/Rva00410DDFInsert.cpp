// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?rva00410DDF@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UTreeHintPayload00410A86@@@_STL@@PBU23@@Z, retail 0x00410DDF 68B. Hashtable insert
// over the Eva bucket vector for the AsciiString-keyed 12-byte node family.
// Buckets at +4 count at +0x10 (same layout as rowed erase 0x00223429 and
// bucketIndex 0x00223149). Resizes via pin 0x00212858 with count+1 hashes key
// via rowed 0x00223149 allocates node via pinned twin 0x00410A86 (ICF twin of
// free NewNode) links old head bumps count returns value at +4. Same shape as
// landed 0x00410E67 68B insert. Caller 0x0041117B in 0x0041112B.
#include "ascii_string.h"

struct TreeHintPayload00410A86
{
	unsigned char m_body[4];
};

namespace _STL {
template <class T1, class T2> struct pair
{
	~pair();
	T1 first;
	T2 second;
};
}

#include "../../Include/GameLogic/Rva000427195.h"

_STL::pair<const AsciiString, TreeHintPayload00410A86> *Rva000427195::rva00410DDF(const _STL::pair<const AsciiString, TreeHintPayload00410A86> *arg)
{
	rva00212858(m_numElements + 1);
	int bucket = bucketIndex(&arg->first);
	void *old = m_beginBuckets[bucket];
	void *n = rva00410A86(arg);
	*(void **)n = old;
	m_beginBuckets[bucket] = n;
	++m_numElements;
	return (_STL::pair<const AsciiString, TreeHintPayload00410A86> *)((char *)n + 4);
}

// Native41112B..4111C7 RET4: default reference insertion in the screen table.
// Constructor50EDB3 writes exactly an8-byte key/reference record; cleanup
// 410688 releases reference+4 then string+0. Keep both existing owners.
// This call-only specialization holds that native record without imposing
// the other tree table's cleanup2175CE on the screen table's temporary.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C() {if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}

#include "../../Include/Common/Rva00410688.h"
namespace _STL {
template<> struct pair<const AsciiString,TreeHintRef00217D4C> {
 pair(const AsciiString &,const TreeHintRef00217D4C &);
 __forceinline ~pair(){((Rva00410688*)this)->~Rva00410688();}
 union {unsigned int m_alignment;unsigned char m_native[8];};
};
}
typedef _STL::pair<const AsciiString,TreeHintRef00217D4C> ScreenRefPair;
class Rva00056F61;
#include "../../Include/GameClient/Rva0041534BIter.h"
#include "../../Include/GameClient/Rva00056F61.h"
void *Rva000427195::rva0041112B(const AsciiString *name) {
 void *node;
 {Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(name);node=found.m_node;}
 return !node ? (char *)rva00410DDF((const _STL::pair<const AsciiString,TreeHintPayload00410A86> *)
  &static_cast<const ScreenRefPair &>(ScreenRefPair(*name,TreeHintRef00217D4C())))+4 : (char *)node+8;
}
