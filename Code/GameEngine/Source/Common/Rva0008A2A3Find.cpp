// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?Rva0008A2A3Find@@YAPAVRva0008A2A3Item@@PAXI_N@Z
// retail 0x0008A2A3, 76 bytes, cdecl.
// Walks a map in key order (rowed tree increment 0x00024250) and returns the first value
// whose virtual slot 120 (+0x1E0) mask matches: all bits of the given mask when the flag is
// set, any bit otherwise; null when none matches. Evidence: target bytes and the rowed
// increment; the map's key type and the item/slot names are neutral views.
#include <map>

class Rva0008A2A3Item
{
public:
	virtual void v000() = 0;
	virtual void v001() = 0;
	virtual void v002() = 0;
	virtual void v003() = 0;
	virtual void v004() = 0;
	virtual void v005() = 0;
	virtual void v006() = 0;
	virtual void v007() = 0;
	virtual void v008() = 0;
	virtual void v009() = 0;
	virtual void v010() = 0;
	virtual void v011() = 0;
	virtual void v012() = 0;
	virtual void v013() = 0;
	virtual void v014() = 0;
	virtual void v015() = 0;
	virtual void v016() = 0;
	virtual void v017() = 0;
	virtual void v018() = 0;
	virtual void v019() = 0;
	virtual void v020() = 0;
	virtual void v021() = 0;
	virtual void v022() = 0;
	virtual void v023() = 0;
	virtual void v024() = 0;
	virtual void v025() = 0;
	virtual void v026() = 0;
	virtual void v027() = 0;
	virtual void v028() = 0;
	virtual void v029() = 0;
	virtual void v030() = 0;
	virtual void v031() = 0;
	virtual void v032() = 0;
	virtual void v033() = 0;
	virtual void v034() = 0;
	virtual void v035() = 0;
	virtual void v036() = 0;
	virtual void v037() = 0;
	virtual void v038() = 0;
	virtual void v039() = 0;
	virtual void v040() = 0;
	virtual void v041() = 0;
	virtual void v042() = 0;
	virtual void v043() = 0;
	virtual void v044() = 0;
	virtual void v045() = 0;
	virtual void v046() = 0;
	virtual void v047() = 0;
	virtual void v048() = 0;
	virtual void v049() = 0;
	virtual void v050() = 0;
	virtual void v051() = 0;
	virtual void v052() = 0;
	virtual void v053() = 0;
	virtual void v054() = 0;
	virtual void v055() = 0;
	virtual void v056() = 0;
	virtual void v057() = 0;
	virtual void v058() = 0;
	virtual void v059() = 0;
	virtual void v060() = 0;
	virtual void v061() = 0;
	virtual void v062() = 0;
	virtual void v063() = 0;
	virtual void v064() = 0;
	virtual void v065() = 0;
	virtual void v066() = 0;
	virtual void v067() = 0;
	virtual void v068() = 0;
	virtual void v069() = 0;
	virtual void v070() = 0;
	virtual void v071() = 0;
	virtual void v072() = 0;
	virtual void v073() = 0;
	virtual void v074() = 0;
	virtual void v075() = 0;
	virtual void v076() = 0;
	virtual void v077() = 0;
	virtual void v078() = 0;
	virtual void v079() = 0;
	virtual void v080() = 0;
	virtual void v081() = 0;
	virtual void v082() = 0;
	virtual void v083() = 0;
	virtual void v084() = 0;
	virtual void v085() = 0;
	virtual void v086() = 0;
	virtual void v087() = 0;
	virtual void v088() = 0;
	virtual void v089() = 0;
	virtual void v090() = 0;
	virtual void v091() = 0;
	virtual void v092() = 0;
	virtual void v093() = 0;
	virtual void v094() = 0;
	virtual void v095() = 0;
	virtual void v096() = 0;
	virtual void v097() = 0;
	virtual void v098() = 0;
	virtual void v099() = 0;
	virtual void v100() = 0;
	virtual void v101() = 0;
	virtual void v102() = 0;
	virtual void v103() = 0;
	virtual void v104() = 0;
	virtual void v105() = 0;
	virtual void v106() = 0;
	virtual void v107() = 0;
	virtual void v108() = 0;
	virtual void v109() = 0;
	virtual void v110() = 0;
	virtual void v111() = 0;
	virtual void v112() = 0;
	virtual void v113() = 0;
	virtual void v114() = 0;
	virtual void v115() = 0;
	virtual void v116() = 0;
	virtual void v117() = 0;
	virtual void v118() = 0;
	virtual void v119() = 0;
	virtual unsigned int mask() = 0;
};

typedef _STL::map<int, Rva0008A2A3Item *> Rva0008A2A3Map;

Rva0008A2A3Item *Rva0008A2A3Find(void *mapArg, unsigned int mask, bool all)
{
	Rva0008A2A3Map *items = (Rva0008A2A3Map *)mapArg;
	for (Rva0008A2A3Map::iterator it = items->begin(); it != items->end(); ++it)
	{
		Rva0008A2A3Item *item = it->second;
		if (all)
		{
			if ((item->mask() & mask) == mask)
				return item;
		}
		else if (mask & item->mask())
			return item;
	}
	return 0;
}
