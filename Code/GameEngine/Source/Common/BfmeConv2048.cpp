#include "../../Include/Common/BfmeVecFN.h"

#include "../../Include/Common/BfmeBufFN.h"

class BfmeOwnerFN
{
public:
	int bfmeFindFN(BfmeVecFN *v, const char *name);

	unsigned char m_bfmeHeadFN[0x2a8];
	BfmeVecFN m_bfmeVecFN;
};

class BfmeHostFN
{
public:
	int appendText(const char *name, const char *text);

	void *m_bfmeVfFN;
	BfmeOwnerFN *m_owner;
	unsigned char m_bfmeGapFN[8];
	BfmeBufFN *m_buffers;
	int m_bufferCount;
};

int BfmeHostFN::appendText(const char *name, const char *text)
{
	int idx = m_owner->bfmeFindFN(&m_owner->m_bfmeVecFN, name);

	if (idx == -1)
		return -106;

	BfmeBufFN *buffer = idx >= m_bufferCount ? 0 : &m_buffers[idx];

	buffer->bfmeAppendFN(text);

	return 0;
}
