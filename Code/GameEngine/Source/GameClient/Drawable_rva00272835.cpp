// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272835@Drawable@@QAE_NHH@Z retail 0x00272835 59B
// Evidence: unlock lane; member +0x14C array of ptrs; virtual slot 0xA4 returns ptr plus slot 0x14 takes 2 ints returns bool; callees all rowed-pinned; callers 9 incl 0x000B710D 0x000B75FF 0x000CFDFB; prev-next Drawable same flags.
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
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
	virtual void *s41();
};

class Drawable
{
public:
	bool rva00272835(int a, int b);
private:
	char m_pad[0x14C];
	Rva00272835Elem **m_list;
};

bool Drawable::rva00272835(int a, int b)
{
	Rva00272835Elem **cur = m_list;
	while (*cur != 0) {
		Rva00272835Elem *e = *cur;
		void *p = e->s41();
		if (p != 0) {
			Rva00272835Elem *q = (Rva00272835Elem *)p;
			if (q->s05(a, b))
				return true;
		}
		++cur;
	}
	return false;
}
