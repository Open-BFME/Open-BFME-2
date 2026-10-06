// cl: /MD /EHsc
// ??1Rva004E1A04@@QAE@XZ, RVA 0x004E1A04, 47B. Unlock lane: non-virtual dtor
// releasing two narrow StringBase members twice through rowed narrow
// releaseBuffer at 0x00036410, first call under EH state 0 then state -1.
// Callers at 0x004E1A87/0x0052BBBE/0x0052CEE6 plus jmps. Owner unproven so
// honest address-derived name.
template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva004E1A04
{
public:
	~Rva004E1A04();
private:
	StringBase<char> m_a;
};

Rva004E1A04::~Rva004E1A04()
{
	m_a.~StringBase<char>();
}
