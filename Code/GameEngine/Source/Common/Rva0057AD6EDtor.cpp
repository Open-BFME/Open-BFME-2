// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0057AD6E@@UAE@XZ @0x0057AD6E 158B
// Multi-vtable dtor: 3 base vptrs, AsciiString +0x10, Rva0052413E +0x18, Rva000AD6F4 +0x28 with inline dtor->clear, list<int> +0x30 with per-element virtual slot5 cleanup via raw chase. Evidence: deleting-dtor caller 0x0042D523, assign-release caller 0x0042D81D, member dtor rows.
#include "ascii_string.h"
#include <list>

class Base1
{
public:
	virtual void b1();
	~Base1() {}
};
class Base2
{
public:
	virtual void b2();
	~Base2() {}
};
class Base3
{
public:
	virtual void b3();
	~Base3() {}
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0x10];
};

class Rva000AD6F4
{
public:
	void clear();
	~Rva000AD6F4() { clear(); }
private:
	void *m_ptr;
};
// ??1Rva000AD6F4@@QAE@XZ present-unmatched

struct YBase
{
	virtual void y0();
	virtual void y1();
	virtual void y2();
	virtual void y3();
	virtual void y4();
	virtual void y5(void *p);
};

struct XNode
{
	char m_pad[0x54];
	YBase *m_y;
};

class Rva0057AD6E : public Base1, public Base2, public Base3
{
public:
	virtual ~Rva0057AD6E();
private:
	int m_0C;
	AsciiString m_10;
	int m_14;
	Rva0052413E m_18;
	Rva000AD6F4 m_28;
	int m_2C;
	_STL::list<int> m_30;
};

Rva0057AD6E::~Rva0057AD6E()
{
	void *head = *(void **)&m_30;
	void *cur = *(void **)head;
	if (cur != head) {
		void *nxt;
		XNode *x;
		YBase *y;
		do {
			nxt = *(void **)cur;
			x = *(XNode **)((char *)cur + 8);
			y = x->m_y;
			y->y5(x);
			cur = nxt;
		} while (nxt != head);
	}
}
