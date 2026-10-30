// cl: /MD /Oi /O1 /arch:SSE /G7
// ?removeBuildUnit@UnitRevivalTracker@@QAEXPBVThingTemplate@@@Z @0x0037EEB9 67B.
// WorldBuilder UnitRevivalTracker.cpp:548 names it UnitRevivalTracker::removeBuildUnit.
// Removal twin of addInitialBuildUnit: scan the 0xD8-stride array at this+4 for the
// element whose string at +0xD4 matches the ThingTemplate string at +0x64,
// then erase via rowed 0x002E204D. Same shape as UnitRevivalTracker::rva0037EF2D.
// Evidence: ret 4 const ThingTemplate* param; callers BuildableHeroListUpgrade
// 0x004B8484 via the UnitRevivalTracker at Player+0x738; callees StringBase::compare
// 0x000069D6 and Rva002E204D::rva002E204D 0x002E204D; neighbours 0x0037EDE0 and
// 0x0037EEFC (ends exactly at next start).
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class ThingTemplate
{
public:
	char unknown00[0x64];
	AsciiString name; // +0x64
};
class Rva002E0D93
{
public:
	char m_pad00[0xA4];
	int m_keyA4;
	char m_padA8[0xD4 - 0xA8];
	AsciiString m_strD4;
};
class Rva002E204D
{
public:
	Rva002E0D93 *rva002E204D(Rva002E0D93 *pos);
	Rva002E0D93 *m_start00;
	Rva002E0D93 *m_finish04;
	Rva002E0D93 *m_end08;
};
class UnitRevivalTracker
{
public:
	void removeBuildUnit(const ThingTemplate *tmpl);

private:
	int m_vtable00;
	Rva002E204D m_entries;
};
void UnitRevivalTracker::removeBuildUnit(const ThingTemplate *thingTemplate)
{
	for (Rva002E0D93 *p = ((Rva002E204D *)&m_entries)->m_start00; p != ((Rva002E204D *)&m_entries)->m_finish04; ++p) {
		if (p->m_strD4.compare(thingTemplate->name) == 0) {
			((Rva002E204D *)&m_entries)->rva002E204D(p);
			break;
		}
	}
}
