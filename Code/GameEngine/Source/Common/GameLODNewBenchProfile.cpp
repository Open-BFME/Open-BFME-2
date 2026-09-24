// cl: /O1 /DNDEBUG /MD /EHsc /G7
//
// ?newBenchProfile@RetailBenchProfileAllocator@@QAEPAUBenchProfile@@XZ,
// retail 0x0020200D, 30 bytes. Dedicated shard.
//
// BFME1 GameLOD.cpp donor (ZH GameLOD.cpp:244) with BFME2 layout and one
// divergence proven by the bytes:
// - Bounds/increments count at +0x17C0, returns a 20-byte profile from the
//   array at +0x1614 (pad1 0x6C covers array-end to count).
// - ZH returns &profiles[m_num-1]; retail indexes the incremented count
//   directly (&profiles[m_num]), so the second LEA carries +0x1614 rather
//   than +0x1600. The imul (6B C0 14) plus LEA shape is what /G7 emits;
//   /O1 without /G7 uses two LEAs instead (probe-proven).
// - No DEBUG_CRASH tail: retail returns NULL on exhaustion, like the BFME1
//   RetailGameLODManager shim used by parseBenchProfile.
// Caller: INI::parseBenchProfile at 0x002026D4 (rowed in GameLOD.cpp).

struct BenchProfile
{
	int m_cpuType;
	int m_mhz;
	float m_intBenchIndex;
	float m_floatBenchIndex;
	float m_memBenchIndex;
};

class RetailBenchProfileAllocator
{
public:
	char m_padBeforeProfiles[0x1614];
	BenchProfile m_benchProfiles[16];
	char m_padAfterProfiles[0x6C];
	int m_numBenchProfiles;
	BenchProfile* newBenchProfile();
};

BenchProfile* RetailBenchProfileAllocator::newBenchProfile()
{
	if (m_numBenchProfiles < 16)
	{
		m_numBenchProfiles++;
		return &m_benchProfiles[m_numBenchProfiles];
	}
	return 0;
}
