// cl: /O1 /DNDEBUG /MD /EHsc

// GpuDrawModuleInfo copy constructor.
//
// Retail 0x003A9D73 (79B) stores the GpuDraw vtable (0xC1C1E8), copies the
// two frame-count dwords at +4/+8, constructs the detail-texture string at
// +0xc through the inline AsciiString copy (rowed StringBase callee
// 0x000365F0, with an EH frame around it), then copies the
// speed-multiplier dword at +0x10. Member layout mirrors the landed DoXfer
// TU GpuDrawModuleInfoDoXfer.cpp and the op= TU
// GpuDrawModuleInfoOpAssign.cpp in this folder.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &that)
		: StringBase<char>(that)
	{
	}
	~AsciiString();
	AsciiString &operator=(const AsciiString &that);
};

namespace FXParticleSystem
{

class GpuDrawModuleInfoBase
{
public:
	GpuDrawModuleInfoBase(const GpuDrawModuleInfoBase &) {}
	virtual ~GpuDrawModuleInfoBase() {}
};

class GpuDrawModuleInfo : public GpuDrawModuleInfoBase
{
public:
	GpuDrawModuleInfo(const GpuDrawModuleInfo &that);
	virtual ~GpuDrawModuleInfo();
	GpuDrawModuleInfo &operator=(const GpuDrawModuleInfo &that);

private:
	int m_totalFrames;
	int m_framesPerRow;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

// ??0GpuDrawModuleInfo@FXParticleSystem@@QAE@ABV01@@Z @0x3A9D73
GpuDrawModuleInfo::GpuDrawModuleInfo(const GpuDrawModuleInfo &that)
	: GpuDrawModuleInfoBase(that),
	  m_totalFrames(that.m_totalFrames),
	  m_framesPerRow(that.m_framesPerRow),
	  m_detailTexture(that.m_detailTexture),
	  m_speedMultiplier(that.m_speedMultiplier)
{
}

}
