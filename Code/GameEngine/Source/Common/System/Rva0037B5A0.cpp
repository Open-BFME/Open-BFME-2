// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037B5A0@Rva0037B5A0@@QAE?AVUnicodeString@@XZ retail 0x0037B5A0 40B.
// Conditional string getter: if int at +0x1c is 1 copy UnicodeString at +0x20 else copy UnicodeString::TheEmptyString via rowed wide copy ctor 0x37050 into return buffer.
// Evidence: callee rowed 0x37050 plus TheEmptyString 0x00A0C898 in use; caller 0x0051B9C0; neighbours Rva0037B3D1 and Rva0037B5DFDtor same flags.
#include "unicode_string.h"

class Rva0037B5A0
{
public:
	UnicodeString rva0037B5A0();
private:
	char m_pad00[0x1C]; // +0x00..+0x1B
	int m_flag1C; // +0x1C
	UnicodeString m_str20; // +0x20
};

UnicodeString Rva0037B5A0::rva0037B5A0()
{
	if (m_flag1C == 1)
		return m_str20;
	return UnicodeString::TheEmptyString;
}
