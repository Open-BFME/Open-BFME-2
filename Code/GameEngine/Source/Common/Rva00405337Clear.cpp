// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// ?Rva00405337Clear@@YAXPAX0@Z @0x00405337 25B
// Range clear over 0x18-byte records with a StringBase<char> at +0.
// Evidence: free-function via callers 0x40536A 0xC04EE 0xC0663 (two pushes
// begin plus end, __cdecl ret); rowed callee StringBase<char>::clear
// 0x0048BA39; step 0x18 matches BfmeStringRecord00404BF3 in neighbouring
// StringRecordCopyBFME2 TU; name stays address-derived.
template <typename T>
class StringBase
{
public:
	void clear();
};

void Rva00405337Clear(void *begin, void *end)
{
	char *p = (char *)begin;
	char *e = (char *)end;
	for (; p != e; p += 0x18)
		((StringBase<char> *)p)->clear();
}
