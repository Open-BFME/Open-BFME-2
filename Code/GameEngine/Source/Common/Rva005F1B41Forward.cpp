// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F1B41@Rva005F1B41@@QAEXPBVImage@@@Z @ 0x005F1B41 8B
// Evidence: tail-jmp to rowed ?rva005F191E@Impl@RegionDetailsTerritoryMovieClip@StrategicHUD@@QAEXPBVImage@@@Z at 0x005F191E; two callers in 0x005E3753; prev/next neighbours in AptImageKeySetters.cpp
class Image;

namespace StrategicHUD {
class RegionDetailsTerritoryMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl
{
public:
	void rva005F191E(const Image *image);
};

class Rva005F1B41
{
public:
	void rva005F1B41(const Image *image);
private:
	char m_pad00[4];
	StrategicHUD::RegionDetailsTerritoryMovieClip::Impl *m_04; // +0x04
};

void Rva005F1B41::rva005F1B41(const Image *image)
{
	m_04->rva005F191E(image);
}
