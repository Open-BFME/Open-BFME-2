// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??1DamageFieldUpdateModuleData@@UAE@XZ, retail 0x0049116A, 68 bytes.
// ModuleData dtor: tears down the RequiredUpgrade string at +0x18 through
// the folded 0x36410 body (AsciiString pin shares the address with the
// StringBase<char> pin retail calls, state 1), then the ObjectFilter at
// +0x14 through the opaque 0x360D26 pin (state 0), then the Rva0048BC03Base
// base through the rowed 0x48BC46 body. Empty derived body; novtable
// suppresses the derived store retail lacks (base call restores the base
// table). Layout from the rowed ctor 0x00491102 (base 0x10 plus Radius
// +0x10 plus filter +0x14 plus string +0x18). Caller is the slot-0 ??_G at
// 0x0049114E.

class Rva0048BC03Base
{
public:
	Rva0048BC03Base();
	virtual ~Rva0048BC03Base();

private:
	unsigned char m_pad[0x10 - 4];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	unsigned char m_data[4];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

class __declspec(novtable) DamageFieldUpdateModuleData : public Rva0048BC03Base
{
public:
	DamageFieldUpdateModuleData();
	virtual ~DamageFieldUpdateModuleData();

private:
	int m_radius; // +0x10
	Rva003623E5Member m_objectFilter; // +0x14
	AsciiString m_requiredUpgrade; // +0x18
};

DamageFieldUpdateModuleData::~DamageFieldUpdateModuleData()
{
}
