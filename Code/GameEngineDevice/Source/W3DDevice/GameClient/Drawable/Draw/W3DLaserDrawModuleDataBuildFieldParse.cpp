// cl: /DNDEBUG /MD
//
// ?buildFieldParse@W3DLaserDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x000C928F (17 bytes: a single MultiIniFieldParse::add of the class
// table at 0x00BCB840 with offset 0). The table runs NumBeams,
// Inner/OuterBeamWidth, Inner/OuterColor, MaxIntensityLifetime, FadeLifetime,
// Texture, ScrollRate, Tile, Segments, ArcHeight, SegmentOverlapRatio,
// TilingScalar, FanWidth and Envelope, matching the BFME1 W3DLaserDraw donor
// table (reference/open-bfme-1 W3DLaserDraw.cpp) plus the FanWidth/Envelope
// tail. The two-phase ModuleData factory at retail 0x00064962 pushes this
// proc's address before calling INI::initFromINIMultiProc, which names the
// class.

class MultiIniFieldParse;

struct FieldParse;

extern const int s_laserDrawFieldTable[];
class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class W3DLaserDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DLaserDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(s_laserDrawFieldTable), 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?W3DLaserDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DLaserDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
