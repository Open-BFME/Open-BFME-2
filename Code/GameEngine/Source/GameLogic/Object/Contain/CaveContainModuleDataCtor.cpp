// cl: /O1 /DNDEBUG /MD
//
// ??0CaveContainModuleData@@QAE@XZ, retail 0x00466D37 (25 bytes). Frameless
// ctor over the pinned opaque base (0x465124): clears m_caveIndexData at
// +0x98, then installs the vtable 0x00C43F40. The base is modeled empty
// (declared-only ctor resolving via its pin, EBO size zero) with a flat
// derived class carrying an explicit m_vtable first (GiantBird precedent);
// the and-zero RMW idiom stays ahead of the vtable store under /O1. Field
// identity is the base-call buildFieldParse table 0x00BEEAC8 (CaveIndex at
// +0x98 matches BFME1's CaveContainModuleData member m_caveIndexData at the
// identical offset, vote 1/1). Sole-moduleData-caller is the factory at
// 0x00257714 which news 0x9C; the TimeForFullHeal factory shares this body
// (fold) and that name stays unclaimed.

class OpenContainModuleData
{
public:
	OpenContainModuleData();
};

class CaveContainModuleData : public OpenContainModuleData
{
public:
	CaveContainModuleData();

private:
	void *m_vtable;			// +0x00
	unsigned char m_pad[0x98 - 4];
	int m_caveIndexData;		// +0x98
};

inline CaveContainModuleData::CaveContainModuleData()
{
	m_caveIndexData = 0;
	m_vtable = reinterpret_cast<void *>(0x00C43F40);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCaveContainModuleDataInlineAnchor@@YAXPAVCaveContainModuleData@@@Z absent-from-retail
void _bfmeCaveContainModuleDataInlineAnchor(CaveContainModuleData *p)
{
    p->CaveContainModuleData::CaveContainModuleData();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0HealContainModuleData@@QAE@XZ=??0CaveContainModuleData@@QAE@XZ")
