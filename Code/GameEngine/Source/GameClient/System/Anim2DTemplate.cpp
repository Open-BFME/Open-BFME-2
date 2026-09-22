// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/asciistring8outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
// ?parseNumImages@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z present-unmatched
void Anim2DTemplate::parseNumImages(INI *ini, void *instance, void *store, const void *userData)
{
	UnsignedInt numFrames;
	ini->parseUnsignedInt(ini, instance, &numFrames, userData);

	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	Int minimumFrames = 1;
	if (numFrames < minimumFrames) {
		throw INIException(3, "Anim2DTemplate::parseNumImages - Invalid animation '%s', animations must have '%d' or more frames defined\n",
			animTemplate->getName().str(), minimumFrames);
	}

	animTemplate->allocateImages((UnsignedShort)numFrames);
}

// ?storeImage@Anim2DTemplate@@QAEXPBVImage@@@Z
// ?storeImage@Anim2DTemplate@@QAEXPBVImage@@@Z present-unmatched
void Anim2DTemplate::storeImage(const Image *image)
{
	if (image == NULL) {
		return;
	}

	for (Int frameIndex = 0; frameIndex < m_numFrames; ++frameIndex) {
		if (m_images[frameIndex] == NULL) {
			m_images[frameIndex] = image;
			return;
		}
	}

	throw INIException(3, "Anim2DTemplate::storeImage - Unable to store image '%s' into animation '%s' because the animation is setup to only support '%d' image frames\n",
		image->getName().str(), getName().str(), m_numFrames);
}
