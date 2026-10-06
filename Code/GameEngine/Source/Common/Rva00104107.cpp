// cl: /O1 /MD
// ?rva00104107@Rva00104107@@QAEXXZ retail 0x00104107 8B.
// Evidence: ptr-chase setter *m_ptr=m_val; neighbours Rva0079D070Apply and Rva0010410FWrap; callers Unwind.
class Rva00104107
{
public:
	void rva00104107();
private:
	int *m_ptr;
	int m_val;
};

void Rva00104107::rva00104107()
{
	*m_ptr = m_val;
}
