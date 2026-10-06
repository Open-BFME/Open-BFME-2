// cl: /MD /EHsc
// ?rva005F7512@Rva005F6A58@@QAEXHH@Z @0x005F7512 44B: vslot 12 of Rva005F6A58 vtable 0x008797F4 forwards to rowed StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot SetProgressString 0x005F6E85 when args differ from +0x20 +0x24.
namespace StrategicHUD {
class BuildQueueDetailsMovieClip
{
public:
	class Impl
	{
	public:
		class InProgressIconSlot;
	};
};
}

class StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot
{
public:
	void SetProgressString(int unused, int turns);
};
class Rva005F6A58
{
public:
	void rva005F7512(int a, int b);
private:
	char m_pad00[0x20];
	int m_20;
	int m_24;
};
void Rva005F6A58::rva005F7512(int a, int b)
{
	if (a == m_20 && b == m_24)
		return;
	((StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot *)this)->SetProgressString(a, b);
	m_20 = a;
	m_24 = b;
}
