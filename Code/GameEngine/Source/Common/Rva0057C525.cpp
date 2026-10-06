// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva0057C525@Rva0057C525@@QAE_NABVRva004FD6F9@@@Z @0x0057C525 36B
// Evidence: this+0x68/+0x29c/+0x1c chase to Rva004FD6F9 then tail-jmp to
// rowed rva004FD8A8 0x004FD8A8; callers at 0x0057CBC5 0x0057CD19 0x0057D7B2.
#include "ascii_string.h"

class Rva004FD6F9
{
public:
	bool rva004FD8A8(const Rva004FD6F9 &o);
};

struct Rva0057C525Mid2
{
	unsigned char m_pad[0x1c];
	Rva004FD6F9 *m_ptr1c;
};

struct Rva0057C525Mid1
{
	unsigned char m_pad[0x29c];
	Rva0057C525Mid2 *m_ptr29c;
};

struct Rva0057C525Outer
{
	unsigned char m_pad[0x68];
	Rva0057C525Mid1 *m_ptr68;
};

class Rva0057C525
{
	unsigned char m_pad[0x68];
	Rva0057C525Mid1 *m_ptr68;
public:
	bool rva0057C525(const Rva004FD6F9 &o);
};

bool Rva0057C525::rva0057C525(const Rva004FD6F9 &o)
{
	Rva0057C525Mid1 *mid1 = m_ptr68;
	if (!mid1)
		return false;
	Rva0057C525Mid2 *mid2 = mid1->m_ptr29c;
	if (!mid2)
		return false;
	Rva004FD6F9 *target = mid2->m_ptr1c;
	if (!target)
		return false;
	return target->rva004FD8A8(o);
}
