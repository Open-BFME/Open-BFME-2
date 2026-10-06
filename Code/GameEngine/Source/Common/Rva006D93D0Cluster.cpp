// cl: /MD
// Apt array clear at retail 0x006D93D0 (195 bytes), reconstructed from the
// retail ABI. Layout follows Rva006D94A0Cluster.cpp (m_data +0x20, mnCapacity
// +0x24, mnLength +0x28); the two assert triples name AptArray.cpp lines
// 0x82/0x83 and their file string. The body first calls the unrowed base/flag
// helper 0x0070DFE0 (address-derived pin), then nulls each element through the
// vtable slot 1 release, hands the backing store to the pool 0x00E176E8
// (freeBlock 0x006DB270 with mnCapacity*4 bytes) and clears all three fields.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class Rva006DB270
{
public:
	void freeBlock(void *pNowFree, int nSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // VA 0x00E176E8

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	virtual void release();

	void rva0070DFE0();
	void rva006D93D0();

	unsigned int m_flags;
	char m_pad[0x18];
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;
};

void BfmeAptValue006DCD20::rva006D93D0()
{
	rva0070DFE0();

	if (!(m_data != 0 || mnLength == 0)) {
		g_bfmeAptAssertAtE17734("mpValues != NULL || mnLength == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x82);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}

	if (!(mnLength <= mnCapacity)) {
		g_bfmeAptAssertAtE17734("mnLength <= mnCapacity", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x83);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__asm int 3
	}

	for (int i = 0; i < mnLength; ++i) {
		BfmeAptValue006DCD20 *pValue = m_data[i];
		if (pValue != 0) {
			pValue->release();
			m_data[i] = 0;
		}
	}

	if (m_data != 0)
		g_pChainBlockAllocator->freeBlock(m_data, mnCapacity * 4);

	m_data = 0;
	mnLength = 0;
	mnCapacity = 0;
}
