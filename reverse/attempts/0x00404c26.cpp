// ?Rva00404C26Get@Rva00404C26Store@@QAEPAUBfmeStringRecord00404BF3@@H@Z
// partial score=0.93 date=2026-09-26
// ?Rva00404C26Get@Rva00404C26Store@@QAEPAUBfmeStringRecord00404BF3@@H@Z
// partial score=0.93 date=2026-09-26
// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// Retail 0x00404C26 58B gap between BfmeStringRecord00404BF3 copy and _Construct
// in Code/GameEngine/Source/Common/StringRecordCopyBFME2.cpp. Bounds-checked
// accessor: index table at +0x28 masked with 0x7fffffff, vector of 0x18-byte
// records at +0x120/+0x124, returns &vec[idx] or NULL. Callers at 0x00404D0D,
// 0x00404D35, 0x004050BD, 0x0056C1BE pass loop index 0..0x13 and read floats
// at +0x4/+0x8/+0x10. Element type reuses honest BfmeStringRecord00404BF3.
// /G7 required for imul-0x18 (probe-proven: /O1 alone gives lea lea).
// Near miss: ours keeps m_begin in edi (mov edi+sub reg+add reg, divisor in
// ecx, 56B) vs retail reloads it (sub mem+add mem, divisor in edi, 58B).
// Branch layout fixed via if (idx < count) return &m_begin[idx]; return 0;
// which yields jae-to-null fall-through computation matching retail.
struct BfmeStringRecord00404BF3
{
	char bytes[0x18];
};

class Rva00404C26Store
{
public:
	BfmeStringRecord00404BF3 *Rva00404C26Get(int i);
private:
	char m_pad0[0x28];
	int m_indices[62];
	BfmeStringRecord00404BF3 *m_begin;
	BfmeStringRecord00404BF3 *m_end;
	BfmeStringRecord00404BF3 *m_cap;
};

// ?Rva00404C26Get@Rva00404C26Store@@QAEPAUBfmeStringRecord00404BF3@@H@Z present-unmatched
BfmeStringRecord00404BF3 *Rva00404C26Store::Rva00404C26Get(int i)
{
	int raw = m_indices[i];
	int count = m_end - m_begin;
	unsigned int idx = (unsigned int)raw & 0x7fffffff;
	if (idx < (unsigned int)count)
		return &m_begin[idx];
	return 0;
}
