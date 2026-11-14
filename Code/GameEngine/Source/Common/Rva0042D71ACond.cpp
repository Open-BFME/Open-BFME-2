#include "../../Include/Common/Rva0042D71A.h"
int Rva0042D71A::get() const
{
	int x = *(int *)((char *)m_ptr + 0x30);
	int y = x + 4;
	return x ? y : 0;
}
