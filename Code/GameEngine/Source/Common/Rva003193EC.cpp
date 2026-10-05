// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva003193EC@Rva003193EC@@QAE_NH@Z @0x003193EC 39B: thiscall bool method
// adding BfmeY1038 value at +0x78 to its int arg then comparing against the
// rowed free helper 0x003192B9 result. Evidence: packet disasm with pinned
// bfmeVal1038 0x0040CF91 plus rowed Rva003192B9Get plus ret-4 single int arg
// plus setle bool return, callers 0x002B6CD6 0x002B6D6F 0x00319422.

class BfmeY1038
{
public:
	int bfmeVal1038();
};

class Rva0037DCA5
{
public:
	int rva0037DCA5();
};

void *Rva003192B9Get(void *key);

class Rva003193EC
{
public:
	bool rva003193EC(int x);
	bool rva00319413(Rva0037DCA5 *p);
private:
	char m_pad00[0x78];
	BfmeY1038 *m_78;
};

bool Rva003193EC::rva003193EC(int x)
{
	int v = m_78->bfmeVal1038();
	int total = v + x;
	void *got = Rva003192B9Get(this);
	return total <= (int)got;
}

bool Rva003193EC::rva00319413(Rva0037DCA5 *p)
{
	return rva003193EC(p->rva0037DCA5());
}
