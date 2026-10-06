// cl: /MD
// ?rva00406E47@Rva00406E47@@QAE_NH@Z @0x00406E47 12B: thiscall setter storing stack arg to +4 and returning true. Callers 0x0021A447 and 0x005B1E9E. Owner unknown so honest-address name.
class Rva00406E47
{
	int m_00;
	int m_04;
public:
	bool rva00406E47(int v);
};
bool Rva00406E47::rva00406E47(int v)
{
	m_04 = v;
	return true;
}
