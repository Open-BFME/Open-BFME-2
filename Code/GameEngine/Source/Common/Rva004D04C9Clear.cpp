// cl: /O1 /MD
// ?rva004D04C9@Rva004D04C9@@QAEPAXXZ @0x004D04C9 23B: memset this 0x2000 plus return this.
// Evidence: pin ji_006291ae memset plus caller 0x004D152E; neighbours ConnectionManagerO1.
void *ji_006291ae(void *dst, int val, unsigned int size);

class Rva004D04C9
{
public:
	void *rva004D04C9();
private:
	char m_pad[0x2000];
};

void *Rva004D04C9::rva004D04C9()
{
	ji_006291ae(this, 0, 0x2000);
	return this;
}
