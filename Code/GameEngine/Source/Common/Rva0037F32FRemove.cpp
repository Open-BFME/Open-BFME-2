// cl: /MD /Oi /O1 /arch:SSE /G7
// ?rva0037EEB9@Rva0037F32F@@QAEXPBVThingTemplate@@@Z @0x0037EEB9 67B.
// Removal twin of rva0037F32F: scan the 0xD8-stride array at this+4 for the
// element whose string at +0xD4 matches the ThingTemplate string at +0x64,
// then erase via rowed 0x002E204D. Same shape as UnitRevivalTracker::rva0037EF2D.
// Evidence: ret 4 const ThingTemplate* param; callers BuildableHeroListUpgrade
// 0x004B8484 via Rva0037F32F holder at Player+0x738; callees StringBase::compare
// 0x000069D6 and Rva002E204D::rva002E204D 0x002E204D; neighbours 0x0037EDE0 and
// 0x0037EEFC (ends exactly at next start).
template<class _T> class StringBase
{
public:
	char *m_text;
	int compare(const StringBase &other) const;
};
class ThingTemplate
{
	char m_pad00[0x64];
public:
	StringBase<char> m_str64;
};
class Rva002E0D93
{
public:
	char m_pad00[0xD4];
	StringBase<char> m_strD4;
};
class Rva002E204D
{
public:
	Rva002E0D93 *rva002E204D(Rva002E0D93 *pos);
	Rva002E0D93 *m_start00;
	Rva002E0D93 *m_finish04;
	Rva002E0D93 *m_end08;
};
class Rva0037F32F
{
	int m_unk00;
	Rva002E204D m_vec04;
public:
	void rva0037EEB9(const ThingTemplate *tmpl);
};
void Rva0037F32F::rva0037EEB9(const ThingTemplate *tmpl)
{
	for (Rva002E0D93 *p = m_vec04.m_start00; p != m_vec04.m_finish04; ++p) {
		if (p->m_strD4.compare(tmpl->m_str64) == 0) {
			m_vec04.rva002E204D(p);
			break;
		}
	}
}
