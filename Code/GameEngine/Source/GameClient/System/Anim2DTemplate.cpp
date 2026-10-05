// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/asciistring8outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Anim2D.h"
#include "GameClient/Image.h"

// BFME retains formatted exceptions in release and adds an integer to ZH's message storage.
class INIException
{
public:
	INIException(Int, const char *message, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_message;
	Int m_unreconstructed04;
};

// ??0Anim2DTemplate@@QAE@VAsciiString@@@Z
Anim2DTemplate::Anim2DTemplate( AsciiString name )
{

	m_name = name;
	m_images = NULL;
	m_numFrames = NUM_FRAMES_INVALID;
	m_framesBetweenUpdates = 0;
	m_animMode = ANIM_2D_LOOP;
	m_randomizeStartFrame = FALSE;
	m_nextTemplate = NULL;

}  // end Anim2DTemplate

// ?parseNumImages@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
// Target Ghidra [2D72F1,2D7355),100B; exact parser error literal
// xref and NumberImages INI-table role establish identity independently of
// the refuted drift placement59E9BD. Native calls full78B bounded unsigned
// parser2EF72 and56B allocation2D6AF5; error uses full85B INIException
// construction2F681 and shared throw information. Native reads the name
// at+8 directly; m_name.str avoids the donor getName by-value temporary.
// Semantic guide: BFME1 6583b3c1 Anim2DTemplate.cpp and ZH Anim2D.cpp;
// layout and complete byte extent established separately from target.
void Anim2DTemplate::parseNumImages(INI *ini, void *instance, void *store, const void *userData)
{
	UnsignedInt numFrames;
	ini->parseUnsignedInt(ini, instance, &numFrames, userData);

	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	Int minimumFrames = 1;
	if (numFrames < minimumFrames) {
		throw INIException(3, "Anim2DTemplate::parseNumImages - Invalid animation '%s', animations must have '%d' or more frames defined\n",
			animTemplate->m_name.str(), minimumFrames);
	}

	animTemplate->allocateImages((UnsignedShort)numFrames);
}

// storeImage is recovered in Anim2DTemplateStoreImage.cpp at2D7355.
// Keep its two previously rowed accessor COMDATs emitted without a second
// application definition. This scaffold has no retail address.
#pragma inline_depth(0)
// ?Anim2DTemplateAccessorEmitAnchor absent-from-retail
void Anim2DTemplateAccessorEmitAnchor(Anim2DTemplate*t,const Image*i,AsciiString*a,AsciiString*b)
{
 *a=t->getName(); *b=i->getName();
}
#pragma inline_depth()

// Existing pin2EF72 is the complete78B bounded parser with the same static
// four-argument ABI. Bind its recovered linker name rather than leaving an
// unresolved donor spelling; the native call proves the consumed identity.
#pragma comment(linker, "/alternatename:?parseUnsignedInt@INI@@SAXPAV1@PAX1PBX@Z=?dup_002EF72@INI@@SAXPAV1@PAX1PBX@Z")
