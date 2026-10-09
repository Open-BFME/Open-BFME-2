// The range-query result cursor; array ctor302C81 now lives in MapMetaDataDefault.cpp.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv881.cpp); trimmed to the two T1
// bodies the sweep places.

struct BfmeQueueEOF
{
	unsigned char m_bfmeHead[4];
	void **m_bfmeEnd;
	unsigned char m_bfmePad[4];
	void **volatile m_bfmeCur;
};

class Object;

// The partition manager's range-query handle (iterateObjectsInRange
// 0x00625610 returns it): next() yields the payload's next hit, stepping
// the +0x0C cursor over 8-byte entries up to +0x04, or 0 when done. 43
// matched callers reference it by this name (pin 0x00045623).
struct BfmeWideResult
{
	Object *next();
	BfmeQueueEOF *m_bfmeQ;
};

Object *BfmeWideResult::next()
{
	BfmeQueueEOF *q = m_bfmeQ;
	if (q->m_bfmeCur == q->m_bfmeEnd)
		return 0;
	void **cur = q->m_bfmeCur;
	Object *v = (Object *)*cur;
	q->m_bfmeCur = cur + 2;
	return v;
}

