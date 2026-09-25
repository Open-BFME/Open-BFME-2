// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1Rva0017FB94@@UAE@XZ @ 0x0017FB94 (89 bytes). HTree prototype dtor,
// twin of the HAnim Rva0014CD63 dtor at 0x0014CD63: stores vtable 0x00BD4F10,
// deletes the +0x14 HTree link (explicit ~HTreeClass via the 0x001667E0 row
// plus operator delete via the 0x0002FD60 row), tears down the +0x18
// StringClass via the 0x00610A40 pin, then delegates to the 0x0061ED80
// base pin. Unlike the HAnim twin (refcounted tree link), the HTree link is
// a plain owned pointer.

class HTreeClass
{
public:
	~HTreeClass();
};

class StringClass
{
public:
	~StringClass();
};

class Rva0061ED80
{
public:
	virtual ~Rva0061ED80();
};

class Rva0017FB94 : public Rva0061ED80
{
public:
	virtual ~Rva0017FB94();

	char m_pad04[0x10]; // +0x04..+0x13, untouched by this body
	HTreeClass *m_tree; // +0x14
	StringClass m_name; // +0x18
};

// ??1Rva0017FB94@@UAE@XZ
Rva0017FB94::~Rva0017FB94()
{
	delete m_tree;
}
