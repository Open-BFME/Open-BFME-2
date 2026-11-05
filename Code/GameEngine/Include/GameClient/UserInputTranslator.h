// Target facts (RVAs except explicit VAs): constructor 0x005748A4 stores VA 0x00C6E430 and returns this; derived constructors 0x0057621A (store 0x0057622D), 0x00576DF1 (0x00576E04) and 0x005776A7 install that table before their own. Their next independent subobject starts at +4: UserInputTranslator occupies four bytes, its sole storage the primary vptr at +0. No virtual bases or additional data are observed.
// Target facts: VA 0x00C6E430 has 26 slots, ending at the independent table VA 0x00C6E498: slot 0 is translateGameMessage 0x005CBC95, slot 1 is deleting destructor 0x004296EE, slots 2 and 18..25 are 0x005748B2 (zero; ret 8), and slots 3..17 are 0x005748AD (zero; ret 12). Destructor 0x00429191 stores VA 0x00BDBA74, the two-slot base table [__purecall 0x0003B810, deleting destructor 0x001DB080]. Base0_00576C4B's rowed constructor 0x001DB0AC stores this base table. The destructor's final base lifetime differs from the constructor's 26-slot lifetime. Structural inference: the destructor is the empty inline one (its own-table store is dead before the base's), so the 7-byte 0x00429191 body is a COMDAT each including unit emits; the derived destructors in Rva00576C4BDtor.cpp and Rva00575F38Dtor.cpp byte-match only with it inline.
// Target facts: translateGameMessage 0x005CBC95 dispatches through +0x08..+0x64 and returns each result; pixel arguments are copied into eight-byte temporaries and passed by reference, region arguments by reference, remaining arguments as dwords. The existing Rva005CBC95Pixel spelling denotes that argument view. Slots 6/11/15 take two pixel references and one integer; slots 3..5/7..10/12..14/16..17 take one pixel reference and two integers; slot 2 takes one pixel reference and one integer; slots 18..23 take a region reference and one integer; slots 24/25 take two integers. Slot 18 is OnMouseLeftClick by the ledger rows at 0x00576946 and 0x005777A0 and their respective derived tables VA 0x00C6E7F0 and VA 0x00C6E980. Other handler names are neutral slot indices; signedness of the integer arguments is not distinguished by these bytes.

#pragma once

#ifndef CANONICAL_USERINPUTTRANSLATOR_H
#define CANONICAL_USERINPUTTRANSLATOR_H

enum GameMessageDisposition;
class GameMessage;
struct IRegion2D;
struct Rva005CBC95Pixel;

class Base0_00576C4B
{
public:
	Base0_00576C4B() {}
	virtual GameMessageDisposition translateGameMessage(const GameMessage *) = 0;
	virtual ~Base0_00576C4B() {}
};

class UserInputTranslator : public Base0_00576C4B
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual ~UserInputTranslator() {}
	virtual int slot02(const Rva005CBC95Pixel &, int) { return 0; }
	virtual int slot03(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot04(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot05(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot06(const Rva005CBC95Pixel &, const Rva005CBC95Pixel &, int) { return 0; }
	virtual int slot07(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot08(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot09(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot10(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot11(const Rva005CBC95Pixel &, const Rva005CBC95Pixel &, int) { return 0; }
	virtual int slot12(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot13(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot14(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot15(const Rva005CBC95Pixel &, const Rva005CBC95Pixel &, int) { return 0; }
	virtual int slot16(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int slot17(const Rva005CBC95Pixel &, int, int) { return 0; }
	virtual int OnMouseLeftClick(const IRegion2D &, int) { return 0; }
	virtual int slot19(const IRegion2D &, int) { return 0; }
	virtual int slot20(const IRegion2D &, int) { return 0; }
	virtual int slot21(const IRegion2D &, int) { return 0; }
	virtual int slot22(const IRegion2D &, int) { return 0; }
	virtual int slot23(const IRegion2D &, int) { return 0; }
	virtual int slot24(int, int) { return 0; }
	virtual int slot25(int, int) { return 0; }
};

typedef char UserInputTranslatorSizeIs4[sizeof(UserInputTranslator) == 4 ? 1 : -1];

#endif
