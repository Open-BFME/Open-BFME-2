// ?rva0057CB7D@Rva0057E3DB@@QAE_NH@Z
// partial score=0.82 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX-
// ?rva0057CB7D@Rva0057E3DB@@QAE_NH@Z @0x0057CB7D 152B
// Evidence: pin; mode at this+0x1c selects LivingWorld 0x0020EAF6 plus rowed
// 36B 0x0057C525 filter and +0x1a2 gate vs map playerCount +0x20 via rowed
// getMap 0x0023E943 and findMap 0x003024BC; caller 0x0043DCFD.
#include "ascii_string.h"

class Rva0043DA65
{
public:
	int rva0043DA65();
};

class GameInfo
{
public:
	AsciiString getMap() const;
};

class MapMetaData
{
public:
	unsigned char m_pad[0x20];
	int m_playerCount;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class Rva0020E89C
{
public:
	unsigned char m_pad[0x1a2];
	bool m_1a2;
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

class LivingWorldLogic
{
public:
	unsigned char m_pad[0xb0];
	Rva0020EAF6View *m_ptrB0;
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004FD6F9;

class Rva0057C525
{
public:
	bool rva0057C525(const Rva004FD6F9 &o);
};

class Rva0057E3DB
{
public:
	bool rva0057CB7D(int index);
private:
	unsigned char m_pad00[0x18];
	Rva0043DA65 *m_ptr18;
	int m_mode1c;
	unsigned char m_pad20[0x68 - 0x20];
	void *m_ptr68;
};

bool Rva0057E3DB::rva0057CB7D(int index)
{
	GameInfo *info = (GameInfo *)m_ptr18->rva0043DA65();
	int mode = m_mode1c;
	if (mode == 1)
	{
		if (index == -1)
			return false;
		Rva0020EAF6View *view = TheLivingWorldLogic->m_ptrB0;
		if (!view)
			return false;
		Rva0020E89C *entry = view->rva0020EAF6(index);
		if (!entry)
			return false;
		if (!((Rva0057C525 *)this)->rva0057C525((const Rva004FD6F9 &)*(const Rva004FD6F9 *)entry))
			return false;
		if (!entry->m_1a2)
			return false;
		return true;
	}
	else if (mode == 0)
	{
		if ((unsigned int)index > 8)
			return false;
		AsciiString map = info->getMap();
		const MapMetaData *md = TheMapCache->findMap(map);
		if (!md)
			return false;
		return index < md->m_playerCount;
	}
	return false;
}
