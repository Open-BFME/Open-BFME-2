// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
//
// ?rva003B693A@Rva003B693AHolder@@QAEXXZ @0x003B693A (59B): clears one script holder.
// Target evidence: 0x003B48E4 runs on the holder with its +4 base subobject
// (null-guarded conversion) as argument; the 0x20-byte lists at +0x0C and +0x2C
// are each drained (0x003B6676 / 0x003B56DC) and then have their record marks
// cleared (0x003B3EEA, the second as a tail jump). Class names and the base
// split are neutral views of those rowed callees' receivers, not recovered names.
class Rva003B48E4
{
public:
	void rva003B48E4(void *p);
	int pad0;
};
class Rva003B693ABase4
{
public:
	int pad4;
	int pad8;
};
class Rva003B573E
{
public:
	void rva003B6676();
	void rva003B56DC();
private:
	char body[0x20];
};
struct Rva003B3EEAOwner
{
	void rva003B3EEA();
};
class Rva003B693AHolder : public Rva003B48E4, public Rva003B693ABase4
{
public:
	void rva003B693A();
private:
	Rva003B573E m_0c;
	Rva003B573E m_2c;
};
void Rva003B693AHolder::rva003B693A()
{
	rva003B48E4((Rva003B693ABase4 *)this);
	m_0c.rva003B6676();
	((Rva003B3EEAOwner *)&m_0c)->rva003B3EEA();
	m_2c.rva003B56DC();
	((Rva003B3EEAOwner *)&m_2c)->rva003B3EEA();
}
