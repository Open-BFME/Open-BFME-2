// cl: /DNDEBUG /MD /EHsc
// ??1Rva003AB9FF@@UAE@XZ @0x003AB9FF 55B
// MI dtor: second base RenderObjectDrawModuleInfo at +0x18 via guarded
// this-adjust then first base Rva003AF50D at +0. Evidence: retail neg/sbb/and
// for +0x18 plus two rowed base dtor calls plus EH_prolog, chain after 0x003A9A8B.
// Rva003AF50D dtor is throw() (22B no-EH body): elides the or -1 between calls.
class Rva003AF50D {
public: virtual ~Rva003AF50D() throw();
private: char m_pad[0x18 - 4];
};

namespace FXParticleSystem {
class RenderObjectDrawModuleInfo {
public: virtual ~RenderObjectDrawModuleInfo();
private: char m_pad[0x40 - 4];
};
}

class __declspec(novtable) Rva003AB9FF : public Rva003AF50D, public FXParticleSystem::RenderObjectDrawModuleInfo {
public: virtual ~Rva003AB9FF();
};

Rva003AB9FF::~Rva003AB9FF()
{
}
