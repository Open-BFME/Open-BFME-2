// cl: /GX- /O1 /arch:SSE /G7
// ?rva005C7C7D@Rva005C7C7D@@QAEXPBVImage@@@Z at 0x005C7C7D (8B). Target disassembly reads Impl* at +4 then tail-jumps to the rowed SetImage; callers at 0x005679D1 and 0x005C3740.
class Image;

class InGameCommandButtonMovieClip
{
public:
	class Impl;
};

class InGameCommandButtonMovieClip::Impl
{
public:
	void SetImage(const Image *image);
};

class Rva005C7C7D
{
public:
	void rva005C7C7D(const Image *image);

private:
	char pad00[4];
	InGameCommandButtonMovieClip::Impl *m_impl;
};

void Rva005C7C7D::rva005C7C7D(const Image *image)
{
	return m_impl->SetImage(image);
}
