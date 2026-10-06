// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??4BfmeAssignRecord36@@QAEAAU0@ABU0@@Z, retail 0x00151336, 119 bytes.
// operator= for 36-byte assign record: first AsciiString at +0 via
// StringBase<char>::set(str()) (row 0x000055F5), int at +4, second string
// at +8 via path-surgery helper ?rva00151288@Rva00151288@@QAEXPBD@Z
// (row 0x00151288, this=record base so its +8 member is ours), then tail
// 16+4+1 bytes at +0x0C/+0x1C/+0x20 via memcpy thunk 0x006291A8.
// Evidence: chain packet (callee 0x00151288 just landed), callers in
// stlport_asciistring_record_bodies.cpp (fill/dup/copy_backward), empty
// default 0x007BAC1C shared for both str() nulls, ret 4. Layout: two
// StringBases + int + 16B + int + byte = 33, padded to 36.

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);

template <typename T>
class StringBase
{
public:
	void set(const T *str);
	const T *str() const { return m_data ? &m_data->data[0] : (const T *)""; }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class Rva00151288
{
public:
	void rva00151288(const char *path);

private:
	char m_pad00[8];
	StringBase<char> m_str08;
};

struct BfmeAssignRecord36
{
public:
	BfmeAssignRecord36 &operator=(const BfmeAssignRecord36 &rhs);

private:
	StringBase<char> m_s00;
	int m_04;
	StringBase<char> m_s08;
	char m_0c[16];
	int m_1c;
	unsigned char m_20;
	char m_pad21[3];
};

BfmeAssignRecord36 &BfmeAssignRecord36::operator=(const BfmeAssignRecord36 &rhs)
{
	m_s00.set(rhs.m_s00.str());
	m_04 = rhs.m_04;
	((Rva00151288 *)this)->rva00151288(rhs.m_s08.str());
	memcpy(m_0c, rhs.m_0c, 16);
	memcpy(&m_1c, &rhs.m_1c, 4);
	memcpy(&m_20, &rhs.m_20, 1);
	return *this;
}
