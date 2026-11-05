// cl: /MD /Oy-
// Debug::operator<<(short) at retail 0x0003B470 (80 bytes), the Zero Hour body
// (GeneralsMD/Code/Libraries/Source/debug/debug_debug.cpp, operator<<(short val)): the prefix is
// written out with its length measured in place, then the value is turned into
// text in the record's radix and sent through the virtual operator<<(const char *).
// The Debug vtable at 0x007BE810 holds the fifteen overloads in reverse
// declaration order: unsigned short is slot 5, short slot 6, const char * slot 14.

#include <string.h>
#include <stdlib.h>
#pragma intrinsic(strlen)


class Debug
{
public:
	class MemDump;
	class HResult;

	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual Debug &operator<<(unsigned val);
	virtual Debug &operator<<(long val);
	virtual Debug &operator<<(unsigned long val);
	virtual Debug &operator<<(bool val);
	virtual Debug &operator<<(float val);
	virtual Debug &operator<<(double val);
	virtual Debug &operator<<(short val);
	virtual Debug &operator<<(unsigned short val);
	virtual Debug &operator<<(__int64 val);
	virtual Debug &operator<<(unsigned __int64 val);
	virtual Debug &operator<<(const void *ptr);
	virtual Debug &operator<<(const MemDump &dump);
	virtual Debug &operator<<(HResult hres);

private:
	virtual void AddOutput(const char *str, unsigned int len);

	unsigned char m_pad04[0x9E78];
	char m_prefix[16];			// +0x9E7C
	int m_radix;				// +0x9E8C
};

Debug &Debug::operator<<(short val)
{
	// usually having a fixed size buffer and a function
	// that doesn't check for buffer overflow isn't a good idea
	// but in this case we know how long it can be at max...
	char help[1+16+1]; // sign, 16 digits, NUL
	Debug::AddOutput(m_prefix, strlen(m_prefix));
	return (*this) << _itoa(val, help, m_radix);
}
