// cl: /DNDEBUG /MD
// ??4Rva0031AB7F@@QAEAAV0@ABV0@@Z @ 0x0031AB7F 80B: copy assign via base
// StreakDrawModuleTemplate assign plus AsciiString at +0x10 plus 32-dword
// copy +0x14..+0x93 plus +0x94/+0x98. Evidence: rowed base assign 0x001FD28E
// plus pinned AsciiString assign 0x000366F0 plus caller 0x0031B0A9.
class FXParticleSystem
{
public:
	class StreakDrawModuleTemplate
	{
	public:
		StreakDrawModuleTemplate &operator=(const StreakDrawModuleTemplate &that);

	private:
		char m_pad[0x10];
	};
};

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &that);
};

class Rva0031AB7F : public FXParticleSystem::StreakDrawModuleTemplate
{
public:
	Rva0031AB7F &operator=(const Rva0031AB7F &that);

private:
	StringBase<char> m_0010;
	int m_0014[32];
	int m_0094;
	int m_0098;
};

Rva0031AB7F &Rva0031AB7F::operator=(const Rva0031AB7F &that)
{
	FXParticleSystem::StreakDrawModuleTemplate::operator=(that);
	m_0010.set(that.m_0010);
	for (int i = 0; i < 32; i++)
		m_0014[i] = that.m_0014[i];
	m_0094 = that.m_0094;
	m_0098 = that.m_0098;
	return *this;
}
