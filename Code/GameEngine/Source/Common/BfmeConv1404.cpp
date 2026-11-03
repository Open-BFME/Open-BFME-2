// Open-BFME5 conversions.

struct BfmeHdrVKK
{
	unsigned short m_bfme00;
	unsigned short m_length;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
};

class BfmeStrVKK;
class EAStringC
{
public:
	enum CBPushZero { CB_NO_PUSH_ZERO, CB_PUSH_ZERO };

private:
	friend class BfmeStrVKK;
	void ChangeBuffer(unsigned int reserve, unsigned int offset, unsigned int copy,
		CBPushZero pushZero, unsigned int size);
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned requestedLength);
	BfmeStrVKK *bfmeReverseVKK();
	BfmeHdrVKK *m_bfme00;
};

void BfmeStrVKK::bfmeTruncVKK(unsigned requestedLength)
{
	unsigned retainedLength = m_bfme00->m_length;
	if (retainedLength > requestedLength)
		retainedLength = requestedLength;
	((EAStringC *)this)->ChangeBuffer(requestedLength, 0, retainedLength, EAStringC::CB_PUSH_ZERO, retainedLength);
}

BfmeStrVKK *BfmeStrVKK::bfmeReverseVKK()
{
	unsigned originalLength = m_bfme00->m_length;
	((EAStringC *)this)->ChangeBuffer(originalLength, 0, originalLength, EAStringC::CB_PUSH_ZERO, originalLength);
	unsigned length = m_bfme00->m_length;
	if (length > 1)
	{
		char *first = (char *)m_bfme00 + 8;
		char *last = first + length - 1;
		if (first < last)
		{
			do
			{
				char lastChar = *last;
				char firstChar = *first;
				*first = lastChar;
				++first;
				*last = firstChar;
				--last;
			} while (first < last);
		}
		m_bfme00->m_bfme06 = 0;
	}
	return this;
}
