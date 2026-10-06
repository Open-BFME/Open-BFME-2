// cl: /DNDEBUG /MD /EHsc
// ??0Rva002A7400@@QAE@XZ @0x002A7400 97B.
// EH ctor zeroing +0/+4 constructing +8 member and initFromStorages with
// two default FixedStorage copies. Evidence: unlock lane, neighbours
// Rva002A73B8Dtor share /O1 layout, callees member ctor/init pin-only and
// FixedStorage copy rowed, __EH_prolog frame, returns this.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	char m_data[28];
};
class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D a, BfmeFixedStorage0004543D b);
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;
class Rva002A7400
{
public:
	Rva002A7400();
private:
	int m_pad0;
	int m_pad4;
	Rva003623E5Member m_member8;
};
Rva002A7400::Rva002A7400() : m_pad0(0), m_pad4(0), m_member8()
{
	m_member8.initFromStorages(g_defaultStorage009FEFA4, g_defaultStorage009FEFA4);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_defaultStorage009FEFA4@@3VBfmeFixedStorage0004543D@@B=?g_00DFEFA4StoragePrototype@@3PAEA")
