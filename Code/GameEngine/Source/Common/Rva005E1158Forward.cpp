// cl: /MD
// ?rva005E1158@Rva005E1158@@QAEXPBVImage@@@Z @0x005E1158 8B
// Evidence: unlock lane tail-forwards this+8 to rowed StrategicHUD::CommandButtonMovieClip::Impl::SetImage callers 0x005E9473 0x005E8E4C prev Rva005E10A8Method
class Image;

namespace StrategicHUD {
class CommandButtonMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::CommandButtonMovieClip::Impl
{
public:
	void SetImage(const Image *image);
};

class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
private:
	char m_pad00[8];
	StrategicHUD::CommandButtonMovieClip::Impl *m_ptr08;
};

void Rva005E1158::rva005E1158(const Image *image)
{
	m_ptr08->SetImage(image);
}
