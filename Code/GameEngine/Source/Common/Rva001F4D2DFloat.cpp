// cl: /MD
// ?rva001F4D2D@Rva001F4D2D@@QAEMXZ @ 0x001F4D2D (34B):
// If sub at +0x9C is null return 0.0f else return its virtual slot 4.
// Evidence: mov ecx [ecx+0x9C] test je xorps movss fld; mov eax [ecx]
// call [eax+0x10]; 7 callers; unblocks 5.
class Rva001F4D2DSub
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual float f4();
};
class Rva001F4D2D
{
public:
	float rva001F4D2D();
private:
	char m_pad00[0x9C];
	Rva001F4D2DSub *m_sub9C;
};
float Rva001F4D2D::rva001F4D2D()
{
	Rva001F4D2DSub *p = m_sub9C;
	float v;
	if (p != 0)
		v = p->f4();
	else
		v = 0.0f;
	return v;
}
