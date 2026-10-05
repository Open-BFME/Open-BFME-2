// ?rva0039BD28@Rva0039BD28@@QAEXV?$StringBase@G@@@Z
// partial score=0.75 date=2026-10-05
// cl: /O1 /EHsc /MD /Ireference/shims/bfme2_ascii
// ?rva0039BD28@Rva0039BD28@@QAEXV?$StringBase@G@@@Z @0x0039BD28 85B: sets the
// +0x310 record text from the by-value string arg through rowed
// StringBase<ushort>::set at 0x00037150, fills +0x314/+0x318 from the pinned
// 0x0039BB0A/0x0039BC85 lookups, then releases the arg buffer through rowed
// 0x00036E70. Evidence: same +0x310 BfmeStringRecord002B4DC1 as neighbouring
// 0x0039BD7D; by-value 4B COW string (lea for address, no dtor call).
template <typename T>
class StringBase
{
	void *m_data;

public:
	~StringBase() { releaseBuffer(); }
	void set(const StringBase<T> &that);
	void releaseBuffer();
};

typedef StringBase<unsigned short> UnicodeString;

struct BfmeStringRecord002B4DC1
{
	UnicodeString text;
	unsigned int word0;
	unsigned int word1;
};

class Rva0039BD28
{
public:
	void rva0039BD28(UnicodeString s);
	int rva0039BB0A(void);
	int rva0039BC85(void);

private:
	char m_pad00[0x310];
	BfmeStringRecord002B4DC1 m_rec310;
};

void Rva0039BD28::rva0039BD28(UnicodeString s)
{
	m_rec310.text.set(s);
	m_rec310.word0 = rva0039BB0A();
	m_rec310.word1 = rva0039BC85();
	s.releaseBuffer();
}
