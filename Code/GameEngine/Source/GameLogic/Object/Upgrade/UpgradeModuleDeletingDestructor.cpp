// cl: /DNDEBUG /MD /EHsc
//
// Protected scalar deleting destructor, RVA 0x00460B50 (28 bytes).
// Slot 0 of the verified UpgradeModule ctor's primary table 0x00842768;
// calls the complete destructor 0x0046089D and operator delete 0x0002FD60.
// Destructor-only declaration and emission anchor follow BFME1's verified
// FireWeaponWhenDeadBehaviorDeletingDestructor.cpp at d6db6bfa4fd3.
// This declaration does not claim an object size or other virtual slots.

class UpgradeModule
{
	friend void forceUpgradeModuleDeletingDestructor();
protected:
	virtual ~UpgradeModule();
};

// ?forceUpgradeModuleDeletingDestructor absent-from-retail
void forceUpgradeModuleDeletingDestructor()
{
	UpgradeModule value;
}
