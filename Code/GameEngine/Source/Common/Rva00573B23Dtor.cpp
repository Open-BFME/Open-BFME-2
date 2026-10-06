// cl: /DNDEBUG /MD /EHsc
// ??1Rva00573B23@@UAE@XZ @0x00573B23 59B
// Dtor: vptr store, inline StringBase<char> member dtor at +0x2c (inlined to
// a direct releaseBuffer call, arming EH state 0), then the virtual public
// base dtor ??1Rva0055B0CC@@UAE@XZ (pin-only). Empty body: everything implicit.
// Evidence: mov [esi] vtable, and [ebp-4]0, lea ecx [esi+2c] call
// releaseBuffer@StringBase@D, or [ebp-4]-1, mov ecx esi call 0x0055B0CC.
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

struct Rva0055B0CC
{
	virtual ~Rva0055B0CC();
};
struct Rva00573B23 : Rva0055B0CC
{
	char m_pad04[0x28];
	StringBase<char> m_2c;
	virtual ~Rva00573B23();
};
Rva00573B23::~Rva00573B23()
{
}
// ??1Rva00573F03@@UAE@XZ @0x00573F03 11B
// Derived dtor: stores its own vtable, then tail-jumps to the rowed base
// dtor ??1Rva00573B23@@UAE@XZ. Empty body, no new members.
// Evidence: mov [ecx] 0x0086E2C8 then jmp 0x00573B23.
struct Rva00573F03 : Rva00573B23
{
	virtual ~Rva00573F03();
};
Rva00573F03::~Rva00573F03()
{
}
