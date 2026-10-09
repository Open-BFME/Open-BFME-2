// ?rva00286E33@Rva00286214@@QAE?AURva00287B2AResult@@PBVRva00285672@@@Z
// partial score=0.93 date=2026-10-09
// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -D_BFME_RETAIL_TREE_INSERT_LAYOUT /O1 /arch:SSE /G7 -Ireference/open-bfme-1/game/gen_small
// stlport
// ?_M_insert@?$_Rb_tree@UGen_t_00062fa0_mc4@@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@U?$_Select1st@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@3@U?$less@UGen_t_00062fa0_mc4@@@3@V?$allocator@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBUGen_t_00062fa0_mc4@@UGen_t_00062fa0_m4cd@@@2@0@Z
// retail 0x0028688A, 146 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/gen_small/fam_003.cpp: the donor preamble and this one _Rb_tree
// instantiation, the donor's other containers omitted. The synthetic
// payloads reproduce a layout and a lifecycle, never a class identity.
#include <map>
#include <set>

struct Gen_t_00062fa0_mc4 { int a[4]; Gen_t_00062fa0_mc4(); Gen_t_00062fa0_mc4(const Gen_t_00062fa0_mc4&); ~Gen_t_00062fa0_mc4(); Gen_t_00062fa0_mc4& operator=(const Gen_t_00062fa0_mc4&); int compare(const Gen_t_00062fa0_mc4&) const; bool operator<(const Gen_t_00062fa0_mc4& o) const; };
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
GenTree_00062fa0::iterator GenTree_00062fa0::_M_insert(_Base_ptr,_Base_ptr,const value_type &,_Base_ptr);

template <>
__forceinline pair<GenTree_00062fa0::iterator, bool>
GenTree_00062fa0::insert_unique(const GenTree_00062fa0::value_type &value)
{
	_Link_type header = this->_M_header._M_data;
	_Link_type x = static_cast<_Link_type>(header->_M_parent);
	_Link_type y = header;
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = _M_key_compare(_Select1st<TgPair_tree_mc4_m4cd_00062fa0>()(value), _S_key(x));
		x = comp ? _S_left(x) : _S_right(x);
	}
	iterator j = iterator(y);
	if (comp && j == iterator(static_cast<_Link_type>(header->_M_left)))
		return pair<iterator, bool>(_M_insert(y, y, value), true);
	if (comp)
		--j;
	if (_M_key_compare(_S_key(j._M_node), _Select1st<TgPair_tree_mc4_m4cd_00062fa0>()(value)))
		return pair<iterator, bool>(_M_insert(x, y, value), true);
	return pair<iterator, bool>(j, false);
}
}


class Rva00285672;
struct Rva00286214Node;
struct Rva00287B2AResult {
 Rva00287B2AResult(const _STL::GenTree_00062fa0::iterator &p,const bool &value):node(p),inserted(value){}
 _STL::GenTree_00062fa0::iterator node;
 bool inserted;
};
class Rva00286214 {
public: Rva00287B2AResult rva00286E33(const Rva00285672 *value);
};
Rva00287B2AResult Rva00286214::rva00286E33(const Rva00285672 *value) {
 _STL::pair<_STL::GenTree_00062fa0::iterator,bool> result=
 reinterpret_cast<_STL::GenTree_00062fa0 *>(this)->insert_unique(
 *reinterpret_cast<const TgPair_tree_mc4_m4cd_00062fa0 *>(value));
 return Rva00287B2AResult(result.first,result.second);
}
