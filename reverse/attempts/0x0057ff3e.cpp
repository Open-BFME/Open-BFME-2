// ??0Rva0057FE6B@@QAE@PAUTargetRef00217D4C@@H_N@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0057FE6B@@QAE@PAUTargetRef00217D4C@@H_N@Z @0x0057FF3E 95B
// Evidence: unlock lane, vtable 0x0086F64C, base pin 0x002D2C34, +0x58 refcount inc, +0x5C -1, +0x60 arg2, +0x64 0, +0x68 0, conditional row 0x0057FD6E, caller 0x00441F6C.
class Rva002D2C34
{
public:
	void rva002D2C34();
};

class Rva0057FD6E
{
public:
	void rva0057FD6E();
};

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva0057FE6B : public Rva005248D0
{
public:
	Rva0057FE6B(TargetRef00217D4C *a, int b, bool c);
private:
	char m_pad0[84];
	TargetRef00217D4C *m_58;
	int m_5C;
	int m_60;
	void *m_64;
	unsigned char m_68;
};

Rva0057FE6B::Rva0057FE6B(TargetRef00217D4C *a, int b, bool c)
{
	((Rva002D2C34 *)this)->rva002D2C34();
	m_58 = a;
	if (a != 0) {
		++a->references;
	}
	m_5C = -1;
	m_60 = b;
	m_64 = 0;
	m_68 = 0;
	if (c != 0) {
		((Rva0057FD6E *)this)->rva0057FD6E();
	}
}
