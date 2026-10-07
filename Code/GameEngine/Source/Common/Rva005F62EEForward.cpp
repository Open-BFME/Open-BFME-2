// cl: /MD
// ?rva005F62EE@Rva005F62EE@@QAEXPBVImage@@@Z @0x005F62EE 8B. Tail-forward to
// rowed 0x005F6096 on member +8. Evidence: mov ecx [ecx+8] then jmp to rowed
// ?rva005F6096@Rva005F6096@@QAEXPBVImage@@@Z in AptImageKeySetters.cpp.
class Image;
class Rva005F6096
{
public:
	void rva005F6096(const Image *img);
	void rva005F6112(const Image *img);
};
class Rva005F62EE
{
	char m_pad00[8];
	Rva005F6096 *m_08;
public:
	void rva005F62EE(const Image *img);
	void rva005F62F6(const Image *img);
};
void Rva005F62EE::rva005F62EE(const Image *img)
{
	m_08->rva005F6096(img);
}

void Rva005F62EE::rva005F62F6(const Image *img)
{
	m_08->rva005F6112(img);
}
