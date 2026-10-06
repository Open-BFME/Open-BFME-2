// cl: /EHsc /MD
//
// ?rva00405A50@Rva00405A50@@QAEXXZ @0x00405A50 (87B):
// Forwards provider TreeHintRef at +0x2A4 to theRadarWindowOverrideSource.
// Evidence: chain lane callee 0x002D36F5 rowed; virtual slot 0xC returning
// TreeHintRef by hidden pointer with EH state 0 then inline holder dtor;
// caller 0x00405D49 passes this in ecx with no stack args; same +0x2A4 as
// big caller 0x00405C04; prev/next share // cl: /O1 /EHsc /MD.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	__forceinline ~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class HintProvider00405A50
{
public:
	virtual void _s00();
	virtual void _s04();
	virtual void _s08();
	virtual TreeHintRef00217D4C GetHint();
};

class RadarWindowOverrideSource
{
public:
	void rva002D36F5(const TreeHintRef00217D4C &hint);
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Rva00405A50
{
public:
	void rva00405A50();
private:
	char m_pad[0x2a4];
	HintProvider00405A50 *m_2a4;
};

void Rva00405A50::rva00405A50()
{
	HintProvider00405A50 *p = m_2a4;
	if (p)
	{
		TreeHintRef00217D4C hint = p->GetHint();
		if (hint.m_ptr)
		{
			if (theRadarWindowOverrideSource)
				theRadarWindowOverrideSource->rva002D36F5(hint);
		}
	}
}
