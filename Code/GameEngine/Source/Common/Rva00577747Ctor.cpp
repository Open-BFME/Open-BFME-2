// cl: /O1 /DNDEBUG /MD
// ???0Rva005772BF@@QAE@PAXH@Z retail 0x00577747 89B
// The body calls the rowed 0x00575383 holder constructor with arg0, then
// allocates 0x3C bytes and calls 0x005776A7 with (this,arg1). The vtable and
// +8 holder correspond to the rowed Rva005772BF destructor. The nested type
// name is address-derived; its layout and argument meanings remain unresolved.
class Rva00575383
{
public:
	Rva00575383(void *held);
	virtual ~Rva00575383() {}
	void *m_field04;
};
class Rva005772BF;
class Rva005776A7
{
public:
	Rva005776A7(Rva005772BF *owner, int arg);
private:
	char m_storage[0x3c];
};
class Rva005772BF : public Rva00575383
{
public:
	virtual ~Rva005772BF();
	Rva005772BF(void *held, int arg);
private:
	void *m_unmodelled_08;
};
Rva005772BF::Rva005772BF(void *held, int arg)
	: Rva00575383(held)
{
	m_unmodelled_08 = new Rva005776A7(this, arg);
}
