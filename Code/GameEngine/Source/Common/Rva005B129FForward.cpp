// cl: -Oy- -GR- -EHsc-
int __cdecl rva005B09D8_i(int a, int b, int c, char* d);

struct Rva005B129FClass
{
	int m_0;
	int m_4;

	int rva005B129F(int a1, int a2);
};

// ?rva005B129F@Rva005B129FClass@@QAEHHH@Z @0x005B129F 38B: forwards
// (a2, m_4, a1, (char*)&a1+3) to the pinned cdecl callee, stores its result
// to m_4 and returns a1.
int Rva005B129FClass::rva005B129F(int a1, int a2)
{
	int r = rva005B09D8_i(a2, m_4, a1, (char*)&a1 + 3);
	m_4 = r;
	return a1;
}
