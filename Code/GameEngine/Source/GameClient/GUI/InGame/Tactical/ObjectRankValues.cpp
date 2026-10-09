// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ComputeObjectRankValues  ?ComputeObjectRankValues@@YA_NABVObject@@AAHAAM@Z
// retail 0x005C3000..0x005C3180 (384B)  WorldBuilder twin 0x01557070 (846B)
// named by its ObjectRank.cpp assert `obj.getExperienceTracker() != NULL`.
//
// Reads the object's experience-level handle (ExperienceTracker 0x0039AC0C on
// Object +0x264) and returns false when the level store reports it invalid.
// Otherwise stores the level rank and computes the progress toward the next
// level: (current experience - this level's requirement) / (next level's
// requirement - this level's requirement) clamped to [0 1] or -1 when there
// is no next level / the tracker cannot gain / the rank is at the cap.
// Returns rank > 1 or progress >= 0.
//
// Target facts: callers 0x005264F5 and 0x00528CEB push (obj &rank &progress)
// and test al; the store is the global at 0x00DFECC4; callee rows
// IsValid (pin 0x0028891F) GetLevelRank 0x0028879C GetNextLevel 0x00288ABC
// GetRequiredExperience 0x002887B8 and tracker rows 0x0039ABFF 0x005CB9FF.
// The tracker's current experience is the float at +0x10.
// Reference vs pointer parameters follow the WB assert text (obj.); the out
// parameters' spelling is a structural inference.

typedef int Int;
typedef float Real;

struct ExperienceLevelNode;
class ExperienceLevelList;

struct ExperienceLevelIterator
{
	ExperienceLevelNode *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceLevelStore
{
public:
	// The store is the global at 0x00DFECC4 (pinned TheExperienceLevelSystem).
	static ExperienceLevelStore *get() { return reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem); }

	bool IsValid(ExperienceLevelHandle handle) const;
	Int GetLevelRank(ExperienceLevelHandle handle) const;
	ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle handle) const;
	Int GetRequiredExperience(ExperienceLevelHandle handle) const;
};

class Rva005CB9FF
{
public:
	bool rva005CB9FF(Int arg);
};

class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
	bool rva0039ABFF() const;
	bool getLevelCap(Int *cap) const { return reinterpret_cast<Rva005CB9FF *>(const_cast<ExperienceTracker *>(this))->rva005CB9FF(reinterpret_cast<Int>(cap)); }
	Real getCurrentExperience() const { return m_currentExperience; }

private:
	unsigned char m_pad00[0x10];
	Real m_currentExperience;	// +0x10
};

class Object
{
public:
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }

private:
	unsigned char m_pad00[0x264];
	ExperienceTracker *m_experienceTracker;	// +0x264
};

bool ComputeObjectRankValues(const Object &obj, Int &rank, Real &progress)
{
	ExperienceLevelHandle handle = obj.getExperienceTracker()->rva0039AC0C();
	if (!ExperienceLevelStore::get()->IsValid(handle))
		return false;

	rank = ExperienceLevelStore::get()->GetLevelRank(handle);
	ExperienceLevelHandle next = ExperienceLevelStore::get()->GetNextLevel(handle);
	if (ExperienceLevelStore::get()->IsValid(next) && obj.getExperienceTracker()->rva0039ABFF()) {
		Int cap;
		if (!obj.getExperienceTracker()->getLevelCap(&cap) || rank < cap) {
			Real current = obj.getExperienceTracker()->getCurrentExperience();
			Real lower = (Real)ExperienceLevelStore::get()->GetRequiredExperience(handle);
			Real upper = (Real)ExperienceLevelStore::get()->GetRequiredExperience(next);
			if (lower < upper) {
				progress = (current - lower) / (upper - lower);
				if (progress < 0.0f)
					progress = 0.0f;
				else if (progress > 1.0f)
					progress = 1.0f;
			} else {
				progress = -1.0f;
			}
		} else {
			progress = -1.0f;
		}
	} else {
		progress = -1.0f;
	}

	return rank > 1 || progress >= 0.0f;
}
