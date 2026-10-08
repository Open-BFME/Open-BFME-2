// cl: /DNDEBUG /MD /EHsc
// ?rva00538CEF@Rva00538CEF@@QAEPAVRva0020E89C@@XZ @0x00538CEF 40B: returns view lookup of last vector element or null.
// Evidence: retail cmp [ecx] [ecx+4] je null then global g_009FEF10 +0xB0 view call rowed 0x0020EAF6 with [edx-4]; callers at 0x31A5FC 0x538D44.

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

class Rva00538CEF
{
public:
	Rva0020E89C *rva00538CEF();
private:
	int *m_start;
	int *m_finish;
};

Rva0020E89C *Rva00538CEF::rva00538CEF()
{
	if (m_start != m_finish) {
		Rva002BA8F1Logic *logic = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
		if (logic) {
			Rva0020EAF6View *view = logic->m_B0;
			if (view)
				return view->rva0020EAF6(m_finish[-1]);
		}
	}
	return 0;
}
