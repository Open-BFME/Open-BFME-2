// cl: /Od /GZ

extern "C" int Rva0081B830(void *comm);

class Rva00813E30Obj
{
public:
	char m_lead[0x78];
	void *m_comm;
};

int Rva00813E30Wrap(Rva00813E30Obj *obj)
{
	return Rva0081B830(obj->m_comm);
}
