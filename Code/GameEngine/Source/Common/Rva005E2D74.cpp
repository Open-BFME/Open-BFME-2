// cl: /MD /EHsc
//
// ?rva005E2D74@Rva005E2D74@@QAEHPAD@Z retail 0x005E2D74 22B
// Evidence: unlock lane; callee write 0x000B44F0; unblocks 0x005E306D; prev Rva005E2144 same /O1 MD; members +0 byte +4 pair.
template <typename T>
class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &that);
	void releaseBuffer();
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
public:
	char *getBufferForRead(int len);
};
class AsciiString
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &that) : m_data(that.m_data) {}
	~AsciiString() { m_data.releaseBuffer(); }
	char *getBufferForRead(int len) { return m_data.getBufferForRead(len); }
private:
	StringBase<char> m_data;
};
class Rva000B3F84Pair
{
public:
	int write(char *dst);
	const char *m_ptr;
	int m_len;
};
class Rva005E2D74
{
public:
	int rva005E2D74(char *dst);
	AsciiString rva005E306D();
private:
	char m_byte00;
	char m_pad01[3];
	Rva000B3F84Pair m_pair04;
};
int Rva005E2D74::rva005E2D74(char *dst)
{
	dst[0] = m_byte00;
	return m_pair04.write(dst + 1) + 1;
}
AsciiString Rva005E2D74::rva005E306D()
{
	AsciiString tmp;
	char *buf = tmp.getBufferForRead(m_pair04.m_len + 1);
	rva005E2D74(buf);
	return tmp;
}
