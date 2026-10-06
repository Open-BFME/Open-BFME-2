// cl: /MD
// ?rva006FBC10@Rva006FBC90Owner@@UAEXXZ @0x006FBC10 25B, vslot 11 of
// 0x008ED880 (the Rva006FBC90Owner dtor class, slot 13 is the matched
// rva006FBC30). Releases the +0x1C AptValue when set, then tail-jumps to the
// rowed Rva006DE150::rva006DE150 0x006DE150 on the same this.
// Structural inference: this passes unchanged to that method, so the class
// is modelled as deriving from a polymorphic Rva006DE150 (shared vptr at +0);
// /O2 like the slot-13 sibling Rva006FBC30Slot13.cpp.
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006DE150
{
public:
	virtual ~Rva006DE150();
	void rva006DE150();
};

class Rva006FBC90Owner : public Rva006DE150
{
public:
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void rva006FBC10();
private:
	char m_pad[0x18];
	AptValue *m_ctor; // +0x1C
};

void Rva006FBC90Owner::rva006FBC10()
{
	if (m_ctor != 0)
		m_ctor->Release();
	rva006DE150();
}
