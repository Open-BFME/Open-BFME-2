// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?GetStartPositionInfoForSlot@AptMapPreview@@QAEPAXH@Z @0x0057C71F 155B evidence: leaf 2 callers; callees rowed getConstSlot getMap findMap rva0043DA65 rva0020EAF6 rva004FCA5A; globals g_009FEF10 TheMapCache

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
class Rva0043DA65
{
public:
	int rva0043DA65();
};
class GameSlot
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
};
class GameInfo
{
public:
	const GameSlot *getConstSlot(int i) const;
	AsciiString getMap() const;
};
class Rva0020E89C;
class Rva00376A62;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int i);
};
class Rva004FCA5A
{
public:
	void *rva004FCA5A(const Rva00376A62 &x);

	char m_pad[0x20];
	int m_20;
};
struct MapEntry
{
	char data[0x14];
};
class MapMetaData
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	char m_24[0x30];
	MapEntry m_entries[1];
};
class MapCache
{
public:
	const MapMetaData *findMap(AsciiString s);
};
class Rva002BA8F1Logic;

extern MapCache *TheMapCache;
class Rva004FCA5AInner
{
public:
	char m_pad[0x1c];
	Rva004FCA5A *m_1c;
};
class Rva004FCA5AOuter
{
public:
	char m_pad[0x29c];
	Rva004FCA5AInner *m_29c;
};
class AptMapPreview
{
	char m_00[0x18];
	Rva0043DA65 *m_18;
	int m_1c;
	char m_20[0x48];
	Rva004FCA5AOuter *m_68;
public:
	void *GetStartPositionInfoForSlot(int slot);
	int rva0057C6C7();
};
void *AptMapPreview::GetStartPositionInfoForSlot(int slot)
{
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	if (info) {
		const GameSlot *gs = info->getConstSlot(slot);
		if (gs) {
			int v10 = gs->m_10;
			if (m_1c == 1) {
				if (v10 != -1) {
					Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
					Rva0020EAF6View *view = *(Rva0020EAF6View **)((char *)logic + 0xb0);
					Rva0020E89C *p = view->rva0020EAF6(v10);
					if (p) {
						Rva004FCA5AOuter *o = m_68;
						if (o) {
							Rva004FCA5A *s = o->m_29c->m_1c;
							if (s)
								return s->rva004FCA5A((const Rva00376A62 &)*p);
						}
					}
				}
			} else {
				const MapMetaData *md = TheMapCache->findMap(info->getMap());
				if (md) {
					if (v10 >= 0 && v10 < md->m_20)
						return (void *)&md->m_entries[v10];
				}
			}
		}
	}
	return 0;
}

// ?rva0057C6C7@AptMapPreview@@QAEHXZ @0x0057C6C7 88B: the start-position
// count the slot lookup above indexes: the living-world start-region set's
// +0x20 in mode 1, else the cached map's +0x20 (the bound the lookup
// checks). Caller 0x00440C66.
int AptMapPreview::rva0057C6C7()
{
	int mode = m_1c;
	GameInfo *info = (GameInfo *)m_18->rva0043DA65();
	if (!info)
		return 0;
	if (mode == 1) {
		Rva004FCA5AOuter *o = m_68;
		if (!o || !o->m_29c)
			return 0;
		Rva004FCA5A *s = o->m_29c->m_1c;
		if (!s)
			return 0;
		return s->m_20;
	}
	const MapMetaData *md = TheMapCache->findMap(info->getMap());
	if (!md)
		return 0;
	return md->m_20;
}
