// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ??0UnitRevivalEntry@@QAE@XZ @0x0037E352 135B
// Default ctor over UnitRevivalEntry: zeros plus ones plus clear80 0x001EAE6F plus
// Rva004E04FD ctor plus float global 1.0f plus AsciiString null.
// Neighbours in Rva0037E270Lookup.cpp share /O1 /DNDEBUG /MD; /arch:SSE for
// retail xorps plus movss float zero and global float moves.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
class Xfer;

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
UnitRevivalEntry::UnitRevivalEntry()
    : m_00(0), m_04(0), m_08(0.0f), m_0C(1), m_10(1), m_14(),
      m_94(0), m_98(-1), m_9C(0), m_A0(false), m_A1(false),
      m_A4(0), m_A8(0), m_AC(0), m_B0(), m_C8(0), m_CC(1.0f),
      // Retail stores m_CC before initializing the final two words.
      m_D0((_ReadWriteBarrier(), 0)), m_str()
{
}
