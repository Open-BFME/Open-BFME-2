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

// The counted critical-section guard; Rva00034C90Finish.cpp supplies retail's
// out-of-line destructor (0x000317C0) under this name.
class Rva00034C90Lock
{
public:
	Rva00034C90Lock(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00034C90Lock()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}

private:
	Rva00030DD0Lock *m_lock;
};

#include "../../Include/Common/GeneralAllocator.h"

class GeneralAllocatorDebug : public EA::Allocator::GeneralAllocator
{
public:
	void *rva006C25F0Run6(void *data, int id, int buffer, int size, unsigned int *outLen, int flags); // 0x006C25F0
};

unsigned int Rva006C50D0Describe(const unsigned long *stack, unsigned int count, char *buffer, unsigned int room);

struct SourceLocation
{
	const char *file;
	int line;
};

class Rva006C2D20Sink : public EA::Allocator::GeneralAllocator
{
public:
	int rva006C2D20(const char *block, const char *buffer, unsigned int bufferLength);
};

int Rva006C2D20Sink::rva006C2D20(const char *block, const char *buffer, unsigned int bufferLength)
{
	Rva00034C90Lock guard(m_pLock);
	void *data = (void *)(block + 8);
	char *end = (char *)buffer + bufferLength;
	unsigned int baseLength = rva00031430(block, (char *)buffer, bufferLength);
	char *writePosition = (char *)buffer + baseLength;
	if (writePosition > buffer && writePosition[-1] == m_475)
		*--writePosition = 0;

	unsigned int len;
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 3, (int)&len, 4, 0, 2)) {
		unsigned int flags = len;
		if (flags && end - writePosition >= 0x18) {
			strcpy(writePosition, "flags:");
			writePosition += 6;
			if (flags & 1) {
				strcpy(writePosition, " high");
				writePosition += 5;
			}
			if (flags & 2) {
				strcpy(writePosition, " end-fit");
				writePosition += 8;
			}
			*writePosition++ = m_474;
			*writePosition = 0;
		}
	}

	len = 0x200;
	char name[0x200];
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 5, (int)name, len, &len, 2) && len
		&& (unsigned int)(end - writePosition) >= len + 12) {
		unsigned int charsWritten = _snprintf(writePosition, end - writePosition, "name: %s%c", name, m_474);
		writePosition += charsWritten;
	}

	SourceLocation loc;
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 6, (int)&loc, 8, 0, 2)) {
		if ((unsigned int)(end - writePosition) >= strlen(loc.file) + 0x16) {
			unsigned int charsWritten = _snprintf(writePosition, end - writePosition, "loc: %s, %d%c", loc.file, loc.line, m_474);
			writePosition += charsWritten;
		}
	}

	unsigned long stack[0x18];
	if (((GeneralAllocatorDebug *)this)->rva006C25F0Run6(data, 7, (int)stack, 0x60, &len, 2)) {
		unsigned int stackLen = len;
		if (stackLen && end - writePosition > 0x20) {
			strcpy(writePosition, "stack: ");
			writePosition += 7;
			writePosition += Rva006C50D0Describe(stack, stackLen >> 2, writePosition, end - writePosition - 4);
			*writePosition++ = m_474;
			*writePosition = 0;
		}
	}

	*writePosition++ = m_475;
	*writePosition = 0;
	return 0;
}
