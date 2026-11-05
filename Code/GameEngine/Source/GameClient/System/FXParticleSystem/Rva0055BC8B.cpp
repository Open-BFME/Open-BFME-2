// cl: /DNDEBUG /MD /EHsc /Ob2
//
// ??0Rva0055BC8B@@QAE@XZ, retail 0x0055BC8B, 71 bytes.
// Evidence: eight RGBColorKeyframe elements at +4 via rowed vector_ctor
// 0x1423 through rowed 0x00001E67 plus float at +0x84 zeroed; vtable
// 0x0081D1A4; EH prolog 0x00629188; prev DefaultColorModuleInfo ctor 82B.
class Xfer;

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class RGBColorKeyframe
{
public:
	RGBColorKeyframe();

private:
	char m_data[0x10];
};

}

class Rva0055BC8B : public Snapshot
{
public:
	Rva0055BC8B();
	virtual ~Rva0055BC8B() {}

private:
	FXParticleSystem::RGBColorKeyframe m_keys[8];
	float m_trailing;
public:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};

Rva0055BC8B::Rva0055BC8B() : m_trailing(0.0f)
{
}
