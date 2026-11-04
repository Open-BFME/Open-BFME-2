// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/shims/stringinline
// ??1Rva000E9BAC@@UAE@XZ @0x000E9BAC 99B: virtual dtor with array plus member plus base.
// Evidence: vptr g_00BCECB8 Reset row 0xE7016 array 0x40x0x5C dtor 0x4E86B8 member 0x8B470 base pin 0xE6C6F; caller deleting dtor.

class W3DShrubBuffer
{
public:
	void rva000E7016();
};

class Rva000E86B8
{
public:
	~Rva000E86B8();
	char m_pad[0x5C];
};

class Rva0008B470
{
public:
	~Rva0008B470();
	char m_pad[0x10];
};

// The base destructor 0x000E6C6F is the rowed ??1Rva000E6AC0@@UAE@XZ
// (Rva000E6AC0Ctor.cpp). The derived vtable holds only the deleting dtor,
// as OpaqueScalarDeletingDtorsB01.cpp's view of it.
class Rva000E6AC0
{
public:
	virtual ~Rva000E6AC0();
};

extern const void *const g_00BCECB8[];

class Rva000E9BAC : public Rva000E6AC0
{
public:
	virtual ~Rva000E9BAC();
private:
	char m_pad00[0x4FB60 - 4];
	Rva0008B470 m_4FB60;
	Rva000E86B8 m_4FB70[0x40];
};

Rva000E9BAC::~Rva000E9BAC()
{
	((W3DShrubBuffer *)this)->rva000E7016();
}
