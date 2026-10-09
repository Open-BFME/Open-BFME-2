// cl: /O1 /DNDEBUG /MD
//
// ?rva002BB2B7@LivingWorldLogic@@QAEXPAVXfer@@@Z, retail 0x002BB2B7..0x002BB49C
// (485B), thiscall ret 4.
//
// The shared state block of LivingWorldLogic's two snapshot xfers (callers
// 0x002BB5FE in 0x002BB5DD and 0x002BBA7A in 0x002BBA45, both after their
// own xferVersion, with ecx = the logic and the stream pushed). Version 7:
// the region id at +0xB8 (rowed Rva003EFE82Get, "LivingWorldRegionID"); when
// not a CRC pass the flags +0xC8 / +0xE8 and from version 5 the int +0xE4,
// the flag +0x10A (cleared again on load) and the flags +0x176 / +0x177; the
// flag +0xE9; the game difficulty +0xEC (rowed XferGameDifficulty, not on CRC
// passes); from version 4 the words +0x100 / +0x104; from version 6 the flag
// +0x175 and from version 7 the flag +0x168 and the word +0x164 (both not on
// CRC passes); then the rowed XferPlayers, the owning army vector at +0x124
// (rowed XferOwningLivingWorldArmyVec), the two module vectors +0x10C /
// +0x118 (rowed rva002B8D06), the two ids +0xF4 / +0xF8 (rowed
// Rva002B2435Get), the flags +0x108 / +0x109 (not on CRC passes), the rowed
// XferDelayedRegionVictories and the rowed rva002B9CFC.
//
// Evidence (target): the callees above are read at the retail REL32s; the
// Xfer slots are +0x04 isLoading / +0x0C isCRC / +0x28 xferVersion / +0x78
// xferUnsignedInt / +0x7C xferInt / +0x90 xferBool. No WorldBuilder twin was
// found; the method and field names stay address-derived.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	unsigned char m_minVersion;
	unsigned char m_version;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();			// +0x04
	virtual void slot08();
	virtual Bool isCRC();				// +0x0C
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(XferVersion &version);	// +0x28
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void xferUnsignedInt(UnsignedInt &value);	// +0x78
	virtual void xferInt(Int &value);		// +0x7C
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(Bool &value);		// +0x90
};

class ModuleData;
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector;
}
typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > ModuleDataVector;

struct Rva003EFE82Obj;
struct Rva002B2435Obj;
class Other002B9CFC;

int __cdecl Rva003EFE82Get(Rva003EFE82Obj *obj, void *out);
int __cdecl Rva002B2435Get(Rva002B2435Obj *obj, void *out);
void __cdecl XferGameDifficulty(Xfer *xfer, int *difficulty);
void __cdecl XferOwningLivingWorldArmyVec(Xfer *xfer, ModuleDataVector *armies);

class Rva002BA8F1Logic
{
public:
	void rva002B8D06(Xfer *xfer, ModuleDataVector *modules);
};

class Rva002B9CFC
{
public:
	void rva002B9CFC(Other002B9CFC *xfer);
};

class LivingWorldLogic
{
public:
	void rva002BB2B7(Xfer *xfer);
	void XferDelayedRegionVictories(Xfer *xfer);
	void XferPlayers(Xfer *xfer);

private:
	unsigned char m_pad000[0xB8];
	Int m_regionB8;			// +0xB8
	unsigned char m_padBC[0xC8 - 0xBC];
	Bool m_flagC8;			// +0xC8
	unsigned char m_padC9[0xE4 - 0xC9];
	Int m_intE4;			// +0xE4
	Bool m_flagE8;			// +0xE8
	Bool m_flagE9;			// +0xE9
	unsigned char m_padEA[0xEC - 0xEA];
	int m_difficultyEC;		// +0xEC
	unsigned char m_padF0[0xF4 - 0xF0];
	Int m_idF4;			// +0xF4
	Int m_idF8;			// +0xF8
	unsigned char m_padFC[0x100 - 0xFC];
	UnsignedInt m_word100;		// +0x100
	UnsignedInt m_word104;		// +0x104
	Bool m_flag108;			// +0x108
	Bool m_flag109;			// +0x109
	Bool m_flag10A;			// +0x10A
	unsigned char m_pad10B;
	unsigned char m_modules10C[0x0C];	// +0x10C
	unsigned char m_modules118[0x0C];	// +0x118
	unsigned char m_armies124[0x0C];	// +0x124
	unsigned char m_pad130[0x164 - 0x130];
	UnsignedInt m_word164;		// +0x164
	Bool m_flag168;			// +0x168
	unsigned char m_pad169[0x175 - 0x169];
	Bool m_flag175;			// +0x175
	Bool m_flag176;			// +0x176
	Bool m_flag177;			// +0x177
};

void LivingWorldLogic::rva002BB2B7(Xfer *xfer)
{
	XferVersion version;
	version.m_minVersion = 1;
	version.m_version = 7;
	xfer->xferVersion(version);
	Rva003EFE82Get((Rva003EFE82Obj *)xfer, &m_regionB8);
	if (!xfer->isCRC())
	{
		xfer->xferBool(m_flagC8);
		xfer->xferBool(m_flagE8);
		if (version.m_version >= 5)
		{
			xfer->xferInt(m_intE4);
			xfer->xferBool(m_flag10A);
			if (xfer->isLoading())
				m_flag10A = false;
			xfer->xferBool(m_flag176);
			xfer->xferBool(m_flag177);
		}
	}
	xfer->xferBool(m_flagE9);
	if (!xfer->isCRC())
		XferGameDifficulty(xfer, &m_difficultyEC);
	if (version.m_version >= 4)
	{
		xfer->xferUnsignedInt(m_word100);
		xfer->xferUnsignedInt(m_word104);
	}
	if (version.m_version >= 6 && !xfer->isCRC())
		xfer->xferBool(m_flag175);
	if (version.m_version >= 7 && !xfer->isCRC())
	{
		xfer->xferBool(m_flag168);
		xfer->xferUnsignedInt(m_word164);
	}
	XferPlayers(xfer);
	XferOwningLivingWorldArmyVec(xfer, (ModuleDataVector *)m_armies124);
	((Rva002BA8F1Logic *)this)->rva002B8D06(xfer, (ModuleDataVector *)m_modules10C);
	((Rva002BA8F1Logic *)this)->rva002B8D06(xfer, (ModuleDataVector *)m_modules118);
	Rva002B2435Get((Rva002B2435Obj *)xfer, &m_idF4);
	Rva002B2435Get((Rva002B2435Obj *)xfer, &m_idF8);
	if (!xfer->isCRC())
	{
		xfer->xferBool(m_flag108);
		xfer->xferBool(m_flag109);
	}
	XferDelayedRegionVictories(xfer);
	((Rva002B9CFC *)this)->rva002B9CFC((Other002B9CFC *)xfer);
}
