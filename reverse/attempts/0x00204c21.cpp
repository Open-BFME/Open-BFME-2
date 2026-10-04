// ?rva00204C21@Rva00204C21@@QAEXPBD@Z
// partial score=1.0 date=2026-10-04
// cl: /O1
// Donor1281192f68 BfmeConv1937.cpp. Target204C21/71B has a preceding
// 204C16/11B base-destructor entry and complete RET4 ending204C68.
// Isolated compiled donor matches every non-relocation byte. Worker20453C
// and ParticleSystemManager worker1F9EAF remain unrowed; no linkable providers.
// Constructor37BA0 and cleanup36410 are matched string workers.
// This bank preserves donor names as source leads, not target identities.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufCW;

private:
	void releaseBuffer();
};

class ParticleSystemManager
{
public:
	void bfmeStopCW(const BFMERetailAsciiString &name);
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeHostCW
{
public:
	void bfmeSpawnCW(const char *name);
	void bfmeStartCW();
};

void BfmeHostCW::bfmeSpawnCW(const char *name)
{
	bfmeStartCW();

	{
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);

		TheParticleSystemManager->bfmeStopCW(text);
	}
}
