// cl: /MD
// ?rva000854CF@Rva000854CF@@QAEPAUOut12@@PAU2@@Z 0x000854CF 29B: thiscall copies 12B at +0x620 (float int int) to out ptr returns out; caller 0x0008ADEA
struct Out12
{
	float a;
	int b;
	int c;
};
class Rva000854CF
{
public:
	char m_pad[0x620];
	Out12 m_620;
	Out12 *rva000854CF(Out12 *out);
};

Out12 *Rva000854CF::rva000854CF(Out12 *out)
{
	Out12 &src = m_620;
	out->a = src.a;
	out->b = src.b;
	out->c = src.c;
	return out;
}
