// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /arch:SSE /G7
// ?rva0028D796@Rva0028D796@@QAEHXZ @0x0028D796 103B
// Evidence: leaf between Object::didExit 0x0028D757 and Object::isSelectable 0x0028D7FD;
// reads this+4 (template) and this+0x264 (tracker); template byte +0x113 bit 4 gate
// then ExperienceLevelStore::FindExperienceLevelList 0x00288C34 via global TheExperienceLevelSystem
// plus Rva00288940Find 0x00288940 stdcall with dead ECX (union trick from
// ExperienceLevelSystem.cpp) plus float (B/C)*A+A via __ftol2; callers unclaimed
// so honest address name Rva0028D796.

typedef int Int;

class ThingTemplate
{
public:
	unsigned char m_pad[0x113];
	unsigned char m_byte113; // +0x113
	unsigned char m_pad114[0x570 - 0x114];
	Int m_570; // +0x570
};

class ExperienceTracker
{
public:
	unsigned char m_pad00[0x24];
	Int m_24; // +0x24
};

class ExperienceLevelList;

class ExperienceLevelStore
{
public:
	ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;
};

class Rva00288CFA : public ExperienceLevelStore
{
};

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

extern const void *__stdcall Rva00288940Find(const void *arg);

union Rva00288940Call
{
	const void *(__stdcall *freeCall)(const void *);
	const void *(Rva00288CFA::*memberCall)(const void *);
};

class Rva0028D796
{
public:
	Int rva0028D796();
private:
	char m_pad00[4];
	ThingTemplate *m_template; // +0x04
	char m_pad08[0x264 - 0x08];
	ExperienceTracker *m_tracker; // +0x264
};

Int Rva0028D796::rva0028D796()
{
	ThingTemplate *tmpl = m_template;
	Int base = tmpl->m_570;
	if ((tmpl->m_byte113 & 4) != 0) {
		ExperienceLevelList *list = reinterpret_cast<Rva00288CFA *>(TheExperienceLevelSystem)->FindExperienceLevelList(m_tracker);
		if (list != 0) {
			Rva00288940Call find;
			find.freeCall = Rva00288940Find;
			const void *found = (reinterpret_cast<Rva00288CFA *>(TheExperienceLevelSystem)->*find.memberCall)(list);
			if (found != 0) {
				Int b = m_tracker->m_24;
				Int c = *(const Int *)((const char *)found + 0xFC);
				double db = (double)b;
				double da = (double)base;
				double f = db / c;
				f *= da;
				f += da;
				return (Int)f;
			}
		}
	}
	return base;
}
