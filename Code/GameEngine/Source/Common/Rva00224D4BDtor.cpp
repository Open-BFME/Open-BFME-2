// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva00224CDC@@UAE@XZ @0x00224D4B 53B
// Virtual dtor calling member at +0xC (rowed Rva002236B9 0x002236B9) then
// rowed base GameEngineDeletingBase 0x001B4E74. Chain from 0x002236B9.
// Evidence: lea ecx esi+0xC call 0x002236B9 then base call; __EH_prolog with
// and [ebp-4] 0 and or -1; caller deleting dtor 0x00224D2F. Novtable
// suppresses the vptr store retail omits; base padded to 0xC like the
// Rva004192D1 precedent.
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class Rva002236B9
{
public:
	~Rva002236B9();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class __declspec(novtable) Rva00224CDC : public GameEngineDeletingBase
{
public:
	virtual ~Rva00224CDC();
private:
	Rva002236B9 m_0C;
};

Rva00224CDC::~Rva00224CDC()
{
}
