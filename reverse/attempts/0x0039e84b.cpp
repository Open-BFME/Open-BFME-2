// ?rva0039E84B@Team@@QAEMPAVObject@@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva0039E84B@Team@@QAEMPAVObject@@@Z @0x0039E84B 160B chain via rowed 0x002627E8 plus iterate 0x00263864 plus advance 0x00263526 prev 0x0039E815 next 0x0039E8EB
class Object;
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
class Rva002627E8 {
public:
	float rva002627E8() const;
};
class ObjectWithRange {
public:
	char m_pad[0x258];
	Rva002627E8 *m_range;
};
extern const float g_00C1ADB8;
extern "C" const float length_estimate_factor;
class Team {
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	float rva0039E84B(Object *obj);
};
// ?rva0039E84B@Team@@QAEMPAVObject@@@Z present-unmatched
float Team::rva0039E84B(Object *obj)
{
	Rva002627E8 *p = ((ObjectWithRange *)obj)->m_range;
	float f = g_00C1ADB8;
	if (p != 0)
		f = p->rva002627E8();
	float best = f;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		Rva002627E8 *rp = ((ObjectWithRange *)cur)->m_range;
		if (rp == 0)
			continue;
		if (best < rp->rva002627E8())
			best = rp->rva002627E8();
	}
	float scaled = length_estimate_factor * f;
	if (scaled > best)
		return scaled;
	return best;
}
