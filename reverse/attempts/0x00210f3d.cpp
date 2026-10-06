// ??4Rva00210F3D@@QAEAAV0@ABV0@@Z
// partial score=0.93 date=2026-10-06
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00210F3D, 39 bytes (first of 79B packet; second starts 0x00210F64):
// copy-assign calling rowed StreakDrawModuleTemplate::operator= then copying
// +0x10/+0x14/+0x18, returning *this. Caller 0x0021117D unblocks 0x00211142.
namespace FXParticleSystem
{
class StreakDrawModuleTemplate
{
public:
	StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &that);
	char m_pad[0x10];
};
}

class Rva00210F3D : public FXParticleSystem::StreakDrawModuleTemplate
{
public:
	Rva00210F3D &operator=(const Rva00210F3D &that);
private:
	int m_10;
	int m_14;
	int m_18;
};

// ??4Rva00210F3D@@QAEAAV0@ABV0@@Z
Rva00210F3D &Rva00210F3D::operator=(const Rva00210F3D &that)
{
	const FXParticleSystem::StreakDrawModuleTemplate &b = that;
	FXParticleSystem::StreakDrawModuleTemplate::operator=(b);
	m_10 = that.m_10;
	m_14 = that.m_14;
	m_18 = that.m_18;
	return *this;
}
