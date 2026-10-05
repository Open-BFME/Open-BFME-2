// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE
//
// ??0Rva0055BC8B@@QAE@XZ, retail 0x0055BC8B, 71 bytes.
// Evidence: eight RGBColorKeyframe elements at +4 via rowed vector_ctor
// 0x1423 through rowed 0x00001E67 plus float at +0x84 zeroed; vtable
// 0x0081D1A4; EH prolog 0x00629188; prev DefaultColorModuleInfo ctor 82B.
class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	Snapshot(const Snapshot &that) {}

	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

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
};

Rva0055BC8B::Rva0055BC8B() : m_trailing(0.0f)
{
}
