// cl: /O1 /DNDEBUG /MD
// ???0Rva00575D45@@QAE@PAXH@Z retail 0x005763ED 89B
// The body calls the rowed 0x00575383 holder constructor with arg0, then
// allocates 0x50 bytes and calls the subordinate constructor at 0x0057621A
// with (this,arg1). The derived vtable and its +8 holder are independently
// supported by the rowed Rva00575D45 destructor and slot-3 method. The nested
// type name is address-derived; its layout and both argument meanings remain
// unresolved. Its pin records the direct constructor call target only.
class Rva00575383
{
public:
	Rva00575383(void *held);
	virtual ~Rva00575383() {}
	void *m_field04;
};
class Rva00575D45;
class Rva0057621A
{
public:
	Rva0057621A(Rva00575D45 *owner, int arg);
private:
	char m_storage[0x50];
};
class Rva00575D45 : public Rva00575383
{
public:
	virtual ~Rva00575D45();
	Rva00575D45(void *held, int arg);
private:
	void *m_unmodelled_08;
};
Rva00575D45::Rva00575D45(void *held, int arg)
	: Rva00575383(held)
{
	m_unmodelled_08 = new Rva0057621A(this, arg);
}
