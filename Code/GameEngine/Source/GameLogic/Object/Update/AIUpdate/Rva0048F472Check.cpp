// cl: /DNDEBUG /MD
// ?Rva0048F472IsEqual@@YG_NPAX@Z @ 0x0048F472 58B
// Evidence: single void* arg ret 4 stdcall bool; member +0x254 null-checked; virtual slots 0x10 and 0x18 returning float compared for equality; caller 0x0048FAB5 in 0x0048F828; unblocks 0x0048F828.
class Rva0048F472Inner
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual float s4();
	virtual void s5();
	virtual float s6();
};

class Rva0048F472Outer
{
public:
	char m_pad[0x254];
	Rva0048F472Inner *m_ptr254;
};

bool __stdcall Rva0048F472IsEqual(void *p)
{
	Rva0048F472Outer *o = (Rva0048F472Outer *)p;
	Rva0048F472Inner *q = o->m_ptr254;
	if (q != 0) {
		float a = q->s4();
		float b = q->s6();
		if (a == b)
			return true;
	}
	return false;
}
