// cl: /DNDEBUG /MD /EHsc
//
// ?rva0027295B@Drawable@@QAEXPAX@Z retail 0x0027295B 22B
// Unlock lane: first-element tail call through member +0x14C array of ptrs;
// virtual slot 0x68 takes one void* and returns void. Caller 0x002975AC.
// The element-list local must be the pointer-to-pointer so the loaded element
// stays in eax while the vtable goes to edx.
class Rva00272835Elem
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual bool s05(int a, int b);
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26(void *arg);
};

class Drawable
{
public:
	void rva0027295B(void *arg);
private:
	char m_pad[0x14C];
	Rva00272835Elem **m_list;
};

void Drawable::rva0027295B(void *arg)
{
	Rva00272835Elem **p = m_list;
	if (*p != 0)
		(*p)->s26(arg);
}
