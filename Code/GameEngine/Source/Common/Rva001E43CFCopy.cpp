// cl: /MD
//
// ?rva001E43CF@Rva001E43CF@@QAEXPAX@Z @0x001E43CF 87B
// __thiscall 12-dword copy from src to +0x68..+0x94; same matrix as 0x001E41FA
// blocked wall; caller 0x001E5BA6 in 0x001E56DC/2113.
struct Rva001E43CFMatrix
{
	int m00, m04, m08, m0c, m10, m14, m18, m1c, m20, m24, m28, m2c;
};
class Rva001E43CF
{
public:
	void rva001E43CF(void *src);
private:
	unsigned char m_pad[0x68];
	int m68, m6c, m70, m74, m78, m7c, m80, m84, m88, m8c, m90, m94;
};
void Rva001E43CF::rva001E43CF(void *src)
{
	int *d1 = &m68;
	int *s1 = (int *)src;
	d1[0] = s1[0];
	d1[1] = s1[1];
	d1[2] = s1[2];
	d1[3] = s1[3];
	int *d2 = &m78;
	int *s2 = (int *)((char *)src + 0x10);
	d2[0] = s2[0];
	d2[1] = s2[1];
	d2[2] = s2[2];
	d2[3] = s2[3];
	int *d3 = &m88;
	int *s3 = (int *)((char *)src + 0x20);
	d3[0] = s3[0];
	d3[1] = s3[1];
	d3[2] = s3[2];
	d3[3] = s3[3];
}
