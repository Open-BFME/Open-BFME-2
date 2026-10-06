// cl: /DNDEBUG /MD /EHsc
// ??1Rva003ABA4C@@UAE@XZ @0x003ABA4C 55B
// MI dtor: second base GpuDrawModuleInfo at +0x18 via guarded this-adjust
// then first base Rva003AF50D at +0. Evidence: retail neg/sbb/and for +0x18
// plus rowed GpuDraw 0x003A9D43 plus rowed Rva003AF50D 0x003A983C plus EH.
// Sibling of landed 0x003AB9FF (RenderObjectDraw second base).
// Rva003AF50D dtor is throw(): elides the or -1 between calls.
class Rva003AF50D {
public: virtual ~Rva003AF50D() throw();
private: char m_pad[0x18 - 4];
};

namespace FXParticleSystem {
class GpuDrawModuleInfo {
public: virtual ~GpuDrawModuleInfo();
private: char m_pad[0x14 - 4];
};
}

class __declspec(novtable) Rva003ABA4C : public Rva003AF50D, public FXParticleSystem::GpuDrawModuleInfo {
public: virtual ~Rva003ABA4C();
};

Rva003ABA4C::~Rva003ABA4C()
{
}
