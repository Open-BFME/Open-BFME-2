// cl: /O1 /DNDEBUG /MD /EHsc

// GpuDrawModuleInfo assignment operator.
//
// Retail 0x003A7EF0 (45B) copies the two frame-count dwords at +4/+8,
// assigns the detail-texture string at +0xc through AsciiString::operator=
// (rowed callee 0x000366F0), then copies the speed-multiplier dword at
// +0x10. Member layout mirrors the landed DoXfer TU
// GpuDrawModuleInfoDoXfer.cpp in this folder.

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
	AsciiString &operator=(const AsciiString &that);
};

namespace FXParticleSystem
{

class GpuDrawModuleInfo
{
public:
	virtual ~GpuDrawModuleInfo();
	GpuDrawModuleInfo &operator=(const GpuDrawModuleInfo &that);

private:
	int m_totalFrames;
	int m_framesPerRow;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

// ??4GpuDrawModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z @0x3A7EF0
GpuDrawModuleInfo &GpuDrawModuleInfo::operator=(const GpuDrawModuleInfo &that)
{
	m_totalFrames = that.m_totalFrames;
	m_framesPerRow = that.m_framesPerRow;
	m_detailTexture = that.m_detailTexture;
	m_speedMultiplier = that.m_speedMultiplier;
	return *this;
}

}
