// ?rva005C65F1@Rva005C65F1@@QAEXXZ
// cl: /MD
// ?rva005C65F1@Rva005C65F1@@QAEXXZ retail 0x005C65F1 (75B).
// Free leaf (all callees rowed: abs via gen-small import row, virtual slot 4
// indirect, EH_prolog row); two tail-jump callers (0x00577969 slot-2 wrapper,
// 0x0053EDEF) readjust this and forward here.
// Layout from retail: vptr +0, flag byte +4, ints +C/+10; virtual at +0x10
// fills two ints at [ebp-8]/[ebp-4]; Manhattan distance >2 commits them.
//
// The banked 0.97 attempt bound the two abs() results to named locals and wrote
// `dy + dx > 2`; MSVC then kept the sum in eax (`add eax,edi; cmp eax,2`) while
// retail accumulates into edi (`add edi,eax; cmp edi,2`). Writing the whole
// Manhattan test inline in the `if` makes the compiler evaluate the operands
// left to right and pick edi as the accumulator, which is retail's shape.

extern "C" int __cdecl abs(int value);

class Rva005C65F1
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void GetPos(int *out);
	void rva005C65F1();

private:
	bool m_moved;
	char m_pad[7];
	int m_x;
	int m_y;
};

void Rva005C65F1::rva005C65F1()
{
	int pos[2];
	GetPos(pos);
	if (abs(m_x - pos[0]) + abs(m_y - pos[1]) > 2) {
		m_x = pos[0];
		m_y = pos[1];
		m_moved = true;
	}
}
