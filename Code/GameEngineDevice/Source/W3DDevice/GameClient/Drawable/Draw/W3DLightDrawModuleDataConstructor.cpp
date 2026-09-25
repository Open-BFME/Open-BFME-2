// cl: /O1 /arch:SSE /GX /MD /DNDEBUG
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
// Donor reference: BFME1 W3DLightDrawModuleDataConstructor.cpp (init-list
// +0x44, chained triples descending, Radius then Intensity, trailing
// scalars ascending). Recipe: the opaque-base plus explicit-vtable idiom of
// the landed W3DSupplyDrawModuleDataCtor TU (vtable spelled as the first
// member init, which is what puts its store ahead of the +0x44 init).

struct LightColorRGB
{
	float m_red; // +0x00
	float m_green; // +0x04
	float m_blue; // +0x08
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	const char *m_data;
};

class W3DLightDrawModuleData
{
public:
	W3DLightDrawModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned char m_pad04[4]; // +0x04
	LightColorRGB m_ambientColor; // +0x08 Ambient
	LightColorRGB m_diffuseColor; // +0x14 Diffuse
	LightColorRGB m_specularColor; // +0x20 Specular
	float m_radius; // +0x2C Radius
	float m_intensity; // +0x30 Intensity
	float m_flickerAmplitude; // +0x34 FlickerAmplitude
	float m_flickerFrequency; // +0x38 FlickerFrequency
	float m_pulseAmplitude; // +0x3C PulseAmplitude
	float m_pulseFrequency; // +0x40 PulseFrequency
	AsciiString m_attachToBone; // +0x44 AttachToBoneInAnotherModule
};

// ??0W3DLightDrawModuleData@@QAE@XZ
W3DLightDrawModuleData::W3DLightDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BCD820))
	, m_attachToBone()
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
