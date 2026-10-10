// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x00355BDA (85 bytes): destroys ArmorTemplateMap members at +0x24/+0x10
// via rowed 0x00355257, restores the Snapshot vptr, then calls the rowed
// SubsystemInterface destructor at 0x001B4E74.

#include "Common/Snapshot.h"

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_pad04[4];
	int m_member08;
};

class ArmorTemplateMap
{
public:
	ArmorTemplateMap();
	~ArmorTemplateMap();

private:
	char m_pad[0x14];
};

class __declspec(novtable) Rva00355BDA : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva00355BDA();

private:
	ArmorTemplateMap m_map10;
	ArmorTemplateMap m_map24;
};

Rva00355BDA::~Rva00355BDA()
{
}
