// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include/Common /GX /MD /DNDEBUG
//
// ??0W3DLightDrawModuleData@@QAE@XZ, retail 0x000CFB3E, 107 bytes.
// Frameless SSE ModuleData ctor: installs the vtable 0x00BCD820, inlines the
// empty AsciiString ctor at +0x44, sets Radius 20.0f at +0x2C, zeroes the
// three light colors as chained triples (Ambient +0x08, Diffuse +0x14,
// Specular +0x20, each stored descending), then Intensity 1.0f at +0x30 and
// the four flicker/pulse scalars at +0x34..+0x40.
//
// Evidence: the rowed factory friend_newModuleData at 0x00064E2F news 0x48
// and calls here (see W3DLightDrawModuleDataFriendNew.cpp); the class parse
// table at 0x00BCD918 names Ambient/Diffuse/Specular (RGB, offsets 8/20/32),
// Radius (44), Intensity (48), FlickerAmplitude/FlickerFrequency (52/56),
// PulseAmplitude/PulseFrequency (60/64) and AttachToBoneInAnotherModule (68);
// the 20.0f/1.0f reads hit the shared literal pool (13+ retail users each).
// The ModuleData base is novtable: its empty constructor leaves the derived
// vptr store first, as in retail. Use the same polymorphic layout as the
// destructor in W3DLightDraw.cpp rather than a separate explicit-vptr view.

#include "BfmeModuleData.h"

class MultiIniFieldParse;

struct LightColorRGB
{
	float m_red; // +0x00
	float m_green; // +0x04
	float m_blue; // +0x08
};

#include "ascii_string.h"

class W3DLightDrawModuleData : public ModuleData
{
public:
	W3DLightDrawModuleData();
	virtual ~W3DLightDrawModuleData();
private:
	unsigned char m_pad04[4];
public:
	LightColorRGB m_ambientColor;
	LightColorRGB m_diffuseColor;
	LightColorRGB m_specularColor;
	float m_radius;
	float m_intensity;
	float m_flickerAmplitude;
	float m_flickerFrequency;
	float m_pulseAmplitude;
	float m_pulseFrequency;
private:
	AsciiString m_attachToBone;
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ??0W3DLightDrawModuleData@@QAE@XZ
W3DLightDrawModuleData::W3DLightDrawModuleData()
	: m_attachToBone()
{
	m_ambientColor.m_red = m_ambientColor.m_green = m_ambientColor.m_blue = 0.0f;
	m_diffuseColor.m_red = m_diffuseColor.m_green = m_diffuseColor.m_blue = 0.0f;
	m_specularColor.m_red = m_specularColor.m_green = m_specularColor.m_blue = 0.0f;

	m_radius = 20.0f;
	m_intensity = 1.0f;

	m_flickerAmplitude = 0.0f;
	m_flickerFrequency = 0.0f;
	m_pulseAmplitude = 0.0f;
	m_pulseFrequency = 0.0f;
}
