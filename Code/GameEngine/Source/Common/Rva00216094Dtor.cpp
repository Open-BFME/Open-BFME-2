// cl: /EHsc /MD
// ??1Rva00216094@@UAE@XZ @0x00216094 (48B):
// Virtual dtor: destroys wide string at +4 via inlined releaseBuffer under
// EH state 0, then stores vtable 0x007E5838 through an inline base dtor
// (novtable derived suppresses its own store, so member runs first).
// Evidence: vtable 0x007E5838; rowed releaseBuffer 0x00036E70; caller
// deleting dtor 0x00406CB7 (slot 0 of 0x00838BA4); donor copy ctor TU
// Rva00406BB0CopyCtor.cpp layout (string +4).
extern const void *const g_00BE5838[];
template <typename T> class StringBase
{
public:
	StringBase(const StringBase &other);
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	void *m_data;
};
class Rva00216094Base
{
public:
	virtual ~Rva00216094Base() { *(const void **)this = g_00BE5838; }
};
class __declspec(novtable) Rva00216094 : public Rva00216094Base
{
public:
	virtual ~Rva00216094();
private:
	StringBase<unsigned short> m_04;
};
Rva00216094::~Rva00216094()
{
}
