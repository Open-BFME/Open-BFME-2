// cl: /O1 /MD /EHsc
// ??1Rva004CE36@@UAE@XZ, retail 0x0004CE36..0x0004CE85 (79 bytes, EH): the
// destructor the rowed scalar deleting destructor ??_GRva004CE36 (0x0004CF47)
// and its -0xC thunk reach. It installs its own tables (0x00BC4C70 at +0,
// 0x00BC4C5C at +0xC), destroys its two 12-byte records at +0xAC through the
// eh vector destructor iterator with the rowed element cleanup 0x0004CDAF,
// and then runs the rowed base destructor 0x001F9D98 (the particle system
// manager's). The derived class and record identities are not established;
// the element is a neutral 12-byte vector-header view.

class Rva001F9D98Primary
{
public:
	virtual ~Rva001F9D98Primary();
private:
	int m_04;
	int m_08;
};

class Rva001F9D98Secondary
{
public:
	virtual ~Rva001F9D98Secondary();
protected:
	unsigned char m_pad04[0x5C - 0x0C - 4];
	int m_5C;	// +0x5C
	unsigned char m_pad60[0xA8 - 0x60];
	bool m_A8;	// +0xA8
	unsigned char m_padA9[3];
};

class Rva001F9D98 : public Rva001F9D98Primary, public Rva001F9D98Secondary
{
public:
	Rva001F9D98();
	virtual ~Rva001F9D98();
};

struct Rva0004CDAFSlot
{
	Rva0004CDAFSlot();
	~Rva0004CDAFSlot();
	unsigned char m_data[0x0C];
};

// Native array construction passes the default-vector closure at 256646;
// native array cleanup passes the complete destroy/deallocate operation at
// 4CDAF. Both take only ECX. Bind the existing operations without assigning
// an application identity to the vector's element type.
#pragma comment(linker, "/alternatename:??0Rva0004CDAFSlot@@QAE@XZ=??_F?$vector@PBVObjectCreationList@@V?$allocator@PBVObjectCreationList@@@_STL@@@_STL@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva0004CDAFSlot@@QAE@XZ=?_M_clear@?$vector@VRvaSmartPtr12@@V?$allocator@VRvaSmartPtr12@@@_STL@@@_STL@@IAEXXZ")

class Rva004CE36 : public Rva001F9D98
{
public:
	Rva004CE36();
	virtual ~Rva004CE36();
private:
	Rva0004CDAFSlot m_slots[2];	// +0xAC
};

Rva004CE36::~Rva004CE36()
{
}

// ??0Rva004CE36@@QAE@XZ, retail 0x0004CDCD..0x0004CE28 (91 bytes, EH): the
// matching constructor. It runs the unrowed base constructor 0x001FA69F
// (address-named view of the 0x001F9D98 base, pinned there), installs the
// same two tables, builds the two +0xAC records through the eh vector
// constructor iterator (element ctor 0x00256646, cleanup 0x0004CDAF, both
// pushed as addresses) and clears the base's +0x5C word and +0xA8 flag.
Rva004CE36::Rva004CE36()
{
	m_5C = 0;
	m_A8 = false;
}
