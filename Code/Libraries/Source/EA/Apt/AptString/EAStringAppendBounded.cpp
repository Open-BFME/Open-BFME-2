// ?bfmeAppendVKG@BfmeBufVKG@@QAEPAV1@PBDI@Z
// cl: /DNDEBUG /MD

#include <string.h>
#pragma intrinsic(memcpy)

struct BfmeStringDataVKG
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

class BfmeBufVKG;
#include "../../../Apt/EAStringC.h"

class BfmeStrVKJ
{
	protected:
	BfmeStringDataVKG *m_data;
};

class BfmeBufVKG : public BfmeStrVKJ
{
public:
	BfmeBufVKG *bfmeAppendVKG(const char *source, unsigned int limit);
};

BfmeBufVKG *BfmeBufVKG::bfmeAppendVKG(const char *source, unsigned int limit)
{
	unsigned int count = 0;
	const char *scan = source;
	if (limit > 0)
	{
		while (*scan++ != 0 && ++count < limit)
			;
	}
	if (count != 0)
	{
		unsigned int oldSize = m_data->m_size;
		unsigned int newSize = oldSize + count;
		((EAStringC *)this)->ChangeBuffer(newSize, 0, oldSize,
			EAStringC::CB_PUSH_ZERO, newSize);
		memcpy(reinterpret_cast<char *>(m_data) + 8 + oldSize,
			source, count);
	}
	return this;
}
