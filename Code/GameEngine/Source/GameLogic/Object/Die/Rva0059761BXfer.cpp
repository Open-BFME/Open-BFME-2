// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?rva0059761B@Rva0059761B@@QAEXPAX@Z 47B @0x0059761B: thiscall with one
// void* arg (Xfer* per caller 0x004EC1D9 which passes the same Xfer* it
// passes to rowed Xfer-taking 0x0059992A); builds two-true-byte local and
// calls arg slot 0x28 with &local then arg slot 0x7c with this+0x3c.
// Evidence: frame/push/leave/ret-4 shape plus slot offsets; caller shows
// same slot-0x28 pattern with bytes 1,5 and passes Xfer*; next TU
// Rva00597693Ctor.cpp carries int at +0x3C and supplies the // cl: line.
// Owner identity unproven so honest address name.

struct TwoTrue
{
	bool a;
	bool b;
};

class XferDummy
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(TwoTrue *t);
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
	virtual void v31(int *p);
};

class Rva0059761B
{
public:
	void rva0059761B(void *p);
private:
	char m_pad[0x3C];
	int m_3C;
};

void Rva0059761B::rva0059761B(void *p)
{
	XferDummy *xfer = (XferDummy *)p;
	TwoTrue tmp;
	tmp.a = true;
	tmp.b = true;
	xfer->v10(&tmp);
	xfer->v31(&m_3C);
}
