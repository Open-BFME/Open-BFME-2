// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/asciistring8outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ?storeImage@Anim2DTemplate@@QAEXPBVImage@@@Z @0x002D7355 122B: next free image slot or INIException; donor reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/Anim2DTemplate.cpp and ZH GeneralsMD Anim2D.cpp; callers parseImage 0x2D740B and 0x2D74B8.
#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "GameClient/Anim2D.h"

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

// Minimal Image model: vtable at +0 (MemoryPoolObject, 4B) then m_name at +4.
// Real Image has protected m_name; public here gives direct str() without temps.
class Image
{
public:
	virtual ~Image();
	AsciiString m_name; // +4
};

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
		image->m_name.str(), m_name.str(), m_numFrames);
}
