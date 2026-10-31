// cl: /MD
//
// ?traceAllocatedMemory@GeneralAllocator@Allocator@EA@@QAEXP6AXPBDPAX@Z11H@Z @0x000353F0 331B.
// Heap trace over allocated blocks (PPMalloc TraceAllocatedMemory-like):
// under the counted lock at +0x4E4 (use count at +0x18, the RAII guard of the
// sibling 0x00035080 with its own EH state), runs the 0x00033930 helper when
// bit 0 of +0x04 is set, defaults the trace callback and its context from
// +0x4C0/+0x4C4, opens a report through 0x00034D10 with (2, 0, context,
// blockTypes), marks the report's +0x0D byte, walks it with 0x00032F60
// (types 0x1F) formatting each block through the rowed 0x00031430 into a
// 4000-byte stack buffer that the callback receives with its context, and
// skips internal blocks (header bit 2) unless the +0x4E0 byte is set. The
// report close is inlined: 'SNAP' magic, then free through 0x00033150 when
// the +0x0D byte is set and +0x0C clear, else clear +0x20.
//
// Target evidence: retail bytes (EH frame, lock pattern, call arguments,
// offsets, the 0x534E4150 magic) and the callers' existing pins. The
// trace/report roles follow PPMalloc's GeneralAllocator naming carried by
// the sibling rows; the original member name is unknown (address-derived).
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs) throw();

class Rva000353F0Lock
{
public:
	void *m_obj;
	Rva000353F0Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(m_obj);
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	~Rva000353F0Lock()
	{
		if (m_obj)
		{
			--*(volatile int *)((char *)m_obj + 0x18);
			LeaveCriticalSection(m_obj);
		}
	}
};

class Rva00034C90
{
public:
	void consolidate();
};

namespace EA
{
namespace Allocator
{

// One heap report entry (layout as memory_pool.cpp's _DumpFragmentation view).
struct BlockInfo
{
	void *m_core;
	unsigned int m_blockSize;
	void *m_data;
	unsigned int m_dataSize;
	char m_blockType;
	bool m_mapped;
};

class GeneralAllocator
{
public:
	struct Snapshot
	{
		unsigned int m_magic;
		unsigned int m_size;
		void *m_arg2;
		unsigned char m_state[4];
		unsigned int m_values[5];
	};
	typedef void (*TraceFunction)(const char *text, void *context);

	typedef bool (*ReportFunction)(const BlockInfo *info, void *context);

	void rva00033150(const void *block);	// free engine 0x00033150 (memory_pool.cpp)
	void *rva00034D10(int blockTypes, bool copy, void *storage, unsigned int storageSize);
	void traceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes);
	bool rva00035540(ReportFunction function, void *context, int blockTypes, bool copy, char *storage, unsigned int storageSize);
	int rva00031430(const void *block, char *dst, unsigned int left);
	const BlockInfo *rva00032F60(void *context, int blockTypes);

private:
	void reportEnd(Snapshot *snapshot)
	{
		if (snapshot && snapshot->m_magic == 0x534E4150)
		{
			if (snapshot->m_state[1])
			{
				if (!snapshot->m_state[0])
					rva00033150(snapshot);
			}
			else
				snapshot->m_values[4] = 0;
		}
	}

	unsigned int m_unknown0;
	unsigned int m_flags04;			// +0x04, bit 0 gates 0x00033930
	char m_pad08[0x4C0 - 0x08];
	TraceFunction m_traceFunction;		// +0x4C0
	void *m_traceContext;			// +0x4C4
	char m_pad4C8[0x4E0 - 0x4C8];
	bool m_traceInternal;			// +0x4E0
	char m_pad4E1[3];
	void *m_pLock;				// +0x4E4
};

void GeneralAllocator::traceAllocatedMemory(TraceFunction function, void *functionContext, void *context, int blockTypes)
{
	Rva000353F0Lock lock(m_pLock);
	if (m_flags04 & 1)
		((::Rva00034C90 *)this)->consolidate();
	if (!function)
		function = m_traceFunction;
	if (!functionContext)
		functionContext = m_traceContext;
	if (function)
	{
		char buffer[4000];
		Snapshot *snapshot = (Snapshot *)rva00034D10(2, false, context, blockTypes);
		if (snapshot)
			snapshot->m_state[1] = 1;
		for (const BlockInfo *info = rva00032F60(snapshot, 0x1F); info; info = rva00032F60(snapshot, 0x1F))
		{
			const unsigned int *core = (const unsigned int *)info->m_core;
			if (m_traceInternal || !(core[1] & 4))
			{
				rva00031430(core, buffer, 4000);
				function(buffer, functionContext);
			}
		}
		reportEnd(snapshot);
	}
}

// ?rva00035540@GeneralAllocator@Allocator@EA@@QAE_NP6A_NPBUBlockInfo@23@PAX@Z1H_NPADI@Z @0x00035540 154B.
// Unlocked heap report walk (ReportHeap-like, declared as such by
// memory_pool.cpp): with a callback, opens the report through 0x00034D10
// with the four trailing arguments, marks +0x0D, hands each 0x00032F60 entry
// of the requested types to the cdecl bool callback until it returns false,
// closes the report the same inlined way as 0x000353F0 and returns the last
// callback result (false without a callback or report). Caller 0x0003094F.
bool GeneralAllocator::rva00035540(ReportFunction function, void *context, int blockTypes, bool copy, char *storage, unsigned int storageSize)
{
	bool result = false;
	if (function)
	{
		Snapshot *snapshot = (Snapshot *)rva00034D10(blockTypes, copy, storage, storageSize);
		if (snapshot)
		{
			result = true;
			snapshot->m_state[1] = 1;
			for (const BlockInfo *info = rva00032F60(snapshot, blockTypes); result && info; info = rva00032F60(snapshot, blockTypes))
				result = function(info, context);
			reportEnd(snapshot);
		}
	}
	return result;
}

}
}
