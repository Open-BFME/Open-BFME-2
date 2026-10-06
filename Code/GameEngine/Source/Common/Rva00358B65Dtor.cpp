// cl: /MD /EHsc
// ??1Rva00358B65@@QAE@XZ @0x00358B65
// (57B): holder dtor with AsciiString narrow at +0 via releaseBuffer plus
// TargetRef at +4 via fastcall Release; unblocks 59B+53B.
// Identity via ReleaseTreeHintRef 0x0007DEEF plus releaseBuffer 0x00036410
// plus callers 0x00358DE5/0x00358E87; non-virtual QAE frameless? EBP? /O1.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

template <typename T> class StringBase
{
	void releaseBuffer();
public:
	~StringBase() { releaseBuffer(); }
private:
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva00358B65
{
public:
	~Rva00358B65();
private:
	StringBase<char> m_00;
	TargetRef00217D4C *m_04;
};

Rva00358B65::~Rva00358B65()
{
	if (m_04)
		ReleaseTreeHintRef00217D4C(m_04);
}
