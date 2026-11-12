// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Existing registration constructors whose virtual-slot providers remain unresolved.
// Preserve their native evidence apart from the independent GapBodiesSeat5A routines.

// --- 0x005C43CF, 0x005C459E, 0x005C47F0 (24B each): derived constructors
// over the rowed registration base 0x0052B894 (name passed through), each
// then installing its own vtable (0x00C745A0, 0x00C74698, 0x00C7475C). Each
// table's slot 0 is the shared deleting destructor 0x005C43E7, as for
// Rva004FA623RegistrationCtor.cpp, so the views declare empty virtual dtors.
class AsciiString;
class Rva0052B668
{
public:
	Rva0052B668(const AsciiString &name);		// 0x0052B894
	// Empty: retail's 0x0052B588 only stores this class's vtable.
	virtual ~Rva0052B668() {}
	// Retail table 0x00C686BC holds __purecall at slot 1; each derived
	// registration table overrides it (0x00C63398's is 0x004FAC99).
	virtual void slot1() = 0;
};

#define SEAT5_REGISTRATION_CTOR(RVA) \
class Rva##RVA##Registration : public Rva0052B668 \
{ \
public: \
	Rva##RVA##Registration(const AsciiString &name); \
	virtual ~Rva##RVA##Registration() {} \
}; \
Rva##RVA##Registration::Rva##RVA##Registration(const AsciiString &name) \
	: Rva0052B668(name) \
{ \
}

SEAT5_REGISTRATION_CTOR(005C43CF)
SEAT5_REGISTRATION_CTOR(005C459E)
SEAT5_REGISTRATION_CTOR(005C47F0)
