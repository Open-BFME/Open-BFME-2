// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Retail 0x0030E2FE (130B, EH), an EH-prolog start Ghidra never listed, right
// after the rowed bit-flag forwarders 0x0030E2EC / 0x0030E2F5: Zero Hour's
// MapObject::duplicate (WorldHeightMap.cpp) --
//   newInstance(MapObject)(m_location, m_objectName, m_angle, m_flags,
//   &m_properties, m_thingTemplate); setColor(getColor());
//   m_runtimeFlags = m_runtimeFlags; return pObj;
// -- plus BFME2's refresh of the copy (bfmeRunEYE 0x0030DEAE, which the
// flag forwarders also end in). The class is the address-named view of
// Rva0030DBD5Lifecycle.cpp (ctor 0x0030DA25); only the offsets duplicate
// reads are modelled.
// Coord3D is the non-POD retail view (Lib/Coord3DCtorView.h): the by-value position argument is built by three
// dword copies through the user copy constructor, with the EH marker in the frame.
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"

#include "../../Include/Common/Dict.h"

class BfmeNodeEYE
{
public:
	void bfmeRunEYE();
};

class Rva0030DBD5
{
public:
	Rva0030DBD5(Coord3D pos, const AsciiString &name, float angle, int a, const Dict *dictSrc, void *thing);
	virtual ~Rva0030DBD5();
	Rva0030DBD5 *duplicate();

private:
	char m_pad04[4];
	Coord3D m_pos;			// +0x08
	AsciiString m_name;		// +0x14
	void *m_thing;			// +0x18
	float m_angleN;			// +0x1C
	int m_20;
	Dict m_dict;			// +0x24
	int m_28;
	char m_pad2C[0x44 - 0x2C];
	int m_44;
	char m_pad48[0x5C - 0x48];
};

Rva0030DBD5 *Rva0030DBD5::duplicate()
{
	Rva0030DBD5 *copy = new Rva0030DBD5(m_pos, m_name, m_angleN, m_20, &m_dict, m_thing);
	copy->m_28 = m_28;
	copy->m_44 = m_44;
	reinterpret_cast<BfmeNodeEYE *>(copy)->bfmeRunEYE();
	return copy;
}
