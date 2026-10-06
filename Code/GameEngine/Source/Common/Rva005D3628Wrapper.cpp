// cl: /DNDEBUG /MD /EHsc
// ??0Rva005D3628@@QAE@HH@Z @0x005D3628 66B new-wrapper.
// Forwards (a, b) to inner ctor 0x005D3506 (pinned, 108B object) via new 0x6C
// then stores result at +0. No vtable. Address-derived.
class Rva005D3506Inner
{
public:
	Rva005D3506Inner(int a, int b);
protected:
	unsigned char m_pad[0x6C];
};

class Rva005D3628
{
public:
	Rva005D3628(int a, int b);
protected:
	Rva005D3506Inner *m_0;
};

Rva005D3628::Rva005D3628(int a, int b)
	: m_0(new Rva005D3506Inner(a, b))
{
}
