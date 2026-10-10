// cl: /O1 /MD /EHsc
// ??1Rva004CE36@@UAE@XZ, retail 0x0004CE36..0x0004CE85 (79 bytes, EH): the
// destructor the rowed scalar deleting destructor ??_GRva004CE36 (0x0004CF47)
// and its -0xC thunk reach. It installs its own tables (0x00BC4C70 at +0,
// 0x00BC4C5C at +0xC), destroys its two 12-byte records at +0xAC through the
// eh vector destructor iterator with the rowed element cleanup 0x0004CDAF,
// and then runs the rowed base destructor 0x001F9D98 (the particle system
// manager's). The derived class and record identities are not established;
// the element destructor is a placeholder view pinned to 0x0004CDAF.

class Rva001F9D98Primary
{
public:
	virtual void s0();
private:
	int m_04;
	int m_08;
};

class Rva001F9D98Secondary
{
public:
	virtual void s0();
private:
	unsigned char m_pad04[0xAC - 0x0C - 4];
};

class Rva001F9D98 : public Rva001F9D98Primary, public Rva001F9D98Secondary
{
public:
	virtual ~Rva001F9D98();
};

struct Rva0004CDAFSlot
{
	~Rva0004CDAFSlot();
	unsigned char m_data[0x0C];
};

class Rva004CE36 : public Rva001F9D98
{
public:
	virtual ~Rva004CE36();
private:
	Rva0004CDAFSlot m_slots[2];	// +0xAC
};

Rva004CE36::~Rva004CE36()
{
}
