// Target facts: destructor RVA 0x00042F8C is E9 BF DF 0D 00, a tail jump to BFME_DX8_Thread_Assert (RVA 0x00120F50), without accessing this or storing a vptr.
// Guard construction at RVA 0x0025C4C4 and 0x0007E13D calls BFME_DX8_Thread_Lock (RVA 0x0011F520) directly, without object initialization; cleanup at RVA 0x00772B08 and 0x0075F40E calls the nonvirtual destructor, while normal exits inline its unlock call, so the destructor is defined inline. No virtual functions or base subobjects are evidenced.
// Lock state is global: VA 0x00DEC598 is the mutex, 0x00DEDA88 is the owner, and 0x00DEDA8C is the recursion count (RVA 0x0011F520 and 0x00120F50). The empty C++ guard has sizeof 1; retail provides no allocation or array stride proving a larger extent.

#pragma once

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};
