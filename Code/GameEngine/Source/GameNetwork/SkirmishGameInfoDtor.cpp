// cl: /O1 /DNDEBUG /MD /EHsc
// ??1SkirmishGameInfo@@UAE@XZ retail 0x0022C516 69B
// Called by the scalar deleting dtor 0x0022C4FA (slot 0 of vtable 0x00BE7480).
// The eight 0x1AC-byte slot records at +0xDC run the vector dtor iterator with
// the rowed element dtor ??1BfmeSaveElement002295D7@@UAE@XZ (VA 0x006294FD),
// then the rowed base dtor ??1Rva00382FA7@@UAE@XZ 0x00400A7F. No own vtable
// store (novtable), as the retail SEH body shows.
class BfmeSaveElement002295D7
{
public:
	virtual ~BfmeSaveElement002295D7();
private:
	char m_pad04[0x1AC - 0x04];
};

class __declspec(novtable) Rva00382FA7
{
public:
	virtual ~Rva00382FA7();
private:
	char m_pad04[0xDC - 0x04];
};

class __declspec(novtable) SkirmishGameInfo : public Rva00382FA7
{
public:
	virtual ~SkirmishGameInfo();
private:
	BfmeSaveElement002295D7 m_slots[8]; // +0xDC
};

SkirmishGameInfo::~SkirmishGameInfo()
{
}
