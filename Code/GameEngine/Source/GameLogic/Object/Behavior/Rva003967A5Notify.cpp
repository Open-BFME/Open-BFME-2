// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /EHsc /MD
//
// ?rva003967A5@@YAXPAVRva003967A5Owner@@HH@Z @0x003967A5 297B: notify every
// template named by the owner's two build lists, range-17 dump lane.
//
// Loop 1 walks the owner's RB-linked node chain (header at +0x68, leftmost at
// +8, advance through the rowed STLport _M_increment at 0x00024250): per node
// the +0x14 name is keyed through TheNameKeyGenerator (0xDF36A4, rowed
// 0x0009FA65), a local BuildListInfo is default-constructed (rowed
// 0x0032A0CE), and TheSidesList (0xE01D58) lookup 0x0032BD25 is driven with
// (key, idx, &info) from idx 0 until it reports false. Each hit copies the
// info's template name through the ICF-shared 0x000AF1DD accessor (called
// through its object-symbol owner Anim2DTemplate::getName; same 27B body,
// AsciiString at this+8) into a temporary, finds the ThingTemplate through
// the rowed 0x002D06CA bucket lookup on TheThingFactory (0xDFF000) and
// notifies it (pinned 0x0033CF34) with the two int args when found. Loop 2
// sweeps the owner's contiguous 8-byte name/payload array at +0x50/+0x54:
// each element is pair-copy-constructed (rowed 0x00466EA7) into a loop temp,
// looked up by its .first the same way, and torn down. /O1 keeps the frame
// in the shared __EH_prolog helper (0x629188) like the neighbouring bodies.
//
// Layout notes: nodes carry the rowed _Rb_tree_node_base link first so the
// _M_increment argument is the node pointer itself, one int, then the name
// at +0x14. BuildListInfo is the 0x80-byte Ctor-TU view (EmptyBase plus the
// explicit vtable slot) with the rowed protected dtor 0x0032A186 declared
// and friended; the ctor/dtor bodies stay out of line.

enum NameKeyType
{
	NK_INVALID = 0
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

namespace _STL
{

typedef bool _Rb_tree_Color_type;

struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair(const pair &);
};

}

struct NoCaseTreeValue4
{
	char m_body[4];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCaseTreePair4;

class Rva003967A5Owner;

void __cdecl rva003967A5(Rva003967A5Owner *owner, int x, int y);

#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class BuildListInfo : public EmptyBase
{
public:
	BuildListInfo();

private:
	AsciiString m_buildingName; // +0x04
	AsciiString m_templateName; // +0x08
	Coord3D m_location; // +0x0C
	Coord2D m_rallyPointOffset; // +0x18
	float m_angle; // +0x20
	bool m_isInitiallyBuilt; // +0x24
	char m_pad25[3]; // +0x25
	unsigned int m_numRebuilds; // +0x28
	BuildListInfo *m_nextBuildList; // +0x2C
	AsciiString m_script; // +0x30
	int m_health; // +0x34
	bool m_whiner; // +0x38
	bool m_unsellable; // +0x39
	bool m_repairable; // +0x3A
	bool m_automaticallyBuild; // +0x3B
	void *m_renderObj; // +0x3C
	void *m_shadowObj; // +0x40
	bool m_selected; // +0x44
	bool m_underConstruction; // +0x45
	bool m_isSupplyBuilding; // +0x46
	bool m_priorityBuild; // +0x47
	int m_objectID; // +0x48
	unsigned int m_objectTimestamp; // +0x4C
	int m_resourceGatherers[10]; // +0x50
	int m_desiredGatherers; // +0x78
	int m_currentGatherers; // +0x7C

protected:
	virtual ~BuildListInfo();
	friend void __cdecl rva003967A5(Rva003967A5Owner *owner, int x, int y);
};

// +0x00 vtable comes from the virtual dtor above (MAE row at 0x0032A186),
// so no explicit slot member here.

typedef char AssertBuildListInfoSize[sizeof(BuildListInfo) == 0x80 ? 1 : -1];
typedef char AssertPairSize[sizeof(NoCaseTreePair4) == 8 ? 1 : -1];

// 0x000AF1DD builds the same 27B AsciiString-at-this+8 copy as the
// dup_000af1dd ICF row and reaches callers through the admitted
// TerrainType::getTexture pin, which is the spelling the REL32 resolver
// knows. Called on the BuildListInfo only for its +0x08 template-name
// member; the pin owner keeps its ZH evidence.
class TerrainType
{
public:
	AsciiString getTexture() const;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

class SidesList
{
public:
	bool rva0032BD25(NameKeyType key, int idx, BuildListInfo *info);
};

extern SidesList *TheSidesList;

class Rva0020AA00Target
{
public:
	void notify(int x, int y);
};

struct Rva003967A5Node
{
	_STL::_Rb_tree_node_base m_link; // +0x00
	int m_x; // +0x10
	AsciiString m_name; // +0x14
};

class Rva003967A5Owner
{
	char m_pad00[0x50]; // +0x00

public:
	NoCaseTreePair4 *m_begin; // +0x50
	NoCaseTreePair4 *m_end; // +0x54
	char m_pad58[0x10]; // +0x58
	_STL::_Rb_tree_node_base *m_header; // +0x68
};

// ?rva003967A5@@YAXPAVRva003967A5Owner@@HH@Z
void __cdecl rva003967A5(Rva003967A5Owner *owner, int x, int y)
{
	Rva003967A5Node *node = (Rva003967A5Node *)owner->m_header->_M_left;
	if (node != (Rva003967A5Node *)owner->m_header) {
		do {
			NameKeyType key = TheNameKeyGenerator->nameToKey(node->m_name);
			{
				int idx = 0;
				BuildListInfo info;
				while (TheSidesList->rva0032BD25(key, idx, &info)) {
					++idx;
					AsciiString hitName(((const TerrainType *)&info)->getTexture());
					void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&hitName);
					if (tmpl != 0)
						((Rva0020AA00Target *)tmpl)->notify(x, y);
				}
			}
			node = (Rva003967A5Node *)_STL::_Rb_global<bool>::_M_increment(&node->m_link);
		} while (node != (Rva003967A5Node *)owner->m_header);
	}
	unsigned int count = (unsigned int)(((char *)owner->m_end - (char *)owner->m_begin) >> 3);
	unsigned int i = 0;
	if (count != 0) {
		do {
			NoCaseTreePair4 tmp(owner->m_begin[i]);
			void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp.first);
			if (tmpl != 0)
				((Rva0020AA00Target *)tmpl)->notify(x, y);
		} while (++i < count);
	}
}
