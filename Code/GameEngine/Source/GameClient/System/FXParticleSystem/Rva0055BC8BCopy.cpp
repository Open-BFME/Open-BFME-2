// cl: /EHs-c-
// ??0Rva0055BC8B@@QAE@ABV0@@Z @0x003ADD9D 42B copy ctor vtable 0x0081D1A4 eight RGB keys at +4 plus float at +0x84. Evidence: rowed ctor 0x0055BC8B same vtable; caller 0x003ADD52; rep movsd 0x20 plus trailing mov.
namespace FXParticleSystem
{
class Xfer;
class Snapshot
{
public:
	Snapshot() {}
	Snapshot(const Snapshot &that) {}
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};
}
class Rva0055BC8B : public FXParticleSystem::Snapshot
{
public:
	Rva0055BC8B(const Rva0055BC8B &that);
	virtual ~Rva0055BC8B();
private:
	struct Keys
	{
		unsigned int v[32];
	};
	Keys m_keys;
	float m_trailing;
};
Rva0055BC8B::Rva0055BC8B(const Rva0055BC8B &that)
{
	m_keys = that.m_keys;
	m_trailing = that.m_trailing;
}
