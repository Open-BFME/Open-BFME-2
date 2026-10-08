// cl: /O2 /G7 /DNDEBUG /MD
//
// PartitionFilter::And, retail 0x00625790 (46B).
//
// Target evidence: the body appends its argument at the end of this filter's
// +0x04 chain and returns this (callers chain several appends through
// mov ecx,eax); the BFME2 filter base (ctor 0x000421C8, vftable 0x00BC26E0,
// chain test 0x00625720) carries the link at +0x04 after the vptr.
// Name and file are carried from the BFME2 WorldBuilder build, whose debug
// body for this function asserts "cur != &rhs" and "!rhs.m_prev ||
// !rhs.m_next" under PartitionFilter::And in
// Code\Libraries\Source\partitionmanager\partitionmanager_filter.cpp; the
// release build drops those checks, leaving the tail walk below.

class Object;

class PartitionFilter
{
public:
	virtual ~PartitionFilter();
	virtual bool allow(Object *obj) = 0;

	PartitionFilter &And(PartitionFilter &rhs);

private:
	PartitionFilter *m_next;	// +0x04
};

PartitionFilter &PartitionFilter::And(PartitionFilter &rhs)
{
	PartitionFilter *cur;
	for (cur = this; cur->m_next; cur = cur->m_next)
		;
	cur->m_next = &rhs;
	return *this;
}
