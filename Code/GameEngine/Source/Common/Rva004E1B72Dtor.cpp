// cl: /O1 /DNDEBUG /MD /EHsc
// Destructor and scalar deleting destructor of an unidentified class with
// vtable 0x00C61DC4: one string member at +4, then an empty base whose vtable
// is 0x00BBB554. These bodies were first claimed as AttackNugget's, but the
// real AttackNugget (built by AttackNugget::parse) uses vtable 0x00BE0FF4 and
// a different member, so the class stays address-named until identified.

// Fold-shared string member teardown (never defined; resolves through the
// symbols.csv pin at 0x00036410).
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class Rva004E1B72Base
{
public:
	virtual ~Rva004E1B72Base() {}
};

class Rva004E1B72 : public Rva004E1B72Base
{
public:
	virtual ~Rva004E1B72();

	AsciiStringMember m_member04;
};

Rva004E1B72::~Rva004E1B72()
{
}
