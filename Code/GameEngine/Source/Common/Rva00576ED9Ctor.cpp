// cl: /O1 /DNDEBUG /MD
// ???0Rva00576B5E@@QAE@PAXH@Z retail 0x00576ED9 89B
// The body calls the rowed 0x00575383 holder constructor with arg0, then
// allocates 0x48 bytes and calls 0x00576DF1 with (this,arg1). The vtable and
// +8 holder correspond to the rowed Rva00576B5E destructor. The nested type
// name is address-derived; its layout and argument meanings remain unresolved.
class Rva00575383
{
public:
	Rva00575383(void *held);
	virtual ~Rva00575383() {}
	void *m_field04;
};
class Rva00576B5E;
class Rva00576DF1
{
public:
	Rva00576DF1(Rva00576B5E *owner, int arg);
private:
	char m_storage[0x48];
};
class Rva00576B5E : public Rva00575383
{
public:
	virtual ~Rva00576B5E();
	Rva00576B5E(void *held, int arg);
private:
	void *m_unmodelled_08;
};
Rva00576B5E::Rva00576B5E(void *held, int arg)
	: Rva00575383(held)
{
	m_unmodelled_08 = new Rva00576DF1(this, arg);
}
