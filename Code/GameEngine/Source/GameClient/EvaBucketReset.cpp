// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003F7954@Rva003F7954@@QAEXXZ @0x003F7954 40B
// Reset for the Eva bucket owner: clears table at +8 via rowed 0x003A2A41
// then zeroes +0x1C and sets +0x20/+0x24/+0x28 to 1.0f from 0x00BBB8D8.
// Evidence: callee row Rva003A2A41Clear; neighbours EvaBucketAdvance/Ensure
// same flags; caller 0x0020EB4E passes its arg as this; landing unblocks it.
#include "ascii_string.h"

class Rva000427195
{
public:
	void rva003A2A41();
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

class Rva003F7954
{
public:
	void rva003F7954();
	int m_00;
	int m_04;
	Rva000427195 m_table;
	int m_1C;
	float m_20;
	float m_24;
	float m_28;
};

void Rva003F7954::rva003F7954()
{
	m_table.rva003A2A41();
	m_1C = 0;
	m_20 = 1.0f;
	m_24 = 1.0f;
	m_28 = 1.0f;
}
