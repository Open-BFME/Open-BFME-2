// cl: /O1 /GX- /DNDEBUG /MD /arch:SSE2

// GpuDrawModuleInfo default constructor.
//
// Retail 0x00563981 (35B) stores the GpuDraw vtable (0xC1C1E8), the two
// frame-count dwords at +4/+8 set to 1, the detail-texture string at +0xC
// nulled with an `and` store from its inline default, then the
// speed-multiplier at +0x10 set to 1.0f from .rdata (gate-filled). Member
// layout mirrors the landed DoXfer TU GpuDrawModuleInfoDoXfer.cpp in this
// folder; the frame counts ride the init list so the string null keeps its
// retail position after them.

class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	~AsciiString();

private:
	char *m_text;
};

namespace FXParticleSystem
{

class GpuDrawModuleInfo
{
public:
	GpuDrawModuleInfo();
	virtual ~GpuDrawModuleInfo();

private:
	int m_totalFrames;
	int m_framesPerRow;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

// ??0GpuDrawModuleInfo@FXParticleSystem@@QAE@XZ @0x563981
GpuDrawModuleInfo::GpuDrawModuleInfo()
	: m_totalFrames(1), m_framesPerRow(1)
{
	m_speedMultiplier = 1.0f;
}

}
