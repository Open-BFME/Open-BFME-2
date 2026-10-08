// ?rva0040A7F1@Rva0040A7F1@@QBEHH@Z @0x0040A7F1 30B
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Evidence: unlock lane; unsigned bounds-checked index over an int range, the
// +4/+8 twin of the matched sibling Rva0040A7D5 (begin-end at +0/+4). Count is
// the byte-difference m_end-m_begin shifted right arithmetically by 2 and then
// reinterpreted unsigned, which is what gives retail its single `sar edx,2`
// followed by an unsigned `jb` rather than a logical `shr`. The element base is
// read through vb(), a volatile-qualified pointer read: that defeats address
// strength reduction, so MSVC keeps the index in eax and re-reads m_begin into
// the now-dead ecx inside the taken branch (mov ecx,[ecx+4] / mov eax,[ecx+eax*4])
// and builds the count as mov edx,[ecx+8] / sub edx,[ecx+4] with m_begin taken
// from memory. Callers 0x00409B73 0x0040BD91.
class Rva0040A7F1
{
public:
	int rva0040A7F1(int index) const;
private:
	const int *vb() const { return *(const int *volatile *)&m_begin; }
	int m_pad;
	const int *m_begin;
	const int *m_end;
};

int Rva0040A7F1::rva0040A7F1(int index) const
{
	unsigned int count = (unsigned int)(((const char *)m_end - (const char *)m_begin) >> 2);
	if ((unsigned int)index >= count)
		return 0;
	return vb()[index];
}

// ?rva0040A80F@Rva0040A80F@@QBEHH@Z @0x0040A80F 30B: the same accessor for
// the range at +0x10/+0x14, same recipe (callers in the 0x00409B73 family).
class Rva0040A80F
{
public:
	int rva0040A80F(int index) const;
private:
	const int *vb() const { return *(const int *volatile *)&m_begin; }
	int m_pad[4];
	const int *m_begin;
	const int *m_end;
};

int Rva0040A80F::rva0040A80F(int index) const
{
	unsigned int count = (unsigned int)(((const char *)m_end - (const char *)m_begin) >> 2);
	if ((unsigned int)index >= count)
		return 0;
	return vb()[index];
}
