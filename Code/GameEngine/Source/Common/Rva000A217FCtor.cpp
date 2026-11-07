// cl: /DNDEBUG /MD
//
// ??0Rva000A217F@@QAE@PAX@Z @0x000A217F 24B.
// Rva000A217F ctor forwarding void* to base Rva000A2137, then installing its
// own table. Evidence: pin name, LINK BONUS 116B via factory Rva0008FABBCreate
// in Rva0008F8EBFactories.cpp, rowed/pinned base ctor 0x000A2137, callers 1.
//
// The class is a GameWindow (LINK-617). Retail's table VA 0x00BC9020, which
// this constructor installs, has GameWindow's eleven slots (target facts):
// slot 0 the deleting destructor 0x0008FFC4 (ICF-shared by the 0x00BC7DC8,
// 0x00BC8FF4 and 0x00BC9020 tables; it calls the folded destructor 0x000A43C8,
// a jmp to Rva0078D310Host's 0x00104E03), slots 1 and 2 Rva000A2137's input
// and system handlers 0x000A214F and 0x000A2167 (also in Rva000A2137's own
// table 0x00BC8FF4), slot 3 this class's draw 0x000A261C, slots 4-6, 8 and 9
// GameWindow's own 0x0008FF56, 0x0009FD78, 0x00313913, 0x0031393A and
// 0x0008FF78, slot 7 this class's factory getter 0x000A219D (returns
// Rva0008FABBCreate) and slot 10 0x0047A699, Rva0078D310Host's `return
// false` (the table 0x00BCF818 its constructors install; the canonical
// GameWindow's own slot 10 at 0x00C0BBCC is 0x0050B5C6, `return true`).
// Declaring the chain over the canonical GameWindow lets the compiler emit
// and relocate the table.
#include "../../Include/GameClient/Bfme2GameWindow.h"

class Rva0078D310Host : public GameWindow
{
public:
	virtual ~Rva0078D310Host();
	virtual bool vslot10() { return false; }
};

class Rva000A2137 : public Rva0078D310Host
{
public:
	Rva000A2137(void *context);
	virtual WindowMsgHandledType input(unsigned int msg, unsigned int mData1, unsigned int mData2);
	virtual WindowMsgHandledType bfmeGoEHCb(unsigned int msg, unsigned int mData1, unsigned int mData2);
};

class Rva000A217F : public Rva000A2137
{
public:
	Rva000A217F(void *context);
	virtual int draw(void *instData);
	virtual void *fetchCreateInstance();
};

Rva000A217F::Rva000A217F(void *context) : Rva000A2137(context)
{
}
