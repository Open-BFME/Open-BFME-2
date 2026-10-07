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

// ?rva005E1178@Rva005E1178@@QAEXM@Z @0x005E1178 19B
// Leaf float forwarder to rowed Rva005E1008::rva005E1008 via +8, same shape
// as the 8B pointer forwarder above. Pin names a stdcall free function but the
// body reads ecx as this and rets 4 for one float, so honest method name.
class Rva005E1008
{
public:
	void rva005E1008(float v);
};

class Rva005E1178
{
public:
	void rva005E1178(float v);
private:
	char m_pad00[8];
	Rva005E1008 *m_ptr08;
};

void Rva005E1178::rva005E1178(float v)
{
	m_ptr08->rva005E1008(v);
}
