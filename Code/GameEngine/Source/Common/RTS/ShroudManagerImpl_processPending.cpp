// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail callers name this operation processPending(bool), at 0x0073D4F0
// (144 bytes). Its queue advances in 0x20-byte records and frees 0x80-byte
// blocks; the helper call at 0x0073D52D reaches 0x0073CCC0. That callee's
// method spelling remains address-derived; native CCC0 and WB UndoShroudReveal
// consume record+18 as float rotation. The 0x20 queue layout is unchanged.

#include <deque>

#include "../../../Include/Common/ScalarTypes.h"

struct BfmeE32
{
	unsigned int timestamp;
	int field04;
	int field08;
	int field0c;
	int field10;
	int field14;
	float rotation;
	int field1c;
};

struct ShroudRegionLayout
{
	char bytes[24];
};

class ShroudManagerImpl
{
private:
	int mode;
	ShroudRegionLayout region;
	Real defaultCellSize;
	Real inverseCellSize;
	unsigned int width;
	unsigned int height;
	void *elements;
	void *nodes;
	void *pendingPartitionData;
	int unknown38;
	_STL::deque<BfmeE32, _STL::allocator<BfmeE32> > records;

	void processPending(bool drainAll);
	void UndoShroudReveal(int field04, int field08, void *field0c,
		float rotation, int field1c);
};

void ShroudManagerImpl::processPending(bool drainAll)
{
	unsigned int compareTime = drainAll
		? (unsigned int)unknown38 : 0xffffffffu;
	while (!records.empty() && records.front().timestamp < compareTime)
	{
		BfmeE32 &record = records.front();
		UndoShroudReveal(record.field04, record.field08, &record.field0c,
			record.rotation, record.field1c);
		records.pop_front();
	}
}
