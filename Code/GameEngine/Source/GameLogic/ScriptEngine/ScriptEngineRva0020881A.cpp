// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_NO_EXCEPTIONS /arch:SSE /G7
// stlport
// Native ScriptEngine lookup family: counters, flags, integers and strings.
// Retail 208CF0/208E99 use maps +190DC/+190E8 and defaults -1/0.
// Method names and application container typedefs remain unknown.
// The resolved/original string key and map offsets 190A0/190AC come from
// these complete bodies; parent DoXfer supplies the stored-value accesses.
// Counter field names are carried from the existing ScriptEngine home.
// In particular, the second timer flag's name is a reference lead; the
// target proves its byte initialization, not that name.
#include "ascii_string.h"
#include <map>

// Compare this TU's iterators directly; the generic iterator-base member has
// a different out-of-line copy in the current link order.
namespace _STL {
template<class T,class L,class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L>& a,const _Rb_tree_iterator<T,R>& b) {
 return a._M_node!=b._M_node;
}
}
#include "../../../Include/GameLogic/ScriptCounter.h"
// A script flag's value; DoXfer's frame shows the class-typed default value.
struct ScriptFlag
{
	bool m_value;
	ScriptFlag() : m_value(false) {}
};

typedef _STL::pair<AsciiString,AsciiString> ScriptKey;
class Rva002046C0Owner { public: AsciiString resolveName(const AsciiString &); };
typedef _STL::_Rb_tree<ScriptKey,_STL::pair<const ScriptKey,ScriptCounter>,
 _STL::_Select1st<_STL::pair<const ScriptKey,ScriptCounter> >,_STL::less<ScriptKey>,
 _STL::allocator<_STL::pair<const ScriptKey,ScriptCounter> > > ScriptCounterTree;
typedef _STL::_Rb_tree<ScriptKey,_STL::pair<const ScriptKey,ScriptFlag>,
 _STL::_Select1st<_STL::pair<const ScriptKey,ScriptFlag> >,_STL::less<ScriptKey>,
 _STL::allocator<_STL::pair<const ScriptKey,ScriptFlag> > > ScriptFlagTree;

// The retail trees use the existing byte allocator and omit the throwing
// allocator cleanup wrapper. Node sizes are 0x20 and 0x1C, respectively.
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptCounter@@@2@@Z
template <>
ScriptCounterTree::_Link_type ScriptCounterTree::_M_create_node(const ScriptCounterTree::value_type &value) {
 _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ScriptCounterTree::value_type>),0);
 _STL::_Construct(&node->_M_value_field,value);
 return node;
}
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptFlag@@@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptFlag@@@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptFlag@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptFlag@@@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UScriptFlag@@@2@@Z
template <>
ScriptFlagTree::_Link_type ScriptFlagTree::_M_create_node(const ScriptFlagTree::value_type &value) {
 _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ScriptFlagTree::value_type>),0);
 _STL::_Construct(&node->_M_value_field,value);
 return node;
}

typedef _STL::map<ScriptKey,AsciiString> ScriptStringMap;
typedef _STL::_Rb_tree<ScriptKey,_STL::pair<const ScriptKey,AsciiString>,
 _STL::_Select1st<_STL::pair<const ScriptKey,AsciiString> >,_STL::less<ScriptKey>,
 _STL::allocator<_STL::pair<const ScriptKey,AsciiString> > > ScriptStringTree;
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@VAsciiString@@@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@VAsciiString@@@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@VAsciiString@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@VAsciiString@@@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@VAsciiString@@@2@@Z
template <>
ScriptStringTree::_Link_type ScriptStringTree::_M_create_node(const ScriptStringTree::value_type &value) {
 _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ScriptStringTree::value_type>),0);
 _STL::_Construct(&node->_M_value_field,value);
 return node;
}


struct TeamLess0019B850 : _STL::less<ScriptKey> {};
typedef _STL::map<ScriptKey,int,TeamLess0019B850> ScriptDefaultIntMap;
typedef _STL::_Rb_tree<ScriptKey,_STL::pair<const ScriptKey,int>,
 _STL::_Select1st<_STL::pair<const ScriptKey,int> >,TeamLess0019B850,
 _STL::allocator<_STL::pair<const ScriptKey,int> > > ScriptDefaultIntTree;
typedef ScriptDefaultIntTree::value_type ScriptDefaultIntValue;
// Native205910/45 placement-copy body; original helper identity unknown.
void __cdecl scriptMapConstruct00205910(ScriptDefaultIntValue *where, const ScriptDefaultIntValue &value) {
 ::new ((void *)where) ScriptDefaultIntValue(value);
}
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@@Z
template <>
ScriptDefaultIntTree::_Link_type ScriptDefaultIntTree::_M_create_node(const ScriptDefaultIntTree::value_type &value) {
 _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ScriptDefaultIntTree::value_type>),0);
 scriptMapConstruct00205910(&node->_M_value_field,value);
 return node;
}

// Retail byte-tree node allocation has no allocator cleanup catch path.
// Its existing complete 34-byte node body supports _STLP_NO_EXCEPTIONS here.
typedef _STL::map<AsciiString,unsigned char> ScriptByteMap;

class ScriptEngine {
public:
 void *rva0020881A(AsciiString name);
 void *rva00208DB8(AsciiString name);
 void *rva00208CF0(AsciiString name);
 void *rva00208E99(AsciiString name);
 void rva00209811(const AsciiString &key,unsigned char flag);
protected:
 ScriptCounter *bfmeCounter(AsciiString name);
 bool *bfmeFlagForWrite(AsciiString name);
private:
 char m_unreconstructed[0x190A0];
 _STL::map<ScriptKey,ScriptCounter> m_counters;
 _STL::map<ScriptKey,ScriptFlag> m_flags;
 char m_beforeByteMap[0x190D0 - 0x190B8];
 ScriptByteMap m_byteFlags;
 ScriptDefaultIntMap m_defaults;
 ScriptDefaultIntMap m_otherDefaults;
 ScriptStringMap m_strings;
};
// Retail's complete 207B and 200B lookup-and-insert bodies. The key is the
// resolved script name followed by the original name; the values are the
// target's integer/two-byte counter and Boolean flag, respectively.
ScriptCounter *ScriptEngine::bfmeCounter(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,ScriptCounter>::iterator,bool> result =
  m_counters.insert(_STL::make_pair(key,ScriptCounter()));
 return &result.first->second;
}

bool *ScriptEngine::bfmeFlagForWrite(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,ScriptFlag>::iterator,bool> result =
  m_flags.insert(_STL::make_pair(key,ScriptFlag()));
 return &result.first->second.m_value;
}


void *ScriptEngine::rva0020881A(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::map<ScriptKey,ScriptFlag>::iterator found=m_flags.find(key);
 if(found!=m_flags.end()) return &found->second.m_value;
 return 0;
}

void *ScriptEngine::rva00208DB8(AsciiString name) {
 AsciiString resolved = ((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<_STL::map<ScriptKey,AsciiString>::iterator,bool> result =
  m_strings.insert(_STL::make_pair(key,AsciiString(AsciiString::TheEmptyString)));
 return &result.first->second;
}

void *ScriptEngine::rva00208CF0(AsciiString name) {
 AsciiString resolved=((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<ScriptDefaultIntMap::iterator,bool> result=m_defaults.insert(_STL::make_pair(key,-1));
 return &result.first->second;
}

void *ScriptEngine::rva00208E99(AsciiString name) {
 AsciiString resolved=((Rva002046C0Owner *)this)->resolveName(name);
 ScriptKey key(resolved,name);
 _STL::pair<ScriptDefaultIntMap::iterator,bool> result=m_otherDefaults.insert(_STL::make_pair(key,0));
 return &result.first->second;
}

// Native209811/132: update or insert the byte at node+0x14 in the tree at
// receiver+0x190D0. Its original method name and mapped typedef remain unknown.
// unsigned char expresses the raw one-byte transfer proved by the retail body.
void ScriptEngine::rva00209811(const AsciiString &key,unsigned char flag) {
 ScriptByteMap::iterator found=m_byteFlags.find(key);
 if (found!=m_byteFlags.end()) {
  found->second=flag;
  return;
 }
 m_byteFlags.insert(_STL::make_pair(key,flag));
}
