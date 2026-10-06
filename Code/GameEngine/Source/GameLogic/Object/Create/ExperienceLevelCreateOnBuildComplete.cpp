// cl: /DNDEBUG /MD
//
// ExperienceLevelCreate::onBuildComplete, retail 0x004B9231 (38 bytes): slot 1
// of the class's +0x10 create-module interface vftable 0x00C5955C, so `this`
// is that subobject (module data at -0x0C). Unless the module data's +0x0C
// flag is set and the GameLogic predicate 0x0023C6FD (rowed as
// BfmeGlob939D::bfmeCall939D; pinned for GameLogic by address on this call
// site) is false, runs the level grant 0x004B9201 on the primary this (tail
// call).
// rva004B9201, retail 0x004B9201 (31 bytes): raises the Object's experience
// tracker (+0x264) by the module data's +0x08 level minus its current level
// (+0x24) through the tracker's 0x0039B4EC (pinned by address; LevelUpUpgrade
// 0x004B3E15 calls it too, with a level count and 1).
typedef bool Bool;
class ModuleData;
class ExperienceTracker
{
public:
	Bool rva0039B4EC(int levels, Bool flag1, Bool flag2);
	unsigned char m_pad00[0x24];
	int m_level;			// +0x24
};
class Object
{
public:
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
private:
	unsigned char m_pad000[0x264];
	ExperienceTracker *m_experienceTracker;	// +0x264
};
class GameLogic
{
public:
	char rva0023C6FD();
};
extern GameLogic *TheGameLogic;
struct ExperienceLevelCreateModuleData
{
	unsigned char m_pad00[0x08];
	int m_level;			// +0x08
	Bool m_0C;			// +0x0C
};
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class CreateModuleInterface
{
public:
	virtual void c00() = 0;
	virtual void onBuildComplete() = 0;
};
class CreateModule : public ModuleBase, public BehaviorModuleInterface, public CreateModuleInterface
{
};
class ExperienceLevelCreate : public CreateModule
{
public:
	virtual void onBuildComplete();
	void rva004B9201();
	const ExperienceLevelCreateModuleData *getData() const
	{
		return (const ExperienceLevelCreateModuleData *)m_moduleData;
	}
};
void ExperienceLevelCreate::rva004B9201()
{
	ExperienceTracker *tracker = m_object->getExperienceTracker();
	tracker->rva0039B4EC(getData()->m_level - tracker->m_level, false, false);
}
void ExperienceLevelCreate::onBuildComplete()
{
	if (!getData()->m_0C || TheGameLogic->rva0023C6FD())
		rva004B9201();
}
