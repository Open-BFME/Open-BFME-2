// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AnimationSoundClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00252BC2, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// pinned sole-caller ctor at 0x4CA70D, then feeds the new data plus the class
// parse proc (rowed at 0x4CAB2C in
// AnimationSoundClientBehaviorBuildFieldParse.cpp, pushed immediate, no pin)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x14 pad) per the
// DemoTrapUpdateModuleDataFriendNew recipe. Class identity is the BFME1
// AnimationSoundClientBehaviorModuleData donor joined to the rowed
// AnimationSound table proc (same class) and the 0x18 size push.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AnimationSoundClientBehaviorModuleData
{
public:
	AnimationSoundClientBehaviorModuleData();
	virtual ~AnimationSoundClientBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@AnimationSoundClientBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AnimationSoundClientBehaviorModuleData::friend_newModuleData(INI *ini)
{
	AnimationSoundClientBehaviorModuleData *data = new AnimationSoundClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AnimationSoundClientBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
