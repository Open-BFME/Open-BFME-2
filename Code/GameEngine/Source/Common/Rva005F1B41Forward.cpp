// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva005F1B41@Rva005F1B41@@QAEXPBVImage@@@Z @ 0x005F1B41 8B
// Evidence: tail-jmp to rowed ?rva005F191E@Rva005F191E@@QAEXPBVImage@@@Z at 0x005F191E; two callers in 0x005E3753; prev/next neighbours in AptImageKeySetters.cpp
class Image;

class Rva005F191E
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
	Rva005F191E *m_04; // +0x04
};

void Rva005F1B41::rva005F1B41(const Image *image)
{
	m_04->rva005F191E(image);
}
