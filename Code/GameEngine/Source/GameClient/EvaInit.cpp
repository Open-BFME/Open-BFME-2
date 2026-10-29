// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD
// stlport
// Eva::init, retail 0x001DF0F9 (171 bytes): ?init@Eva@@UAEXXZ
// Identity (target): WorldBuilder's debug Eva.cpp Eva::init loads the
// "Data\\INI\\Default\\Eva.ini" and "Data\\INI\\Eva.ini" literals through
// INI::loadFile, then calls three Eva member helpers (0x001DEF89,
// 0x001DE3E3, 0x001DEE92), as retail does.
// Donor (Zero Hour Eva::init): the two INI loads with INI_LOAD_OVERWRITE.
// BFME 2 deltas (target): afterwards the event table (0x30-byte records at
// +0x1C) is processed with the +0x28 member, the +0x34 member with the
// +0x48 member, and the +0x5C member is sized to the event count; the
// helpers' names are not recovered.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
	char m_storage[0x87C];
};

struct EvaEventRecord
{
	unsigned char m_bytes[0x30];
};

class Rva001DEF89Table
{
public:
	int size() const { return m_end - m_begin; }

private:
	EvaEventRecord *m_begin; // +0x00
	EvaEventRecord *m_end; // +0x04
	EvaEventRecord *m_capacityEnd; // +0x08
};

// Row spellings: 0x001DE3E3 is Rva001DE3E3::rva001DE3E3(Rva001DE3E3 *)
// returning this, and 0x001DEF89 is vector<Rva001DEF89Record>::operator=.
class Rva001DE3E3
{
public:
	Rva001DE3E3 *rva001DE3E3(Rva001DE3E3 *other);
};
struct Rva001DEF89Record;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	vector &operator=(const vector &other);
};
}
typedef _STL::vector<Rva001DEF89Record, _STL::allocator<Rva001DEF89Record> > Rva001DEF89Vector;

class Rva001DE3E3Member
{
};

class Rva001DEE92Member
{
public:
	void rva001DEE92(int count);
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Eva : public SubsystemInterface
{
public:
	// Slot 1 of retail's base table.
	virtual void init();

private:
	unsigned char m_pad0C[0x1C - 0x0C];
	Rva001DEF89Table m_events; // +0x1C
	unsigned char m_member28[0x34 - 0x28]; // +0x28
	Rva001DE3E3Member m_member34; // +0x34
	unsigned char m_pad35[0x48 - 0x35];
	unsigned char m_member48[0x5C - 0x48]; // +0x48
	Rva001DEE92Member m_member5C; // +0x5C
};

void Eva::init()
{
	INI ini;
	ini.loadFile("Data\\INI\\Default\\Eva.ini", INI_LOAD_OVERWRITE, 0);
	ini.loadFile("Data\\INI\\Eva.ini", INI_LOAD_OVERWRITE, 0);

	*(Rva001DEF89Vector *)&m_events = *(const Rva001DEF89Vector *)m_member28;
	Rva001DE3E3Member *member34 = &m_member34;
	((Rva001DE3E3 *)member34)->rva001DE3E3((Rva001DE3E3 *)m_member48);
	m_member5C.rva001DEE92(m_events.size());
}
