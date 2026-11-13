// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc
// The 0x009F2A20 and 0x009F2A40 forwarders name this result maker.  The
// 0x009F39F0 constructor, 0x009F3C00 append method, and 0x009F2A70 predicate
// identify its result payload and linked-node filtering behavior.
//
// The payload is viewed raw here (the vector view lives in the append TU):
// retail destroys the item buffer with a plain free, not an stlport dtor.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

class Object;

// Partition filter base: allows (0x00625720) runs the chain from this filter
// along the +0x04 links.
#include "../../Include/GameLogic/PartitionFilter.h"

class BfmeResultNodeItem
{
public:
	virtual void bfmeSpare000(void) = 0;
	virtual void bfmeSpare001(void) = 0;
	virtual void bfmeSpare002(void) = 0;
	virtual void *bfmeGetResultThing(void) = 0;
};

struct BfmeResultNode
{
	void *m_bfmeUnused;
	BfmeResultNodeItem *m_bfmeItem;
	void *m_bfmeUnused2;
	BfmeResultNode *m_bfmeNext;
};

struct Rva009F39F0Payload
{
	void *m_start;
	void *m_finish;
	void *m_end;
	void *m_cursor;
	int m_refCount;
};

#include "../../Include/Common/Rva009F39F0Result.h"

typedef Rva009F39F0Payload BfmeResultPayload;

struct BfmeResultA : private Rva009F39F0Result
{
	BfmeResultA()
		: Rva009F39F0Result()
	{
	}
	__forceinline BfmeResultA(const BfmeResultA &that)
		: Rva009F39F0Result(*(const Rva009F39F0Result *)&that)
	{
		m_value = that.m_value;
		++m_value->m_refCount;
	}

	__forceinline ~BfmeResultA()
	{
		--m_value->m_refCount;
		if (m_value->m_refCount == 0)
		{
			BfmeResultPayload *payload = m_value;
			if (payload->m_start != 0)
				free(payload->m_start);
			::operator delete(payload);
		}
	}
};

class __declspec(novtable) PartitionManagerImpl
{
	unsigned char m_bfmePadding[0x114];
	BfmeResultNode *m_bfmeHead;

public:
	// ?GetAllObjects@PartitionManagerImpl@@QAE?AUBfmeResultA@@H@Z @0x00628980 209B:
	// renamed from placeholder BfmeResultSourceA::bfmeMakeResultA — the
	// WorldBuilder twin names PartitionManagerImpl::GetAllObjects at EA's own
	// partitionmanager_impl.cpp (callgraph 2; the class is corroborated by the
	// landed DoSmallFill/DoRectFill/_ClearNumObjBelow siblings).
	BfmeResultA GetAllObjects(int value);
};

BfmeResultA PartitionManagerImpl::GetAllObjects(int value)
{
	BfmeResultA result;
	BfmeResultNode *node = m_bfmeHead;

	while (node != 0)
	{
		void *thing = node->m_bfmeItem->bfmeGetResultThing();

		if (thing != 0 && (value == 0 || ((Rva000421C8 *)value)->allows((Object *)thing) != 0))
			((Rva009F39F0Result *)&result)->append((int)thing, 0);

		node = node->m_bfmeNext;
	}

	return result;
}
