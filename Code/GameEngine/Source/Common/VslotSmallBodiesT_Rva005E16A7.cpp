// cl: /DNDEBUG /MD
// Split from VslotSmallBodiesT.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch T. As in VslotSmallBodiesA-S, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// 0x0057BC25: tail call of the rowed 0x0057BAC4 on this object.
// Slot 8 of StrategicHUD::SelectionDetailsUIImpl's vftable 0x00C6F26C (its
// rowed ctor and dtor install it): virtual.
namespace StrategicHUD { class SelectionDetailsUIImpl; }
class StrategicHUD::SelectionDetailsUIImpl
{
public:
	void Close();
	virtual void rva0057BC25();
};


// 0x0058AD81 and 0x005EE2CF: the pinned Object command-button entry points
// for the argument, with the +0x08 button (and the +0x1C position).
class CommandButton;
struct Coord3D;
#include "../GameLogic/Object/object.h"
// 0x00596BA2: the unsigned +0x38 count as a Real (the argument is unused).
// 0x005C4212 and 0x005C4221: hand this object to virtual slot 3 (resp. 2)
// of the argument.
class Rva005C4212;
class Rva005C4212Visitor
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02(Rva005C4212 *o);
	virtual void v03(Rva005C4212 *o);
};
class Rva005C4212
{
public:
	void rva005C4212(Rva005C4212Visitor *v);
	void rva005C4221(Rva005C4212Visitor *v);
};



// 0x005DAA9E and 0x005DAC6D: copy the three words at +0x30 (resp. +0x2C)
// out, the first as a Real.
// 0x005E16A7 and 0x005E2126: the pinned INI::initFromINI on this object with
// the field table at VA 0x00C779F0 (resp. 0x00C77A98).
class INI;
#include "../../Include/Common/INI/FieldParse.h"
#include "../../Include/Common/INI/INI.h"
// The two tables (retail .rdata): Image/Title/Help strings at +8/+0xC/+0x10
// through the rowed INI::parseAsciiString (0x0002F11E), and
// ProgressOverlayColor at +8 through the rowed INI::parseColorInt (0x0002F3FE),
// each closed by a null entry.
extern const FieldParse g_rva005E16A7FieldParse[] =
{
	{ "Image", INI::parseAsciiString, 0, 0x8 },
	{ "Title", INI::parseAsciiString, 0, 0xC },
	{ "Help", INI::parseAsciiString, 0, 0x10 },
	{ 0, 0, 0, 0 }
};
extern const FieldParse g_rva005E2126FieldParse[] =
{
	{ "ProgressOverlayColor", INI::parseColorInt, 0, 0x8 },
	{ 0, 0, 0, 0 }
};
class Rva005E16A7
{
public:
	void rva005E16A7(INI *ini);
};

class Rva005E9F7B
{
public:
	virtual ~Rva005E9F7B();
	virtual void rva005E2126(INI *ini);
};
void Rva005E16A7::rva005E16A7(INI *ini)
{
	ini->initFromINI(this, g_rva005E16A7FieldParse);
}
void Rva005E9F7B::rva005E2126(INI *ini)
{
	ini->initFromINI(this, g_rva005E2126FieldParse);
}

// 0x005F84F7: clears entry i (8 bytes each) of the +0x20 vector through the
// rowed 0x002BED91 when i is in range.
// 0x00604A1E: creates the named directory (kernel32 CreateDirectoryW, no
// security attributes) unless the name is NULL or empty.
// 0x00740A96: the rowed 0x007401A3 setter on the +0x20 member with the first
// argument and the rowed 0x00740A60 lookup of the second.
template <class T> class StringBase;
Int Rva00740A60Get(const StringBase<char> &name);
