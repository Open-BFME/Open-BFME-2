// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1GpuDrawModuleInfo@FXParticleSystem@@UAE@XZ, retail 0x003A9D43, 48 bytes.
// GpuDrawModuleInfo destructor: destroys the detail-texture AsciiString at
// +0x0C through the pinned StringBase<char> dtor at 0x00036410 (the implicit
// AsciiString dtor inlines to that single call), then restores the base
// vtable 0x00BBB554 with the trivial inline base. Layout mirrors the landed
// copy ctor at 0x003A9D73 in GpuDrawModuleInfoCopyCtor.cpp (ints at +4/+8,
// string at +0x0C, float at +0x10). novtable suppresses the derived store so
// only the base store remains. Precedent: SlaveWatcherBehaviorModuleDataDtor
// (novtable plus trivial base) and W3DProjectileStreamDrawModuleDataDtor
// (single string plus EH base).

#include "ascii_string.h"


namespace FXParticleSystem
{

class GpuDrawModuleInfoBase
{
public:
	GpuDrawModuleInfoBase() {}
	virtual ~GpuDrawModuleInfoBase() {}
};

class __declspec(novtable) GpuDrawModuleInfo : public GpuDrawModuleInfoBase
{
public:
	virtual ~GpuDrawModuleInfo();
private:
	int m_totalFrames;
	int m_framesPerRow;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

GpuDrawModuleInfo::~GpuDrawModuleInfo()
{
}

}
