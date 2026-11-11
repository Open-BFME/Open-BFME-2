// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva0022B0B8Subsystem@@UAE@XZ, retail 0x003EF36E (137B, EH): destructor of a
// SubsystemInterface-derived owner (vftable 0x00C363D8) whose +0x0C member is
// the ASCII-keyed hash table rowed as Rva003EF22B (dtor 0x003EF22B). It walks
// the table with the rowed begin 0x00427195 / next 0x00411084 cursor, deletes
// each entry's Rva003EF14A manager (dtor 0x003EF14A, then operator delete)
// and nulls the slot, clears the table (0x003A2A41), then the member and base
// destructors run. Names stay address-derived.
//
// Same-TU callee lever: the cursor helpers' bodies (byte-identical spellings
// of the rowed 0x00427195 / 0x00411084 / 0x003F7925, as in PlayerUpdate.cpp
// and LivingWorldManagerXferObjects.cpp) are defined here, so cl knows the
// cursor never escapes: this stays in esi, the table in ebx and the node in
// edi as in retail (declared only, the 0.72 bank swapped those roles and
// grew a frame slot).
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include "../../Include/Common/Rva003EF14A.h"
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end
struct AudioCacheCursor
{
	struct { void *first, *second; } s;
	AudioCacheCursor(void *a, void *b) { s.first = a; s.second = b; }
	AudioCacheCursor(const AudioCacheCursor &audioCacheCursor) { s.first = audioCacheCursor.s.first; s.second = audioCacheCursor.s.second; }
};

#include "../../Include/GameLogic/Rva000427195.h"

__declspec(noinline) inline AudioCacheCursor Rva000427195::rva00427195()	// 0x00427195
{
	for (unsigned n = 0; n < (unsigned)(m_endBuckets - m_beginBuckets); ++n)
		if (m_beginBuckets[n])
			return AudioCacheCursor(m_beginBuckets[n], this);
	return AudioCacheCursor(0, this);
}

#include "../../Include/GameClient/Rva000411084.h"

// Keep the native inline bodies visible to preserve cl's alias analysis.
__declspec(noinline) inline void *Rva000411084::next()					// 0x00411084
{
	void *node = *(void **)m_current;
	if (node == 0)
		node = advance();
	m_current = node;
	return this;
}
__declspec(noinline) inline void *Rva000411084::advance()				// 0x003F7925
{
	struct Table
	{
		void *m_unused00;
		union {
			void **m_beginBuckets;
			void ** volatile m_beginBucketsVolatile;
		};
		void **m_endBuckets;
	};
	Table *table = (Table *)m_owner;
	unsigned index = (unsigned)((Rva000427195 *)table)->bucketIndex((const AsciiString *)((char *)m_current + 4));
	unsigned count = (unsigned)(((char *)table->m_endBuckets - (char *)table->m_beginBuckets) >> 2);
	void *head = 0;
	do {
		++index;
		if (index >= count)
			break;
		head = table->m_beginBucketsVolatile[index];
	} while (head == 0);
	return head;
}


void Rva00030830GameFree(void*);
struct S3RegionBucketStorage {~S3RegionBucketStorage(){if(begin)Rva00030830GameFree(begin);}void**begin;void**end;void**capacity;};
struct Rva003EF22B {void*unused;S3RegionBucketStorage buckets;unsigned count;~Rva003EF22B();};
// ~Rva003EF22B is rowed in Rva003EF22BTableDtor.cpp (0x003EF22B).
class Rva0022B0B8Subsystem :public SubsystemInterface {
public:virtual ~Rva0022B0B8Subsystem();virtual void init(){}virtual void reset(){}virtual void update(){}
private:Rva003EF22B table;
};
Rva0022B0B8Subsystem::~Rva0022B0B8Subsystem()
{
	AudioCacheCursor it = ((Rva000427195 *)&table)->rva00427195();
	void *node;
	while ((node = it.s.first) != 0)
	{
		Rva003EF14A *&manager = *(Rva003EF14A **)((char *)node + 8);
		delete manager;
		manager = 0;
		((Rva000411084 *)&it)->next();
	}
	((Rva000427195 *)&table)->rva003A2A41();
}
