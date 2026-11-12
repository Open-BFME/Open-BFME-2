// cl: /Ob0

#include "../../Include/Common/BfmeResultA.h"

class PartitionManagerImpl
{
public:
	BfmeResultA GetAllObjects(int value);
};

class BfmeResultForwardA
{
	char m_pad[0x10];
	PartitionManagerImpl *m_source;

public:
	BfmeResultA bfmeForwardResultA();
};

// The filtered sibling of the forwarder above (BFME 1 0x009F2A40): the same
// +0x10 result maker, passed the caller's filter chain.
class BfmeResultForwardB
{
	char m_pad[0x10];
	PartitionManagerImpl *m_source;

public:
	BfmeResultA bfmeForwardResultB(int value);
};

BfmeResultA BfmeResultForwardA::bfmeForwardResultA()
{
	return m_source->GetAllObjects(0);
}

BfmeResultA BfmeResultForwardB::bfmeForwardResultB(int value)
{
	return m_source->GetAllObjects(value);
}
