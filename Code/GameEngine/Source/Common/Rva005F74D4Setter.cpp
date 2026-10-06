// cl: /MD
// ?rva005F74D4@Rva005F74D4@@QAEXPAVRva005F6AB0@@@Z retail 0x005F74D4 35B
// Evidence: cmp new vs old at +0 then store new before dtor plus delete; rowed dtor 0x005F6AB0 plus rowed operator delete 0x0002FD60; caller 0x005F8015; precedent plus4 forwarder file layout
class Rva005F6AB0
{
public:
	virtual ~Rva005F6AB0();
};

class Rva005F74D4
{
public:
	void rva005F74D4(Rva005F6AB0 *p);
private:
	Rva005F6AB0 *m_ptr00;
};

void Rva005F74D4::rva005F74D4(Rva005F6AB0 *p)
{
	if (p != m_ptr00) {
		Rva005F6AB0 *old = m_ptr00;
		m_ptr00 = p;
		if (old) {
			old->Rva005F6AB0::~Rva005F6AB0();
			::operator delete(old);
		}
	}
}
