// cl: /O1 /DNDEBUG /MD
//
// ?giveSelfUpgrade@UpgradeMux@@QAEXXZ, retail 0x0045230C, 33 bytes.
// UpgradeMux self-upgrade (frameless leaf: four virtual dispatches through
// the +0 vptr at slots 0x30/0x3C/0x28/0x24 with a 1 flag on the last).
// Called on the +0x20 UpgradeMux member by 10 behavior-ctor sites
// (0x4829F4/0x482DF0 plus family); donor ZH ctor tail backs the name.
// Shard (not graft): the UpgradeMux home TU carries the novtable leaf
// ctor, and same-TU virtuals would collide with its explicit vtable.

class UpgradeMux
{
public:
	void giveSelfUpgrade();

private:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09(int flag);
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
};

// ?giveSelfUpgrade@UpgradeMux@@QAEXXZ @0x45230C
void UpgradeMux::giveSelfUpgrade()
{
	slot12();
	slot15();
	slot10();
	slot09(1);
}
