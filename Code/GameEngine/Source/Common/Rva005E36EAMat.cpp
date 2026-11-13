// cl: /EHsc
//
// ??BRva005E36C5@@QAE?AV?$StringBase@D@@XZ retail 0x005E36EA 105B.
// The native caller 0x005E3753 requires an implicit conversion to the base
// string before its AsciiString copy; a named-method call loses the LEA and
// changes temporary homes. The existing whole105B provider and EH stay exact.
// Five-part materializer: length via rowed 0x00513E03 plus tail len at +0x1C
// then getBufferForRead then rowed write 0x005E36C5 then copy ctor 0x000365F0
// then releaseBuffer, EH frame, ret 4.
// Evidence: retail EH_prolog getBufferForRead write calls; caller 0x005E3753;
// chain from 0x005E36C5 in Code/GameEngine/Source/Common/Rva005E36A0Write.cpp.
template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class Rva005E36C5;
	StringBase(const T *text);
	StringBase(const StringBase &src);
public:
	StringBase() : m_data(0) {}
	~StringBase();
	T *getBufferForRead(int len);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
protected:
	Header *m_data;
};
class UnicodeString;
class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &src) : StringBase<char>(src) {}
	AsciiString &operator=(const AsciiString &src);
	int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? m_data->data : ""; }
	void translate(const UnicodeString &src);
};
#include "../../Include/Common/Rva000B3F84Pair.h"
#include "../../Include/Common/AsciiStringRef.h"
#include "../../Include/Common/Rva0059B3E9.h"
class Rva005E36A0
{
public:
	int rva005E36A0(char *dst);
private:
	Rva0059B3E9 m_head;
	AsciiStringRef m_tail;
};
class Rva005E36C5
{
public:
	int copyToBuffer(char *dst);
	operator StringBase<char>();
private:
	Rva005E36A0 m_head;
	Rva000B3F84Pair m_tail;
};
#include "../../Include/Common/Rva00513E03.h"

Rva005E36C5::operator StringBase<char>()
{
	StringBase<char> tmp;
	int extra = m_tail.m_len;
	copyToBuffer(tmp.getBufferForRead(((const Rva00513E03 *)this)->length() + extra));
	return tmp;
}
