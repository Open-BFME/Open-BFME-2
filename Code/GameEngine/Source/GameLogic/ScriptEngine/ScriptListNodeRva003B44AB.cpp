// cl: /O1 /MD /GX-
//
// The 0x14-byte ScriptList node's two constructors (rows 0x003B44AB and
// 0x003B44C7, formerly spelled as methods). Each is called only from a
// new-expression (0x003B805C in 0x003B7FE0 and 0x003B7E89 in 0x003B7E39)
// that keeps the allocation under an EH cleanup state and uses the call's
// eax as the node. Compiled /O1 both are exact matches:
//   ??0Rva003B44AB@@QAE@PBV0@@Z                 retail 0x003B44AB 28B
//   ??0Rva003B44AB@@QAE@PBVRva003529B0@@@Z      retail 0x003B44C7 21B
// Clear +0x00 then copy the Rva003529B0 member at +0x04 from other+0x04 /
// copy the payload into +0x04. Callee ??0Rva003529B0@@QAE@PBV0@@Z rowed.
class Rva003529B0
{
public:
	Rva003529B0(const Rva003529B0 *other);
};

class Rva003B44AB
{
public:
	Rva003B44AB(const Rva003B44AB *other);
	Rva003B44AB(const Rva003529B0 *other);
private:
	Rva003B44AB *m_00;		// +0x00
	Rva003529B0 m_04;		// +0x04
};

Rva003B44AB::Rva003B44AB(const Rva003B44AB *other) : m_00(0), m_04(&other->m_04)
{
}

Rva003B44AB::Rva003B44AB(const Rva003529B0 *other) : m_04(other)
{
}
