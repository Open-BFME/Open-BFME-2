// cl: /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0ShadowTypeInfo@Shadow@@QAE@XZ, retail 0x00079514, 64 bytes. Dedicated
// TU (its file name is from the row's earlier, wrong AudioEventRTS name).
//
// Shadow::ShadowTypeInfo default-constructs empty: two null strings, a
// zeroed shadow type, five zero floats, a 20.0f default, two zero flags and
// a set one. The retail body is frameless straight-line member stores with
// no calls.
//
// Identity (target evidence): every retail caller is shadow or decal code
// (W3DShadowManager::addShadow 0x0009A8D3, which builds its local copy of
// the Shadow::ShadowTypeInfo it is passed here; W3DDebrisDraw::setModelName;
// RadiusDecalTemplate; DynamicDecalFXNugget::doFXPos; the shadow INI
// parser 0x000B9AFF ...), and WB's W3DScriptedModelDraw::allocateShadows
// (WB 0x009292C0) calls this body's WB twin (0x0064F230) before handing
// the info to addShadow. The two-string layout is BFME 2's; Zero Hour's
// ShadowTypeInfo holds a char name instead. The type at +8 is the word
// addShadow reads; the other member names are neutral.

typedef int Int;

#define NULL 0

#include "ascii_string.h"

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();

		AsciiString m_first;
		AsciiString m_second;
		Int m_type;
		float m_floatC;
		float m_float10;
		float m_float14;
		float m_float18;
		float m_float1C;
		float m_float20;
		unsigned char m_byte24;
		unsigned char m_byte25;
		unsigned char m_byte26;
	};
};

// ??0ShadowTypeInfo@Shadow@@QAE@XZ
Shadow::ShadowTypeInfo::ShadowTypeInfo()
	: m_type(0),
	  m_floatC(0.0f),
	  m_float10(0.0f),
	  m_float14(0.0f),
	  m_float18(0.0f),
	  m_float1C(0.0f),
	  m_float20(20.0f),
	  m_byte24(0),
	  m_byte25(0),
	  m_byte26(1)
{
}
