// cl: /O2 /MD /DNDEBUG /DWIN32 /D_WINDOWS /EHsc
// stlport
// ?_M_skip_to_next@?$_Hashtable_iterator@U?$pair@$$CBHW4Relationship@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHW4Relationship@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHW4Relationship@@@_STL@@@2@@_STL@@QAEPAU?$_Hashtable_node@U?$pair@$$CBHW4Relationship@@@_STL@@@2@XZ
// retail 0x00620B30..0x00620B6A (59 bytes)
//
// STLport 4.5.3 _Hashtable_iterator::_M_skip_to_next for the
// hash_map<Int, Relationship> that PlayerRelationMap and TeamRelationMap hold.
// The rowed iterator ++ 0x00620E70 (Player.cpp) calls it when a bucket chain
// ends. Retail placed it in the O2 x87 template pool beside the hash_map<int,int>
// members, and its body is /O2 blend code: /O2 /G7 and the /O1 /arch:SSE /G7 of
// Player.cpp's region both emit a body of another size (measured with
// explain_mismatch). It lived in Player.cpp, which therefore had to compile at
// /O2 and emitted /O2 copies of every inline it shares with the rest of
// GameEngine; this unit holds the one /O2 body on its own instead.

#include <hash_map>

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

typedef _STL::pair<const int, Relationship> RelationPair;

template _STL::_Hashtable_node<RelationPair> *
_STL::_Hashtable_iterator<RelationPair, int, _STL::hash<int>, _STL::_Select1st<RelationPair>,
	_STL::equal_to<int>, _STL::allocator<RelationPair> >::_M_skip_to_next();
