// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 ParticleSystem saveable-flag getter, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameClient/System/ParticleSys.cpp).
// Retail BFME2 keeps the flag at the same offset (+0x33A).

class ParticleSystem
{
public:
	bool isSaveable() const;

private:
	unsigned char m_pre[0x33A];
	bool m_saveable;	// +0x33A
};

// ?isSaveable@ParticleSystem@@QBE_NXZ
bool ParticleSystem::isSaveable() const
{
	return m_saveable;
}
