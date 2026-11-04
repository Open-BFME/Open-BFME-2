// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
//
// ?rva003B693A@ScriptList@@QAEXXZ @0x003B693A (59B): clears one script list.
// Target evidence: 0x003B48E4 runs on the holder with its +4 base subobject
// (null-guarded conversion) as argument; the 0x20-byte lists at +0x0C and +0x2C
// are each drained (0x003B6676 / 0x003B56DC) and then have their record marks
// cleared (0x003B3EEA, the second as a tail jump). Class names and the base
// split are neutral views of those rowed callees' receivers, not recovered names;
// the receiver is ScriptList (pinned, WB 0xaa4f70; callers hold it at SidesInfo+8).
class Rva003B48E4
{
public:
	void rva003B48E4(void *arg);
	char m_pad00[0x4];
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
public:
	void rva003B3EEA();
	char m_pad00[0xC];
	unsigned int m_entries; // +0x0C
	char m_pad10[0xC];
	int m_index; // +0x1C
};
class ScriptList : public Rva003B48E4, public Rva003B693ABase4
{
public:
	void rva003B693A();
private:
	Rva003B573E m_0c;
	Rva003B573E m_2c;
};
void ScriptList::rva003B693A()
{
	rva003B48E4((Rva003B693ABase4 *)this);
	m_0c.rva003B6676();
	((Rva003B3EEAOwner *)&m_0c)->rva003B3EEA();
	m_2c.rva003B56DC();
	((Rva003B3EEAOwner *)&m_2c)->rva003B3EEA();
}
