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
	StringBase(const StringBase &other);	// 0x00037050 (wide copy, pinned)
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

// The wide string members: a StringBase<wchar_t> wrapper whose implicit copy
// calls the base copy.
class Rva005E8908Text : public StringBase<unsigned short>
{
};

class Rva005E8908
{
public:
	Rva005E8908(const Rva005E8908 &other);
	~Rva005E8908();

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	Rva005E8908Text m_str14; // +0x14
	Rva005E8908Text m_str18; // +0x18
};

Rva005E8908::~Rva005E8908()
{
}

// ??0Rva005E8908@@QAE@ABV0@@Z @0x005E8943 95B: the member-wise copy, five
// words then both wide strings through the StringBase copy 0x00037050 (EH
// state 0 once the first is built). Callers 0x005E89A2 and 0x005E8A31 copy
// it into the counted 0x24-byte Rva005E8AAF at +0x08.
Rva005E8908::Rva005E8908(const Rva005E8908 &other)
	: m_00(other.m_00),
	  m_04(other.m_04),
	  m_08(other.m_08),
	  m_0C(other.m_0C),
	  m_10(other.m_10),
	  m_str14(other.m_str14),
	  m_str18(other.m_str18)
{
}
