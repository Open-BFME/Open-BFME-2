// ?rva003B8D4D@Rva003B8D4D@@QAEHH@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /MD
// ?rva003B8D4D@Rva003B8D4D@@QAEHH@Z @0x003B8D4D 36B: bounds-checked indexed
// table tail call. Returns the pinned 0x0052C7A2 entry at table[idx] when
// 0 <= idx < count, else 0. Evidence: signed jl for <0, sar-count with
// unsigned jae bounds check, scaled table load straight into ecx for the
// tail jmp; second arg dead.
class Rva0052C7A2
{
public:
	int rva0052C7A2(void);
};

class Rva003B8D4D
{
public:
	int rva003B8D4D(int /*unused*/);

private:
	char m_pad00[0x10];
	int m_10;
	char *m_14;
	char *m_18;
};

int Rva003B8D4D::rva003B8D4D(int /*unused*/)
{
	int idx = m_10;
	if (idx < 0)
		return 0;
	unsigned int count = (m_18 - m_14) >> 2;
	if ((unsigned int)idx >= count)
		return 0;
	return ((Rva0052C7A2 *)((int *)m_14)[idx])->rva0052C7A2();
}
