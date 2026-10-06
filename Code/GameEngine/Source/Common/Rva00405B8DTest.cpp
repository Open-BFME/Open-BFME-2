// cl: /EHsc /MD
// ?Rva00405B8DTest@@YG_NPAVObject@@PAUUpgradeRange@@_N@Z @0x00405B8D 119B
// Evidence: leaf free stdcall ret 0xc 3 args; loops UpgradeTemplate* array via range begin/end; +4==1 via rowed Object 0x00290D2B else +4==0 via rowed getControllingPlayer 0x0028AFA9 then rowed Player 0x002AB87D else false; flag at +0x10 selects any vs all; callers 0x0040656F.
class Object;
class UpgradeTemplate
{
public:
	void *m_0;
	int m_4;
};
struct UpgradeRange
{
	UpgradeTemplate **m_begin;
	UpgradeTemplate **m_end;
};
class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *tmpl) const;
};
class Object
{
public:
	bool rva00290D2B(const UpgradeTemplate *tmpl) const;
	Player *getControllingPlayer() const;
};

bool __stdcall Rva00405B8DTest(Object *obj, UpgradeRange *range, bool flag)
{
	for (unsigned int i = 0; i < (unsigned int)(range->m_end - range->m_begin); ++i)
	{
		UpgradeTemplate *tmpl = range->m_begin[i];
		if (!tmpl)
			continue;
		int v = tmpl->m_4;
		bool r;
		if (v == 1)
			r = obj->rva00290D2B(tmpl);
		else if (v == 0)
			r = obj->getControllingPlayer()->rva002AB87D(tmpl);
		else
			return false;
		if (flag)
		{
			if (r)
				return true;
		}
		else
		{
			if (!r)
				return false;
		}
	}
	return flag == 0;
}
