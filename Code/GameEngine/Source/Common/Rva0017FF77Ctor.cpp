// cl: /EHsc /MD
//
// ??0Rva0017FF77@@QAE@PBDHH@Z @0x0017FF77 (77B):
// Ctor with GenBase base plus StringClass at 0x18 plus ints at 0x14 0x1C 0x20 plus vtable.
// Evidence: unlock lane callees GenBase 0x0061ED40 StringClass 0x000F0ED1 caller 0x001800EE.
extern "C" char GenBase009EB7D0_vtbl;
class __declspec(novtable) GenBase009EB7D0
{
public:
	__declspec(noinline) GenBase009EB7D0();
	virtual void handle();
private:
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};
class EmptyBase0017FF77
{
public:
	EmptyBase0017FF77() {}
	~EmptyBase0017FF77();
};
class StringClass
{
public:
	StringClass(const char *name, bool flag);
};
class Rva0017FF77 : public GenBase009EB7D0, public EmptyBase0017FF77
{
public:
	Rva0017FF77(const char *name, int a, int b);
private:
	int m_14;
	StringClass m_str18;
	int m_1c;
	int m_20;
};

Rva0017FF77::Rva0017FF77(const char *name, int a, int b) : m_14(0), m_str18(name, false), m_1c(a), m_20(b)
{
}
