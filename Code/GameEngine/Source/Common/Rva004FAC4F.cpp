// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FAC4F@Rva004FAC21@@QAE?AV?$StringBase@D@@XZ 28B @0x004FAC4F:
// virtual slot 2 (offset 0x8) of vtable 0x008633B0 installed by rowed ctor
// 0x004FAC21. Returns the fixed "SpawnArmy" string by value through the
// hidden out-pointer; method and element names are honest-address
// placeholders. StringBase PBD ctor is rowed private (AAE) via friendship.

template <typename T> class StringBase
{
	friend class Rva004FA830;
	friend class Rva004FAC21;
	StringBase(const StringBase<T> &other);
	StringBase(const T *s);
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &s);

private:
	StringBase<char> m_s;
};

class Rva004FAC21 : public Rva004FA830
{
public:
	Rva004FAC21(const StringBase<char> &s);
	virtual StringBase<char> rva004FAC4F();
};

StringBase<char> Rva004FAC21::rva004FAC4F()
{
	return "SpawnArmy";
}
