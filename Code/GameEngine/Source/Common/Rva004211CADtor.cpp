// cl: /MD /GX
// ??1Rva004211CA@@UAE@XZ @ 0x004211CA 92B
// Dtor with vtable 0x0083BDFC, Ascii at +0x10, Unicode at +0x14, heap at +0x18
// freed via _free, then base Rva001E3624 pinned dtor. Unblocks deleting dtor
// 0x00421226. Layout from member offsets, base size 0x10 from first member.
// Evidence: mov [esi] vtable, test+free +0x18, releaseBuffer +0x14 wide
// +0x10 narrow, base call 0x001E3624, caller 0x00421229, neighbours
// 0x004210B0 and 0x0042169B.
extern "C" void __cdecl free(void *block);

template <typename T>
class StringBase
{
	void *m_data;
	void releaseBuffer();
public:
	~StringBase() { releaseBuffer(); }
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva001E3624
{
public:
	virtual ~Rva001E3624();
private:
	char m_pad[0x0C];
};

class Rva004211CA : public Rva001E3624
{
public:
	virtual ~Rva004211CA();
private:
	StringBase<char> m_ansi10;
	StringBase<unsigned short> m_wide14;
	void *m_heap18;
};

Rva004211CA::~Rva004211CA()
{
	if (m_heap18)
		free(m_heap18);
}
