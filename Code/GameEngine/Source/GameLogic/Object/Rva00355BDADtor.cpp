// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x00355BDA (85 bytes): destroys ArmorTemplateMap members at +0x24/+0x10
// via rowed 0x00355257, restores the Snapshot vptr, then calls the rowed
// GameEngineDeletingBase destructor at 0x001B4E74.

#include "Common/Snapshot.h"

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

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

class __declspec(novtable) Rva00355BDA : public GameEngineDeletingBase, public Snapshot
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
