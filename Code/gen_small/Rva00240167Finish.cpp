// ?rva00240167@Rva00240167@@QAEPAVAsciiString@@V2@@Z
// partial score=0.96 date=2026-10-01
// ?rva00240167@Rva00240167@@QAEPAVAsciiString@@V2@@Z
// partial score=0.96 date=2026-10-01
// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
// ?rva00240167@Rva00240167@@QAEPAVAsciiString@@V2@@Z @ 0x00240167 89B
// Circular name search at this+0x1C0 via compare 0x69D6 key by value via
// 0x36410. Follows TerrainTypes_findTerrain recipe. Evidence calls at
// 0x240188/0x2401A4 head +0x1C0 next +0 name +8 callers 0x245FE5/0x247C1A.
//
// The two remaining instructions were lea/push scheduling, not a loop shape:
// retail emits lea ecx,[esi+8] BEFORE push eax, and every direct spelling of
// cur->m_name emitted the push first. The rowed callee is
// ?compare@?$StringBase@D@@QBEHABV1@@Z -- a template member of StringBase<char>
// taking `const StringBase<char>&`, not a member of AsciiString taking
// `const AsciiString&`. Binding the node's name to a `const StringBase<char>&`
// local before the call is what makes VC7 materialise the base this-pointer as
// its own lea ahead of the argument push; using cur->m_name directly (or a
// static_cast to the same base) folds the two back together and reproduces the
// wrong order. Verified by an isolated sweep over 12 declaration and loop
// spellings; this was the only exact 89B match. The `throw()` specifier on the
// base compare is load-bearing: without it VC7 emits 93B.
typedef int Int;

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &str) const throw();
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();
private:
	void *m_data;
};

struct Rva00240167Node
{
	Rva00240167Node *m_next;
	char m_pad04[4];
	AsciiString m_name;
};

class Rva00240167
{
public:
	AsciiString *rva00240167(AsciiString name);
private:
	char m_pad00[0x1C0];
	Rva00240167Node *m_head;
};

AsciiString *Rva00240167::rva00240167(AsciiString name)
{
	for (Rva00240167Node *cur = m_head->m_next; cur != m_head; cur = cur->m_next) {
		const StringBase<char> &key = cur->m_name;
		if (key.compare(name) == 0)
			return &cur->m_name;
	}
	return 0;
}