// cl: /DNDEBUG /MD
//
// ?buildFieldParse@W3DModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x000C9240 (17 bytes: a single MultiIniFieldParse::add of the class
// table at 0x00BCB3C8 with offset 0). The table starts InitialRecoilSpeed,
// MaxRecoilDistance, RecoilDamping, RecoilSettleSpeed and runs through the
// W3DModelDraw field set (OkToChangeModelColor, MinLODRequired,
// ProjectileBoneFeedbackEnabledSlots, Default/ModelConditionState,
// Idle/Transition/AnimationState, TrackMarks, ExtraPublicBone,
// AttachToBoneInAnotherModule, DependencySharedModelFlags, TimeOfDayTexture,
// UseProducerTexture, NoRotate, UseFiringArcRotation, RandomTexture,
// BurntTexture, AttachModel, ParticlesAttachedToAnimatedBones,
// TrackMarksLeft/RightBone, RampMesh1/2, EmbedPortal, WallBoundsMesh).
// Provenance: the field order matches the BFME1 W3DModelDrawModuleData donor
// table (reference/open-bfme-1 W3DModelDraw.cpp); the two-phase ModuleData
// factory at retail 0x000648D6 pushes this proc's address before calling
// INI::initFromINIMultiProc, which names the class. Four chained subclass
// procs call this one as their base (0x000CAE28, 0x000CB133, 0x000CDF96,
// 0x000CA089) plus 0x000CF8D3 through the ModelName sibling chain.

class MultiIniFieldParse;

struct FieldParse;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class W3DModelDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DModelDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(0x00BCB3C8), 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?W3DModelDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DModelDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
