// cl: /O1 /MD
// ?rva005E1158@Rva005E1158@@QAEXPBVImage@@@Z @0x005E1158 8B
// Evidence: unlock lane tail-forwards this+8 to rowed Rva005E0E1D::rva005E0E1D callers 0x005E9473 0x005E8E4C prev Rva005E10A8Method
class Image;

class Rva005E0E1D
{
public:
	void rva005E0E1D(const Image *image);
};

class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
private:
	char m_pad00[8];
	Rva005E0E1D *m_ptr08;
};

void Rva005E1158::rva005E1158(const Image *image)
{
	m_ptr08->rva005E0E1D(image);
}
