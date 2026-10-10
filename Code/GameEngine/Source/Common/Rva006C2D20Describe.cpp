// cl: /O2 /G6 /arch:SSE /MD /EHsc
// ?rva006C2D20@Rva006C2D20Sink@@QAEHPBD0I@Z retail 0x006C2D20..0x006C2FA5
// (645 bytes) thiscall ret 0xC returning 0 (xor eax eax; WB twin 0x0070D990
// also returns a constant 0), so the existing void pin spelling QAEXPBD0I@Z
// cannot produce this body. EA GeneralAllocatorDebug chunk describer: under
// the +0x4E4 lock guard (AddRef 0x00030DD0 / Release 0x00030DF0; the unwind
// funclet jumps to the guard destructor 0x000317C0) let the base describer
// 0x00031430 write the chunk line and strip its trailing line-end byte
// (+0x475), then append the debug records fetched through 0x006C25F0 for the
// data at block+8: kind 3 flags (" high" " end-fit"), kind 5 name, kind 6
// file/line and kind 7 call stack (0x006C50D0), each closed by the separator
// byte at +0x474, and end with the line-end byte. Literals are retail's.
// One length slot serves the flags and both size queries (retail shares the
// stack slot); the flags and stack length are read once into register locals.
// Caller 0x006C2FB0 (Rva006C2FB0Finish.cpp) ignores the result.
#include <string.h>
#include <stdio.h>
#pragma intrinsic(strcpy, strlen)

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva00030DD0Guard
{
public:
	Rva00030DD0Guard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00030DD0Guard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}

private:
	Rva00030DD0Lock *m_lock;
};

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	int rva00031430(const void *block, unsigned int buffer, char *size); // 0x00031430
};
}}

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void *rva006C25F0Run6(void *data, int id, int buffer, int size, unsigned int *outLen, int flags); // 0x006C25F0
};

unsigned int Rva006C50D0Describe(const unsigned long *stack, unsigned int count, char *buffer, unsigned int room);

struct Rva006C2D20Location
{
	const char *file;
	int line;
};

class Rva006C2D20Sink : public EA::Allocator::GeneralAllocator
{
public:
	int rva006C2D20(const char *block, const char *buffer, unsigned int bufferLength);

private:
	unsigned char m_pad0[0x474];
	unsigned char m_separator; // +0x474
	unsigned char m_lineEnd;   // +0x475
	unsigned char m_pad476[0x4E4 - 0x476];
	Rva00030DD0Lock *m_lock;   // +0x4E4
};

int Rva006C2D20Sink::rva006C2D20(const char *block, const char *buffer, unsigned int bufferLength)
{
	Rva00030DD0Guard guard(m_lock);
	void *data = (void *)(block + 8);
	char *end = (char *)buffer + bufferLength;
	unsigned int n0 = rva00031430(block, (unsigned int)buffer, (char *)bufferLength);
	char *p = (char *)buffer + n0;
	if (p > buffer && p[-1] == m_lineEnd)
		*--p = 0;

	unsigned int len;
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 3, (int)&len, 4, 0, 2)) {
		unsigned int flags = len;
		if (flags && end - p >= 0x18) {
			strcpy(p, "flags:");
			p += 6;
			if (flags & 1) {
				strcpy(p, " high");
				p += 5;
			}
			if (flags & 2) {
				strcpy(p, " end-fit");
				p += 8;
			}
			*p++ = m_separator;
			*p = 0;
		}
	}

	len = 0x200;
	char name[0x200];
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 5, (int)name, len, &len, 2) && len
		&& (unsigned int)(end - p) >= len + 12) {
		unsigned int n = _snprintf(p, end - p, "name: %s%c", name, m_separator);
		p += n;
	}

	Rva006C2D20Location loc;
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 6, (int)&loc, 8, 0, 2)) {
		if ((unsigned int)(end - p) >= strlen(loc.file) + 0x16) {
			unsigned int n = _snprintf(p, end - p, "loc: %s, %d%c", loc.file, loc.line, m_separator);
			p += n;
		}
	}

	unsigned long stack[0x18];
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 7, (int)stack, 0x60, &len, 2)) {
		unsigned int stackLen = len;
		if (stackLen && end - p > 0x20) {
			strcpy(p, "stack: ");
			p += 7;
			p += Rva006C50D0Describe(stack, stackLen >> 2, p, end - p - 4);
			*p++ = m_separator;
			*p = 0;
		}
	}

	*p++ = m_lineEnd;
	*p = 0;
	return 0;
}
