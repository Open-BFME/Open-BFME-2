// cl: /DNDEBUG /MD
//
// ?buildFieldParse@W3DLightDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z
// retail 0x000CFBDF (17 bytes: a single MultiIniFieldParse::add of the class
// table at 0x00BCD918 with offset 0). The table runs Ambient, Diffuse,
// Specular, Radius, Intensity, FlickerAmplitude, FlickerFrequency,
// PulseAmplitude, PulseFrequency and AttachToBoneInAnotherModule. The
// two-phase ModuleData factory at retail 0x00064E2F pushes this proc's
// address before calling INI::initFromINIMultiProc, which names the class;
// the BFME1 W3DLightDraw factory donor (reference/open-bfme-1
// W3DLightDrawFriendNewModuleDataThunk.cpp) news the same 0x48 bytes.

class MultiIniFieldParse;

struct FieldParse;

extern const int s_lightDrawFieldTable[];
class MultiIniFieldParse
{
public:
	void add(const FieldParse *parse, unsigned int extraOffset);
};

class W3DLightDrawModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void W3DLightDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(s_lightDrawFieldTable), 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?W3DLightDrawModuleDataParse@@YAXAAVMultiIniFieldParse@@@Z=?buildFieldParse@W3DLightDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z")
