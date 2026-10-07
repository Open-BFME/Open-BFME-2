// cl: /O1 /arch:SSE /G7 /MD /EHsc
// 0x005FC9F0 / 8 bytes. The caller passes an integer from +0x90. Retail
// forwards through the implementation pointer at +0x18 to the matched Impl
// method; the wrapper class and member offset are structural inferences.

class Image;

namespace StrategicHUD
{
class ArmyMemberIconMovieClip
{
public:
	class Impl
	{
	public:
		void rva005FC85A(int value);
		void SetTypeImage(const Image *image);
	};
};
}

class Rva005FC9F0
{
public:
	void rva005FC9F0(int value);
	void rva005FC9E8(const Image *image);

private:
	unsigned char m_pad00[0x18];
	StrategicHUD::ArmyMemberIconMovieClip::Impl *m_impl;
};

void Rva005FC9F0::rva005FC9F0(int value)
{
	m_impl->rva005FC85A(value);
}

void Rva005FC9F0::rva005FC9E8(const Image *image)
{
	m_impl->SetTypeImage(image);
}
