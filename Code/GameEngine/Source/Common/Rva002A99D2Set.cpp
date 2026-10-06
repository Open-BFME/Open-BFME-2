// cl: /MD
//
// ?rva002A99D2@Rva002A99D2@@QAEXPAX@Z @0x002A99D2 40B
// Evidence: caller 0x002A8104; slot 0 takes int 0 and returns block freed via rowed ??3@YAXPAX@Z; field +0x278 overwritten with incoming arg.
class Rva002A99D2Target
{
public:
	virtual void *v0(int dummy);
};

class Rva002A99D2
{
public:
	void rva002A99D2(void *newVal);
private:
	unsigned char m_pad[0x278];
	Rva002A99D2Target *m_target;
};

void Rva002A99D2::rva002A99D2(void *newVal)
{
	if (m_target != 0)
	{
		void *tmp = m_target->v0(0);
		::operator delete(tmp);
	}
	m_target = (Rva002A99D2Target *)newVal;
}
