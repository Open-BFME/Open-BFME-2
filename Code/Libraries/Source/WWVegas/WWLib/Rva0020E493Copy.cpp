// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020E493@Rva0020E493@@QAEPAUOut0020E493@@PAU2@@Z, retail 0x0020E493, 23 bytes.
// Eight-byte copy from this+0xB0 (float first via fld/fstp) to out pointer.
// Caller at 0x0020F2C9 uses eax as out pointer.
struct Out0020E493
{
	float m_f;
	int m_i;
};

class Rva0020E493
{
public:
	Out0020E493 *rva0020E493(Out0020E493 *out);

private:
	char m_pad[0xB0];
};

Out0020E493 *Rva0020E493::rva0020E493(Out0020E493 *out)
{
	Out0020E493 *src = (Out0020E493 *)((char *)this + 0xB0);
	out->m_f = src->m_f;
	out->m_i = src->m_i;
	return out;
}
