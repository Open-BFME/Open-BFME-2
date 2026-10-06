// cl: /MD
// ??0Rva00051C6C@@QAE@ABV0@@Z @ 0x00051C6C 29B
// Evidence: __thiscall copy ctor via ecx plus ret 4 with this-return; +0x00 dword copy plus +0x04 BfmePoolRef10 copy ctor at 0x00051950; caller 0x00053FB0; neighbours Rva002D9893Copy plus Rva00051CBAEquals use /O1 /MD.
class BfmePoolRef10
{
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
private:
	void *m_target;
};

class Rva00051C6C
{
public:
	Rva00051C6C(const Rva00051C6C &other);

private:
	int m_00;
	BfmePoolRef10 m_04;
};

Rva00051C6C::Rva00051C6C(const Rva00051C6C &other) : m_00(other.m_00), m_04(other.m_04)
{
}
