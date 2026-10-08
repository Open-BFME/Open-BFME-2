// cl: /Ob0
//
// 0x0061EDA0 neighbourhood cluster.  The body carries a BFME1 donor identity
// (reference/open-bfme-1/game/Libraries/Source/assetmanager/assetmanager_base.cpp
// bfmeAdvanceStages), but the BFME2 tail diverges (it deletes the bfmeStage7(0)
// result). WorldBuilder names the body AssetFactoryBase::Delete
// (assetmanager_base.cpp:37 assert); it is a virtual, slot 8 of 18 retail
// vtables of AssetFactoryBase-derived factories that inherit it, as its WB
// twin is slot 8 of the matching WB tables.

class AssetFactoryBase
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void bfmeSlot08();
	virtual void bfmeSlot0C();
	virtual void bfmeSlot10();
	virtual void bfmeStage4();
	virtual void bfmeStage5();
	virtual void bfmeStage6();
	virtual void Delete();
	virtual void *bfmeStage7(unsigned int finalStage);
	virtual bool bfmeCanAdvanceStages();

private:
	volatile unsigned int m_flags;
};

// ?Delete@AssetFactoryBase@@UAEXXZ
void AssetFactoryBase::Delete()
{
	if (bfmeCanAdvanceStages()) {
		m_flags = (m_flags & 0xFF04FFFF) | 0x00040000;
		bfmeStage4();
		m_flags = (m_flags & 0xFF05FFFF) | 0x00050000;
		bfmeStage5();
		m_flags = (m_flags & 0xFF06FFFF) | 0x00060000;
		bfmeStage6();
		m_flags = (m_flags & 0xFF07FFFF) | 0x00070000;
	}
	operator delete(bfmeStage7(0));
}
