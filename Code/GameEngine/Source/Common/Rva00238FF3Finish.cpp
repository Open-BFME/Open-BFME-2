// cl: /MD /Oy-
// ?rva00238FF3@Rva00238E1B@@QAEXPAVRva00238FF3Arg@@@Z @0x00238FF3 72B
// Leaf walk: set the "drawables" phase on the host, then call w14 for every
// node on the m_head list, then clear the arg slot through v31 and finish v06.
// Evidence: caller 0x00245E59; string "drawables" at 0x007ED678.

class Rva00238FF3Arg
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05(const char *s);
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31(void **pp);
};

class Rva00238FF3Node
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14(Rva00238FF3Arg *a);
private:
	char m_pad[0x100];
public:
	Rva00238FF3Node *m_next;
};

class Rva00238E1B
{
public:
	void rva00238FF3(Rva00238FF3Arg *arg);
private:
	char m_pad0[0x14];
	Rva00238FF3Node *m_head;
};

void Rva00238E1B::rva00238FF3(Rva00238FF3Arg *arg)
{
	arg->v05("drawables");
	Rva00238FF3Node *p = m_head;
	for (; p != 0; p = p->m_next)
		p->w14(arg);
	Rva00238FF3Arg *host = arg;
	void *zero = 0;
	host->v31(&zero);
	host->v06();
}
