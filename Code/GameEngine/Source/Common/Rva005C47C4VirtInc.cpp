// cl: /O1
// ?rva005C47C4@Rva005C47C4@@QAEXH@Z 0x005C47C4 24B evidence: gap between dtor 0x005C4758 and const getter 0x005C47EA; thiscall void(int unused) via ret 4 plus no eax return; virtual slot 0 cmp plus14 with inc; honest Rva name
class Rva005C47C4
{
public:
	virtual int v0();
	void rva005C47C4(int unused);

private:
	char m_04[0x10];
	int m_14;
};

void Rva005C47C4::rva005C47C4(int /*unused*/)
{
	int cur = m_14;
	int r = v0();
	if (cur <= r)
		m_14 = cur + 1;
}
