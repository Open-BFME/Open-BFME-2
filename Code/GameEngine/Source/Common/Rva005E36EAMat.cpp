// cl: /EHsc
//
// ?rva005E36EA@Rva005E36C5@@QAE?AV?$StringBase@D@@XZ retail 0x005E36EA 105B.
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
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);
	int write(char *dst);
	const char *m_ptr;
	int m_len;
};
struct AsciiStringRef
{
	int write(char *dst);
	const AsciiString *m_string;
};
class Rva0059B3E9
{
public:
	int rva0059B3E9(char *dst);
private:
	Rva000B3F84Pair m_first;
	AsciiStringRef m_mid;
	Rva000B3F84Pair m_last;
};
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
	int rva005E36C5(char *dst);
	StringBase<char> rva005E36EA();
private:
	Rva005E36A0 m_head;
	Rva000B3F84Pair m_tail;
};
struct Rva00513E03
{
	int length() const;
	Rva000B3F84Pair m_first;
	const AsciiString *m_second;
	Rva000B3F84Pair m_third;
	const AsciiString *m_fourth;
};

StringBase<char> Rva005E36C5::rva005E36EA()
{
	StringBase<char> tmp;
	int extra = m_tail.m_len;
	rva005E36C5(tmp.getBufferForRead(((const Rva00513E03 *)this)->length() + extra));
	return tmp;
}
