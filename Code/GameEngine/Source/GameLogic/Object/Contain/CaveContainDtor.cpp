// cl: /DNDEBUG /MD
//
// ??1CaveContain@@MAE@XZ, retail 0x004663B2, 77 bytes.
// CaveContain behavior dtor over the canonical OpenContain base (0xFC).
// Restores the nine OpenContain-path tables at
// +0/+0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34 plus the derived table at
// +0xFC, then tail-jumps to OpenContain's destructor at 0x00464692. The rowed
// pool key at 0x4663FF and the rowed instance factory 0x24B797 (news 0x10C)
// prove the class. The ten vtable immediates resolve through DIR32. Donor is
// ZH CaveContain.

#include "../../../../Include/GameLogic/Module/OpenContain.h"


// The +0xFC interface: retail's table 0x00C43A54 holds CaveContain's
// tryToSetCaveIndex (0x004667D1) in slot 0.
class CaveExtra { public: virtual void tryToSetCaveIndex(int newIndex) = 0; };

class CaveContain : public OpenContain, public CaveExtra
{
public:
	// Retail CaveContain tables 0x00C43CB8 (primary), 0x00C43A70 (+0x20),
	// 0x00C43A6C (+0x28), 0x00C43A5C (+0x34) and 0x00C43A54 (+0xFC): the
	// overrides the ledger rows under CaveContain's name.
	virtual NameKeyType getModuleNameKey() const;			// 0x004663FF
	virtual void recalcApparentControllingPlayer();			// 0x00466977
	virtual void onContaining(Object *obj, bool wasSelected);	// 0x004664BB
	virtual void onRemoving(Object *obj);				// 0x004668DC
	virtual int getContainMax() const;				// 0x0046651C
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool flag);	// 0x004664E1
	virtual void addToContainList(Object *obj);			// 0x0046646E
	virtual void removeFromContain(Object *obj, bool exposeStealthUnits = false);	// 0x004666C9
	virtual void removeAllContained(bool exposeStealthUnits = false);	// 0x00466A50
	virtual void onDie(const DamageInfo *damageInfo);		// 0x00466724
	virtual void onCreate();					// 0x00466780
	virtual void onBuildComplete();					// 0x00466790
	virtual void tryToSetCaveIndex(int newIndex);			// 0x004667D1
protected:
	virtual ~CaveContain();
	virtual void xfer(Xfer *xfer);					// 0x00466577

private:
	unsigned char m_100; // +0x100
	unsigned char m_pad101[3];
	int m_104;
	int m_108;
};

CaveContain::~CaveContain()
{
}

// This unit no longer references the flat-base placeholder destructor, but
// HealContain.cpp's Rva00220240FlatDtor still calls it and links through this
// directive.
#pragma comment(linker, "/alternatename:??1Rva00039D6AFlatBase@@UAE@XZ=??1OpenContain@@UAE@XZ")
