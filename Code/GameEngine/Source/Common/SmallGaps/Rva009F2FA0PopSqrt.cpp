// ?popSqrt@Rva009F2FA0Reader@@QAEHPAM@Z
#include <math.h>
#pragma intrinsic(sqrt)
struct Rva009F2FA0Elem { int m_key; float m_value; };
struct Rva009F2FA0Queue { int m_0; Rva009F2FA0Elem* m_end; int m_8; Rva009F2FA0Elem* m_read; };
struct Rva009F2FA0Reader {
	Rva009F2FA0Queue* m_queue;
	int popSqrt(float* out);
};
int Rva009F2FA0Reader::popSqrt(float* out)
{
	Rva009F2FA0Elem* readElement = m_queue->m_read;
	if (readElement == m_queue->m_end)
		return 0;
	// sqrt(double) directly: the float overload emits sqrt/sqrtf COMDATs that lose the link.
	*out = (float)sqrt((double)readElement->m_value);
	readElement = m_queue->m_read;
	int key = readElement->m_key;
	m_queue->m_read = readElement + 1;
	return key;
}
