// cl: /DNDEBUG /MD
//
// ?rva003EF2E0@Rva003EF2E0@@QAEXXZ @0x003EF2E0 31B (dump range 18).
// Clear-plus-register: zeroes +0x44, points +0x48 at the +0x4C element,
// runs the rowed 0x003EED9D member, then appends itself to the global list
// through rowed 0x005A0B4C append.
struct Rva002BA8F1Listener
{
	char opaque[4];
};
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};
extern Rva005A0B4CList g_00E02E88;

class Rva003EED9D
{
public:
	void rva003EED9D();
};

class Rva003EF2E0
{
public:
	void rva003EF2E0();
private:
	char m_pad[0x44];
	int m_44;
	void *m_48; // +0x48
};

void Rva003EF2E0::rva003EF2E0()
{
	m_44 &= 0; // retail and-form clear
	m_48 = (char *)this + 0x4C;
	((Rva003EED9D *)this)->rva003EED9D();
	g_00E02E88.append((Rva002BA8F1Listener *)this);
}
