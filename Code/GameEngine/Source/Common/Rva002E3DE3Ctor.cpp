// cl: /MD /EHsc
//
// ??0Rva002E3DE3@@QAE@HH@Z retail 0x002E3DE3 71B.
// Evidence: forwards the list head at 0x00DFF0B8 (the global the rowed
// Rva002E3714Unlink walks) and both stack arguments to the base ctor at
// 0x002E3D7B, enters unwind state 0, installs vtable 0x00C04C04, stores the
// same head at +0x10 and calls the rowed no-argument Rva002E373CClear at
// 0x002E373C, returning with ret 8. Names are generated; the argument types
// and the base's contents are not established.

struct Rva002E36D5Node;
extern Rva002E36D5Node *g_00DFF0B8;

void Rva002E373CClear();

class Rva002E3D7BBase
{
public:
	Rva002E3D7BBase(Rva002E36D5Node **head, int first, int second);
	virtual ~Rva002E3D7BBase();
private:
	char m_pad04[0xC];
};

class Rva002E3DE3 : public Rva002E3D7BBase
{
public:
	Rva002E3DE3(int first, int second);
	virtual ~Rva002E3DE3();
private:
	Rva002E36D5Node **m_head10;
};

Rva002E3DE3::Rva002E3DE3(int first, int second)
	: Rva002E3D7BBase(&g_00DFF0B8, first, second), m_head10(&g_00DFF0B8)
{
	Rva002E373CClear();
}
