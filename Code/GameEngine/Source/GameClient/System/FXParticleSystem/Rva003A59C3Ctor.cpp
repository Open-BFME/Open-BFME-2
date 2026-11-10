// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva003A59C3@@QAE@IAAURva003A59C3Src@@@Z, retail 0x003A59C3, 127 bytes,
// EH thiscall RET 8.
// Identified by the rowed module factory 0x003AD03B (Rva003AC9AFCreate.cpp),
// the rowed base ctor 0x0055EFE1 and the copy ctor 0x003AE03D: the complete
// class has vfptrs at +0 and +8 (the Rva0055EFE1 base object, 12 bytes) plus
// a second base at +0x0C whose transient vtable is 0x00C1B568, i.e. the rowed
// Rva003AE07D (default ctor 0x003A5773, Real at +4). The class then installs
// 0x00C1B5E0 (+0), 0x00C1C780 (+8) and 0x00C1B5D0 (+0x0C). The second ctor
// argument is unread; the factory passes its template there by reference, as
// the sibling factories do for their module ctors (0x0055F840, 0x0056413D).
// Class and method names remain address-derived.
//
// The Rva0055EFE1 base is modelled as an MI pair so the +8 secondary vfptr
// exists in this TU; its out-of-line ctor at 0x0055EFE1 owns the construction
// stores. Both destructible bases arm retail's EH state stores: state 0 is
// zeroed before the +0x0C base's vptr store, and state 1 is set before the
// random-value call whose result is assigned to the base's Real.

float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

class Xfer;
struct Rva003A59C3Src;

// The module base's primary table (0x00C1D2C0) is four slots: the deleting
// destructor and three __purecall words. Slot 1 is the per-frame update this
// class overrides (0x003A5A58) and slot 2 stays pure in this class; the
// factory's derived class fills it with its clone (0x003ADFFA in table
// 0x00C1CED8). Slot 3 is DoXfer(Xfer &), which this class overrides at
// 0x003A57A9; that row is still spelled under another placeholder class, so
// the slot keeps an inline stand-in here until it moves.
class Rva003A59C3B0A
{
public:
	virtual ~Rva003A59C3B0A() {}
	virtual void update() = 0;
	virtual void *clone() const = 0;
	virtual void DoXfer(Xfer &) {}

private:
	int m_4;
};

// The +8 table (0x00C1C780) is a single __purecall word.
class Rva003A59C3B0B
{
public:
	virtual void s0() = 0;
};

class Rva0055EFE1 : public Rva003A59C3B0A, public Rva003A59C3B0B
{
public:
	Rva0055EFE1(unsigned int arg);
};

// Same shape as the rowed Rva003AE07D (V3PolyCopyCtors.cpp): vtable
// 0x00C1B568 and a Real at +4 zeroed by the default ctor. Retail's table is
// four slots (destructor, LoadPostProcess, GetSnapshotName, DoXfer).
extern "C" const void *const __identifier("??_7Snapshot@@6B@")[];

class Rva003A59C3B3
{
public:
	Rva003A59C3B3() : m_real04(0.0f) {}
	// Retail destroys this subobject through 0x0049B47C (vtable slot 0 and the
	// ctor unwind): the folded Snapshot destructor, restore 0x00BBB554, return.
	virtual ~Rva003A59C3B3() { *(const void *const **)this = __identifier("??_7Snapshot@@6B@"); }
	virtual void s0() {}
	virtual void s1() {}
	virtual void s2(Xfer &) {}

	float m_real04;
};

// Retail's primary table 0x00C1B5E0: deleting destructor 0x003AE270, update
// 0x003A5A58, __purecall, DoXfer 0x003A57A9.
class Rva003A59C3 : public Rva0055EFE1, public Rva003A59C3B3
{
public:
	Rva003A59C3(unsigned int arg, Rva003A59C3Src &src);
	virtual void update();
};

Rva003A59C3::Rva003A59C3(unsigned int arg, Rva003A59C3Src &)
	: Rva0055EFE1(arg)
{
	m_real04 = GetGameClientRandomValueReal(
		0.7f, 1.3f,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpswindmodule.cpp",
		404);
}
