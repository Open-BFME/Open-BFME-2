// cl: /MD
// ?rva00340E5E@Rva00340E5E@@QBEMXZ @0x00340E5E 18B chain via rowed 0x002627E8 float getter prev 0x00340D70 next 0x00340E70 caller 0x0034E795
class Rva002627E8 {
public:
	float rva002627E8() const;
};
struct Rva00340E5EMid258 {
	char m_pad[0x258];
	Rva002627E8 *m_obj;
};
struct Rva00340E5EMid14 {
	char m_pad[0x14];
	Rva00340E5EMid258 *m_mid;
};
class Rva00340E5E {
public:
	float rva00340E5E() const;
private:
	char m_pad[0x18];
	Rva00340E5EMid14 *m_p;
};
float Rva00340E5E::rva00340E5E() const
{
	float r = m_p->m_mid->m_obj->rva002627E8();
	return r;
}
