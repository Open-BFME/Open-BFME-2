// cl: /MD
//
// ?rva000BBD66@Rva000BBD66@@QAEHPAD@Z retail 0x000BBD66 25B
// Forwarding write over the rowed Rva000B980E base at +0: copies the held
// AsciiString slice at +4/+8 to dst via 0x000B980E then returns size at +8.
// Evidence: chain from 0x000B980E plus 2 callers 0x000BC834 0x000BD268 plus
// contiguous prev row 0x000BBD41 in same page.
class AsciiString;

class Rva000B980E
{
public:
	void rva000B980E(char *dst, int off, int size);
private:
	AsciiString *m_str;
};

class Rva000BBD66 : public Rva000B980E
{
public:
	int rva000BBD66(char *dst);
private:
	int m_off;
	int m_len;
};

int Rva000BBD66::rva000BBD66(char *dst)
{
	rva000B980E(dst, m_off, m_len);
	return m_len;
}
