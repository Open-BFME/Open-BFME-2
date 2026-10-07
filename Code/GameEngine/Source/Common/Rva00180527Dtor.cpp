// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??1Rva001805E0@@UAE@XZ @0x00180527 90B
// Virtual dtor twin of Rva0017FB94 (89B) and Rva00151632 (90B): stores
// vtable 0x007D4FD0, deletes +0x14 link via slot-0 virtual get(0) plus
// operator delete 0x0002FD60 row, tears down +0x18 StringClass via
// 0x00610A40 pin, delegates to base 0x0061ED80 pin. Called from 0x0018062D.
// Layout mirrors ctor Rva001805E0Ctor.cpp: vtable + pad 0x10 + link + String.
class Rva001805E0Link
{
public:
	virtual void *get(int x);
};

class StringClass
{
public:
	~StringClass() { Free_String(); }
private:
	void Free_String();
};

class Rva0061ED80
{
public:
	virtual ~Rva0061ED80();
};

class Rva001805E0 : public Rva0061ED80
{
public:
	virtual ~Rva001805E0();

private:
	char m_pad04[0x10];
	Rva001805E0Link *m_link;
	StringClass m_name;
};

Rva001805E0::~Rva001805E0()
{
	void *tmp = m_link ? m_link->get(0) : 0;
	delete tmp;
}
