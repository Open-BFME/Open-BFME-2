// cl: /Ireference/shims/bfme2_ascii /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva002234BA@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@PBU23@@Z @0x002234BA 68B
// Hash insert old-before-new over the Eva bucket vector. Buckets at +4,
// count at +0x10 (same layout as rowed erase 0x00223429 and bucketIndex
// 0x00223149). Resizes via pin 0x00212858 with count+1, hashes key via rowed
// 0x00223149, allocates node via rowed 0x002230FF, links old head, bumps
// count, returns value at +4. Same shape as landed 0x00223854 68B insert.
// Callers 0x0022363A. Returns pair pointer for LINK BONUS style callers.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../Include/Common/NoCaseTreeValue4.h"

namespace _STL {
template <class T1, class T2> struct pair
{
	~pair();
	T1 first;
	T2 second;
};
}

#include "../../Include/GameClient/Rva002230FF.h"

#include "../../Include/GameLogic/Rva000427195.h"

_STL::pair<const AsciiString, NoCaseTreeValue4> *Rva000427195::rva002234BA(const _STL::pair<const AsciiString, NoCaseTreeValue4> *entry)
{
	rva00212858(m_numElements + 1);
	int bucket = bucketIndex(&entry->first);
	void *old = m_beginBuckets[bucket];
	void *node = ((Rva002230FF *)this)->newNode(entry);
	*(void **)node = old;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return (_STL::pair<const AsciiString, NoCaseTreeValue4> *)((char *)node + 4);
}
