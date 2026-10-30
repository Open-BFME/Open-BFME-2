// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?getThingTemplate@UnitRevivalEntry@@QAEPAXXZ retail 0x0037E270 25 bytes.
// Null-checked global lookup via 0x00DFF000 plus AsciiString at +0xd4.
// Returns 0 when global null else rowed 0x002D06CA result. Callers
// 0x002E1A25 0x0037E3F6 0x0037E7B4 0x0037E93E 0x0037EB8C 0x0037EFB9
// 0x004067DD. Flags from sibling Rva002D06CAGet without EHsc.
#include "ascii_string.h"
class ThingTemplate;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &key); };
extern ThingFactory *TheThingFactory;
#define TheRva00DFF000 TheThingFactory
struct Rva0037E3D9Def
{
	char m_pad00[0x4DC];
	float m_buildTime;
	char m_pad4E0[0x5DA - 0x4E0];
	unsigned short m_buildCost;
};
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
void *UnitRevivalEntry::getThingTemplate()
{
    ThingFactory *mgr = TheRva00DFF000;
    if (mgr == 0)
        return 0;
    return (void *)mgr->findTemplate(*((const AsciiString *)((char *)this + 0xd4)));
}
void UnitRevivalEntry::setThingTemplateName(const AsciiString &asciiString)
{
    m_str = asciiString;
    if (m_A0)
        return;
    void *def = getThingTemplate();
    if (!def)
        return;
    m_94 = ((Rva0037E3D9Def *)def)->m_buildCost;
    m_9C = (unsigned int)((Rva0037E3D9Def *)def)->m_buildTime;
}
