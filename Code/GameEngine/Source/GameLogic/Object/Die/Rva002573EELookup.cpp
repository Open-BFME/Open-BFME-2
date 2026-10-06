// cl: /GX /DNDEBUG /MD
// ?rva002573EE@Rva002573EE@@QAEXHHHW4ModuleType@@ABVAsciiString@@H@Z @0x002573EE 62B
// Fill Pod16 slot from 6 args via decorated name key plus subscript lookup.
// Evidence: chain lane (calls just-landed 0x00257252); caller passes key at
// +0x14 and fills 16B at returned pointer; unblocks 0x000652CA.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};
enum ModuleType
{
	MODULETYPE_FIRST = 0
};
class AsciiString;
struct BfmePod16 { int a[4]; };
class Rva00257252
{
public:
	BfmePod16 &rva00257252(const int &key);
};
class ModuleFactory
{
	friend class Rva002573EE;
protected:
	static NameKeyType makeDecoratedNameKey(const AsciiString &name, ModuleType type);
};
class Rva002573EE
{
public:
	void rva002573EE(int a1, int a2, int a3, ModuleType a4, const AsciiString &a5, int a6);
private:
	char _pad[16];
	Rva00257252 m_holder;
};
void Rva002573EE::rva002573EE(int a1, int a2, int a3, ModuleType a4, const AsciiString &a5, int a6)
{
	int key = ModuleFactory::makeDecoratedNameKey(a5, a4);
	BfmePod16 &slot = m_holder.rva00257252(key);
	slot.a[0] = a1;
	slot.a[1] = a2;
	slot.a[3] = a6;
	slot.a[2] = a3;
}
