// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /O1 /Ob1 /EHsc /DNDEBUG /MD /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0037F2C0@Rva0037F2C0@@QAEHPAVObject@@_N@Z @0x0037F2C0 111B via UnitRevivalTracker vector at +4, UnitRevivalEntry from Object, size-1 return
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"

class Xfer;

class Rva001EAE6FHelper
{
	char m_data[0x80];
public:
	Rva001EAE6FHelper *clear80() throw();
	// Keep the existing clear worker while constructing this member in order.
	__forceinline Rva001EAE6FHelper() throw() { clear80(); }
};
class Rva004E04FD
{
	char m_data[0x18];
public:
	Rva004E04FD() throw();
};
class Object;

class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(Object *object);
	UnitRevivalEntry(const UnitRevivalEntry &that);
	~UnitRevivalEntry();
	UnitRevivalEntry &operator=(const UnitRevivalEntry &that);
	void *getThingTemplate();
	void setThingTemplateName(const AsciiString &name);
	void rva0037E473(Xfer *xfer);

	int m_00;
	int m_04;
	float m_08;
	int m_0C;
	int m_10;
	Rva001EAE6FHelper m_14;
	int m_94;
	int m_98;
	unsigned int m_9C; // build time, from the template's float via _ftol
	bool m_A0;
	bool m_A1;
	int m_A4;
	int m_A8;
	int m_AC;
	Rva004E04FD m_B0;
	int m_C8;
	float m_CC;
	int m_D0;
	AsciiString m_str; // +0xD4
};

class Rva0037F2C0
{
public:
	int rva0037F2C0(Object *object, bool flag);
private:
	int m_00;
	_STL::vector<UnitRevivalEntry> m_vec;
};

int Rva0037F2C0::rva0037F2C0(Object *object, bool flag)
{
	UnitRevivalEntry entry(object);
	if (flag)
		entry.m_94 = 0;
	m_vec.push_back(entry);
	int count = (int)m_vec.size() - 1;
	return count;
}
