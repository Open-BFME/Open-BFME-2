// cl: /O1 /MD /EHsc
// ??1Rva00A897D@@UAE@XZ, retail 0x000A897D..0x000A89C1 (68 bytes, EH).
// Destructor of the 0x5C-byte audio device the pinned constructor
// 0x000A8903 builds (its scalar deleting destructor 0x00051A2A and the
// device-reference assign 0x00053D66 call here). Retail stores no vptr, so
// the class is novtable over its base's table. Members die in reverse:
// the +0x38 handle through its rowed virtual destructor 0x00040FE5 called
// directly (EH state 1), the +0x30 owning holder through its rowed clear
// 0x000A8879 (state 0), then the rowed base destructor 0x0073F4F3.
// Identity stays address-derived (the pinned name); the constructor's
// separate address-derived spelling is not merged here.
#include "../../Include/Common/Rva00041004Lock.h"

class Rva0073F4F3
{
public:
	Rva0073F4F3(void *owner);
	virtual void slot0();
	~Rva0073F4F3();
private:
	char m_pad04[0x30 - 4];
};

class Rva0073EE55;

class Rva000A8879
{
public:
	Rva000A8879() : m_ptr(0) {}
	~Rva000A8879() { clear(); }
	void clear();
private:
	Rva0073EE55 *m_ptr;
};


class __declspec(novtable) Rva00A897D : public Rva0073F4F3
{
public:
	virtual ~Rva00A897D();
private:
	Rva000A8879 m_holder30;	// +0x30
	int m_driver34;		// +0x34
	Rva00041004 m_lock38;	// +0x38
};

Rva00A897D::~Rva00A897D()
{
}

// ??0Rva000A8903AudioDevice@@QAE@PAX@Z, retail 0x000A8903..0x000A897D (122
// bytes, EH, RET4): the constructor of the same 0x5C-byte device under its
// pinned address-derived spelling (called from openDevice). Base 0x0073F468
// with a null argument, an empty +0x30 holder, the driver argument at
// +0x34, the +0x38 lock with initial count 1, then a 16-byte worker built
// by 0x000A8893 (byte copy of the rowed Rva0073F708 constructor) with
// (this, 3) handed to the holder through rowed 0x000A8856.
class Rva000A8903AudioDevice;

class Rva000A8856
{
public:
	void rva000A8856(Rva000A8903AudioDevice *worker);
};

class Rva000A8893Worker
{
public:
	Rva000A8893Worker(void *device, int kind);
private:
	char m_data[0x10];
};

class __declspec(novtable) Rva000A8903AudioDevice : public Rva0073F4F3
{
public:
	Rva000A8903AudioDevice(void *driver);
	virtual ~Rva000A8903AudioDevice();
private:
	Rva000A8879 m_holder30;	// +0x30
	void *m_driver34;	// +0x34
	Rva00041004 m_lock38;	// +0x38
};

Rva000A8903AudioDevice::Rva000A8903AudioDevice(void *driver)
	: Rva0073F4F3(0), m_driver34(driver), m_lock38(1)
{
	reinterpret_cast<Rva000A8856 *>(&m_holder30)->rva000A8856(
		reinterpret_cast<Rva000A8903AudioDevice *>(new Rva000A8893Worker(this, 3)));
}
