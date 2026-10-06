// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?update@TimedOperationRef@@QAEIM_N@Z, retail 0x003FE6A0 (53 bytes).
// Dedicated TU: the caller (TimedOp::update) lives in
// TimedOperations_updateTimedOps.cpp, so the body lives here (a TU holding
// a row must not define that row's callees).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/Common/TimedOperations.cpp,
// TimedOperationNode::update): the null-operation path threw a FatalError in
// BFME1; BFME2 throws a 0x0C-byte std::exception child instead (default
// constructed into the frame slot, then _CxxThrowException). The live path
// forwards to virtual slot 1. The x87 float spill (fld/fstp, no SSE) sets
// the plain /O1 flags.

class TimedOperation
{
public:
	virtual ~TimedOperation(void);
	virtual unsigned int update(float elapsedSeconds, bool firstCall);
};

// 0x0C-byte std::exception child (retail vtable install + shared throw
// info); thrown from every null-operation guard in this family. The default
// constructor resolves through its pin; the vtable and throw info patch over
// as data references. Identity beyond the shape is unproven, so the name is
// address-derived.
class Rva002035E2
{
public:
	Rva002035E2(void);

	virtual ~Rva002035E2(void);

private:
	char m_pad[0x0C - 4];
};

class TimedOperationRef
{
public:
	unsigned int update(float elapsedSeconds, bool firstCall);

private:
	TimedOperation *m_operation; // +0x00
};

// ?update@TimedOperationRef@@QAEIM_N@Z
unsigned int TimedOperationRef::update(float elapsedSeconds, bool firstCall)
{
	TimedOperation *operation = m_operation;

	if (operation == 0)
	{
		throw Rva002035E2();
	}

	return operation->update(elapsedSeconds, firstCall);
}
