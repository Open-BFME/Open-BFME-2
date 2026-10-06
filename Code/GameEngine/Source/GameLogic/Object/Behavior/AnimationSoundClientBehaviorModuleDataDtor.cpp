// cl: /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1AnimationSoundClientBehaviorModuleData@@UAE@XZ, retail 0x004CA768, 48 bytes.
// Target evidence: the audited scalar deleting dtor 0x004CA74C calls this
// body (registration AnimationSoundClientBehavior -> factory 0x00252BC2 ->
// ctor 0x004CA70D). It destroys the sound tree at +0x08 (rowed
// ~AnimationSoundTree 0x004CA653), then the inlined trivial Snapshot base
// stores 0x00BBB554. No derived vptr store (novtable).

#include "Common/Snapshot.h"

class AnimationSoundTree
{
public:
	~AnimationSoundTree();

private:
	void *m_header;
	int m_count;
};

class __declspec(novtable) AnimationSoundClientBehaviorModuleData : public Snapshot
{
public:
	virtual ~AnimationSoundClientBehaviorModuleData();

private:
	int m_04;
	AnimationSoundTree m_tree;	// +0x08
};

AnimationSoundClientBehaviorModuleData::~AnimationSoundClientBehaviorModuleData()
{
}
