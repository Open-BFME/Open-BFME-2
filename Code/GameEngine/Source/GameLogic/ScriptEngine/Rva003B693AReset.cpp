// cl: /O1 /DNDEBUG /MD
//
// ?rva003B693A@Rva003B693A@@QAEXXZ @0x003B693A 59B.
// Reset next to the ScriptList helpers: runs the recursive script clear
// 0x003B48E4 on itself, passing its second base (+4, null-checked), then
// sweeps the two indexed record tables at +0x0C and +0x2C: each gets its
// element pass (0x003B6676 / 0x003B56DC, two 98-byte instantiations of one
// template) followed by the shared mark-flag clear 0x003B3EEA, the last one
// as a tail jump. Owner, base and table types are unknown; offsets and call
// order are from the retail bytes.

class Rva003B48E4
{
public:
	void rva003B48E4(void *p);

private:
	int unknown00;
};

class Rva003B693ABase04
{
	int unknown04;
	int unknown08;
};

class Rva003B3EEAOwner
{
public:
	void rva003B3EEA();

private:
	char unknown00[0x20];
};

class Rva003B6676 : public Rva003B3EEAOwner
{
public:
	void rva003B6676();
};

class Rva003B56DC : public Rva003B3EEAOwner
{
public:
	void rva003B56DC();
};

class Rva003B693A : public Rva003B48E4, public Rva003B693ABase04
{
public:
	void rva003B693A();

private:
	Rva003B6676 m0C;
	Rva003B56DC m2C;
};

void Rva003B693A::rva003B693A()
{
	rva003B48E4(static_cast<Rva003B693ABase04 *>(this));
	m0C.rva003B6676();
	m0C.rva003B3EEA();
	m2C.rva003B56DC();
	m2C.rva003B3EEA();
}
