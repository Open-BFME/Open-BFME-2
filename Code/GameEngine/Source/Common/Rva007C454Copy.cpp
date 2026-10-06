// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva007C454@@QAE@ABV0@@Z @0x0007C404 80B: copy constructor of the
// CameraClass-derived Rva007C454 (rowed ctor 0x0007C3CD, deleting dtor
// 0x0007C5B9 with its -0x8 thunk 0x0007C3FC). Caller: its clone slot
// 0x0007C4C6 (call at 0x0007C4EE). It copies the base through the rowed
// CameraClass copy 0x00134C50, installs both vptrs (0x00BC6C58 at +0 and
// 0x00BC6C54 at +8, the secondary base the thunk proves) and copies the
// vector holder at +0x3FC through the rowed Rva005386F5 copy 0x005386F5.

class Rva007C454CameraBase0
{
public:
	virtual ~Rva007C454CameraBase0();
private:
	char m_unmodelled[0x4];
};

class Rva007C454CameraBase8
{
public:
	virtual ~Rva007C454CameraBase8();
};

class CameraClass : public Rva007C454CameraBase0, public Rva007C454CameraBase8
{
public:
	CameraClass(const CameraClass &src);
	virtual ~CameraClass();
private:
	char m_unmodelled[0x3FC - 0xC];
};

class Rva005386F5
{
public:
	Rva005386F5(const Rva005386F5 &other);
	~Rva005386F5();
private:
	char m_pad[0x10];
};

class Rva007C454 : public CameraClass
{
public:
	Rva007C454(const Rva007C454 &other);
	virtual ~Rva007C454();
private:
	Rva005386F5 m_3FC;
};

Rva007C454::Rva007C454(const Rva007C454 &other) :
	CameraClass(other),
	m_3FC(other.m_3FC)
{
}
