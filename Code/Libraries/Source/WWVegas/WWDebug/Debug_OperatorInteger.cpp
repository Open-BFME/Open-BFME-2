// cl: /DNDEBUG /MD /EHsc
//
// Debug::operator<<(int) at retail 0x0003B3D0 and Debug::operator<<(unsigned)
// at 0x0003B420 (79 bytes each, ret 4). Ported from Open-BFME-1
// debug_debug.cpp, itself the Zero Hour body.
//
// Identity: the int body calls _itoa and fills Debug vtable (RVA 0x7BE810)
// slots 0x2C and 0x34 (0x34 is the slot AssertDone/CrashDone use to print
// the hit count); the unsigned body calls _ultoa and fills 0x28 and 0x30.
// The long / unsigned long overloads compile to the same bytes, so each
// address carries two names; the ledger uses the int / unsigned ones.
// m_prefix sits at +0x9E7C and m_radix at +0x9E8C; AddOutput is called
// directly and the digits go out through the virtual operator<<(const
// char *) at slot 0x38.

#pragma optimize("y", off)

extern "C" unsigned int strlen(const char *text);
extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *buffer, int radix);
extern "C" __declspec(dllimport) char *__cdecl _ultoa(unsigned long value, char *buffer, int radix);

class Debug
{
public:
	// MSVC groups the overloads at the first one's slot in reverse
	// declaration order: unsigned 0x30, int 0x34, const char * 0x38.
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual Debug &operator<<(unsigned val);

private:
	virtual void AddOutput(const char *str, unsigned int len);

	unsigned char m_pad04[0x9E78];
	char m_prefix[16];                   // +0x9E7C
	int m_radix;                         // +0x9E8C
};

// ??6Debug@@UAEAAV0@H@Z
Debug &Debug::operator<<(int val)
{
	// usually having a fixed size buffer and a function
	// that doesn't check for buffer overflow isn't a good idea
	// but in this case we know how long it can be at max...
	char help[1 + 32 + 1]; // sign, 32 digits (binary), NUL
	Debug::AddOutput(m_prefix, strlen(m_prefix));
	return (*this) << _itoa(val, help, m_radix);
}

// ??6Debug@@UAEAAV0@I@Z
Debug &Debug::operator<<(unsigned val)
{
	char help[32 + 1]; // 32 digits, NUL
	Debug::AddOutput(m_prefix, strlen(m_prefix));
	return (*this) << _ultoa(val, help, m_radix);
}
