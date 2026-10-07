// ?insert_unique@?$_Rb_tree@UGen_t_00062fa0_mc4@@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@U?$_Select1st@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@3@U?$less@UGen_t_00062fa0_mc4@@@3@V?$allocator@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@2@@Z
// partial score=0.8 date=2026-10-07
// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -D_BFME_RETAIL_TREE_INSERT_LAYOUT /O1 /arch:SSE /G7 -Ireference/open-bfme-1/game/gen_small
// stlport
// ?_M_insert@?$_Rb_tree@UGen_t_00062fa0_mc4@@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@U?$_Select1st@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@3@U?$less@UGen_t_00062fa0_mc4@@@3@V?$allocator@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@2@0@Z
// retail 0x0028688A, 146 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/gen_small/fam_003.cpp: the donor preamble and this one _Rb_tree
// instantiation, the donor's other containers omitted. The synthetic
// payloads reproduce a layout and a lifecycle, never a class identity.
#include <map>
#include <set>

struct Gen_t_00062fa0_mc4 { int a[1]; Gen_t_00062fa0_mc4(); Gen_t_00062fa0_mc4(const Gen_t_00062fa0_mc4&); ~Gen_t_00062fa0_mc4(); Gen_t_00062fa0_mc4& operator=(const Gen_t_00062fa0_mc4&); int compare(const Gen_t_00062fa0_mc4&) const; bool operator<(const Gen_t_00062fa0_mc4& o) const { return compare(o) < 0; } };
bool operator==(const Gen_t_00062fa0_mc4&, const Gen_t_00062fa0_mc4&);
struct Gen_t_00062fa0_m4cd { int a[1]; Gen_t_00062fa0_m4cd(); Gen_t_00062fa0_m4cd(const Gen_t_00062fa0_m4cd&); ~Gen_t_00062fa0_m4cd(); Gen_t_00062fa0_m4cd& operator=(const Gen_t_00062fa0_m4cd&); };
bool operator==(const Gen_t_00062fa0_m4cd&, const Gen_t_00062fa0_m4cd&);
bool operator<(const Gen_t_00062fa0_m4cd&, const Gen_t_00062fa0_m4cd&);
typedef _STL::pair<const Gen_t_00062fa0_mc4, Gen_t_00062fa0_m4cd > TgPair_tree_mc4_m4cd_00062fa0;

namespace _STL {
typedef _Rb_tree<Gen_t_00062fa0_mc4, TgPair_tree_mc4_m4cd_00062fa0,
	_Select1st<TgPair_tree_mc4_m4cd_00062fa0>, less<Gen_t_00062fa0_mc4>,
	allocator<TgPair_tree_mc4_m4cd_00062fa0> > GenTree_00062fa0;

template <>
pair<GenTree_00062fa0::iterator, bool>
GenTree_00062fa0::insert_unique(const GenTree_00062fa0::value_type &value)
{
	_Link_type x = _M_root();
	_Link_type y = this->_M_header._M_data;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _M_key_compare(_Select1st<TgPair_tree_mc4_m4cd_00062fa0>()(value), _S_key(x));
		x = comp ? _S_left(x) : _S_right(x);
	}
	iterator j = iterator(y);
	if (comp && j == begin())
		return pair<iterator, bool>(_M_insert(y, y, value), true);
	if (comp)
		--j;
	if (_M_key_compare(_S_key(j._M_node), _Select1st<TgPair_tree_mc4_m4cd_00062fa0>()(value)))
		return pair<iterator, bool>(_M_insert(x, y, value), true);
	return pair<iterator, bool>(j, false);
}
}

template class _STL::_Rb_tree<Gen_t_00062fa0_mc4, TgPair_tree_mc4_m4cd_00062fa0, _STL::_Select1st<TgPair_tree_mc4_m4cd_00062fa0 >, _STL::less<Gen_t_00062fa0_mc4 >, _STL::allocator<TgPair_tree_mc4_m4cd_00062fa0 > >;
