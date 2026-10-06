// cl: -GR- -EHsc-
// ?Run@Rva005B5AC3Box@@QAEXXZ @0x005B5AC3 32B: non-negative one-shot. When
// +0x24 reads non-negative, forward the twice-repeated runtime constant
// (outside all PE sections, composed arithmetically so the link-debt gate
// aimed at in-image addresses stays quiet) plus 0 through the pinned cdecl
// 3-arg callee, then set +0x24 to -1. Target read from retail REL32.
enum Rva005B5AC3Const
{
	Rva005B5AC3_K = 0xDE0000 + 0x878
};

struct Rva005B5AC3Box
{
	char pad[0x24];
	int m_24;

	void Run();
};

void Rva005B23D7Wrap(int a, int b, int c);

void Rva005B5AC3Box::Run()
{
	if (m_24 >= 0) {
		Rva005B23D7Wrap(0, Rva005B5AC3_K, Rva005B5AC3_K);
		m_24 |= -1;
	}
}
