// ?rva00538D17@Rva00538CEF@@QAE_NPAURva00538CEFPair@@@Z
// partial score=0.8 date=2026-10-08
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

struct Rva00538CEFElement
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

struct Rva00538CEFPair
{
	int m_00;
	int m_04;
};

class Rva00538CEF
{
public:
	Rva0020E89C *rva00538CEF();
	bool rva00538D17(Rva00538CEFPair *out);
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

// Retail 0x00538D17, 36 bytes: copies the last element's two dwords at +4 and
// +8 into the out pair; false when the vector is empty. Element size 16.
bool Rva00538CEF::rva00538D17(Rva00538CEFPair *out)
{
	Rva00538CEFElement *begin = (Rva00538CEFElement *)m_start;
	Rva00538CEFElement *end = (Rva00538CEFElement *)m_finish;
	int count = (int)(end - begin);
	if (count == 0)
		return false;
	out->m_00 = end[-1].m_04;
	out->m_04 = end[-1].m_08;
	return true;
}
