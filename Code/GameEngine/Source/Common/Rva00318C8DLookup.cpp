// cl: /DNDEBUG /MD /EHsc
// ?rva00318C8D@Rva00318C8DOwner@@QAEPAVRva0020E89C@@XZ @0x00318C8D 23B: forwards this+0x2c through global g_009FEF10+0xB0 view to rowed 0x0020EAF6; callers 0x002B9FDB 0x0040CCC6.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0020E89C;

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

class Rva002BA8F1Logic
{
public:
	char m_pad00[0xB0];
	Rva0020EAF6View *m_B0;
};

class Rva00318C8DOwner
{
public:
	Rva0020E89C *rva00318C8D();
private:
	char m_pad00[0x2C];
	int m_2c;
};

Rva0020E89C *Rva00318C8DOwner::rva00318C8D()
{
	Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
	Rva0020EAF6View *view = logic->m_B0;
	return view->rva0020EAF6(m_2c);
}
