// cl: /O1 /DNDEBUG /MD /EHsc
// ??1FadeInTextRender@@UAE@XZ @0x0059675A 89B
// Dtor with EH frame: vptr store, delete of interface ptr at +0x1c via virtual
// slot0 plus operator delete, StringBase<char> at +0x24 via releaseBuffer,
// then base vtable store. Empty body plus delete.
// Evidence: mov [esi] 0x00870A70, virtual call [eax] with push 0, call delete
// at 0x2FD60, lea ecx [esi+24] call 0x36410, mov [esi] 0x00870A5C.
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

struct Rva0059675ABase
{
	virtual ~Rva0059675ABase();
};
struct Rva0059675AInner
{
	virtual void *slot0(int flag);
};
struct FadeInTextRender : Rva0059675ABase
{
	char m_pad04[0x18];
	Rva0059675AInner *m_1c;
	char m_pad20[0x4];
	StringBase<char> m_24;
	virtual ~FadeInTextRender();
	virtual void LoadAssets();
};
// ??1Rva0059675ABase@@UAE@XZ present-unmatched
Rva0059675ABase::~Rva0059675ABase()
{
}
FadeInTextRender::~FadeInTextRender()
{
	void *tmp = m_1c ? m_1c->slot0(0) : 0;
	::operator delete(tmp);
	m_1c = 0;
}
