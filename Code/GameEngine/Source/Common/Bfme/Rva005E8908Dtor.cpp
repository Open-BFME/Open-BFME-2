// cl: /EHsc /MD
// ??1Rva005E8908@@QAE@XZ @0x005E8908 54B
// Non-virtual dtor releasing two wide strings at +0x14/+0x18 via rowed
// releaseBuffer 0x00036E70 with EH states 0 then -1 and homed this for
// the 0x007A3F20 funclet. No vptr store and no base call. Unlocks
// 0x005E8AAF 0x005F8CB0 0x005E8B66. Precedent RankInfoDtor unto inlined
// StringBase dtor emitting the releaseBuffer call.
template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class Rva005E8908
{
public:
	~Rva005E8908();

private:
	char m_pad00[0x14];
	StringBase<unsigned short> m_str14; // +0x14
	StringBase<unsigned short> m_str18; // +0x18
};

Rva005E8908::~Rva005E8908()
{
}
