// cl: /EHs /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1ReplaceObjectUpdateModuleData@@UAE@XZ, retail 0x004B2C9A, 142 bytes.
//
// Virtual dtor over the ctor TU layout ReplaceObjectUpdateModuleDataCtor.cpp
// (base SpecialAbilityUpdateModuleData 0xC8 via pinned 0x44EB54 ctor, vtable 0x00C56C78, vector
// at +0xC8 via folded Vector_base 0x211E58, float 0.0 at +0xD4, int 0 at
// +0xD8, bool 0 at +0xDC, factory 0x24FCEA news 0xE0). Destroys the +0xC8
// entry-pointer vector: null-tested deletes through the rowed entry dtor
// 0x004B2B2F plus rowed operator delete 0x002FD60, then clears the range
// through the rowed voidptr erase 0x0031BD55, then frees the buffer through
// the rowed _free 0x00030830 inside the inline vector dtor, then the pinned
// base dtor 0x0044ECCE. Called by the audited ??_G at 0x004B2E5D (slot 0 of
// 0x00C56C78). Element type is a TU-local void* stand-in (4-byte pointers
// fold to the voidptr erase; SiegeDocking and WeaponRebuild precedents);
// the delete casts to the rowed entry type. /EHs (not the neighbour's /EHsc)
// is load-bearing: /EHsc omits the retail `mov byte [ebp-4],0` before the
// free (138B), /EHs emits it (142B exact) because extern C free is throwing.

#include <vector>

class Rva004B2B2F
{
public:
	~Rva004B2B2F();
};

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class ReplaceObjectUpdateModuleData : public Rva0044ECCE
{
public:
	virtual ~ReplaceObjectUpdateModuleData();

private:
	_STL::vector<void *> m_vec; // +0xC8
	float m_radius; // +0xD4
	int m_count; // +0xD8
	unsigned char m_flag; // +0xDC
};

ReplaceObjectUpdateModuleData::~ReplaceObjectUpdateModuleData()
{
	for (void **it = m_vec.begin(); it != m_vec.end(); ++it)
	{
		void *entry = *it;
		if (entry != 0)
			delete reinterpret_cast<Rva004B2B2F *>(entry);
	}
	m_vec.clear();
}
