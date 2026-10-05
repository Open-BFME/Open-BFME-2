// ?rva0039DB89@Team@@QAEXHPAPAVThingTemplate@@_NPAH1@Z
// partial score=0.98 date=2026-10-05
// ?rva0039DB89@Team@@QAEXHPAPAVThingTemplate@@_NPAH1@Z
// partial score=0.98 date=2026-10-03
// cl: /O1 /DNDEBUG /MD
// ?rva0039DB89@Team@@QAEXHPAPAVThingTemplate@@_NPAH1@Z, retail 0x0039DB89, 124 bytes.
// Team template-equivalence counter with status and flag checks via rowed
// iterate 0x263864 advance pin 0x263526 isEquivalentTo 0x33BB04 testStatus
// 0x4E536. Evidence: finish stash 0.96 callers 0x0039EC03 0x004F3EBF.

class Object;
class ThingTemplate;
enum ObjectStatusTypes
{
	STATUS_2 = 2
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1[0x438 - 0x08];
	unsigned char m_dead;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void rva0039DB89(int count, ThingTemplate **templates, bool flag1, int *counts, bool flag2);
};

// ?rva0039DB89@Team@@QAEXHPAPAVThingTemplate@@_NPAH1@Z present-unmatched
void Team::rva0039DB89(int count, ThingTemplate **templates, bool flag1, int *counts, bool flag2)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		const Object *obj = iter.cur();
		const ThingTemplate *tmpl = obj->m_template;
		for (int i = 0; i < count; i++) {
			if (!tmpl->isEquivalentTo(templates[i]))
				continue;
			if (flag1) {
				if ((obj->m_dead & 1) != 0)
					continue;
			}
			if (flag2) {
				if (obj->testStatus(STATUS_2))
					continue;
			}
			counts[i]++;
			break;
		}
	}
}
