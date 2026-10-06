// cl: /DNDEBUG /MD
//
// Client-side Drawable behavior ModuleData::buildFieldParse procs.
//
// ?buildFieldParse@AnimationSoundClientBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x004CAB2C (17 bytes): the AnimationSound table at 0x00C5F064
// (AnimationSound, MaxUpdateRangeCap). Class evidenced by BFME1's
// AnimationSoundClientBehaviorModuleData files (Drawable/Behavior, 0x18-byte
// factory product matching the owning factory at 0x00252BC2, which pushes
// this proc's VA). Registered with MultiIniFieldParse::add (rowed at
// 0x2BC6E).

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class AnimationSoundClientBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void AnimationSoundClientBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00C5F064), 0);
}
