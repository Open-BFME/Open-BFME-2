// cl: /O1 /MD
// Scalar deleting destructor for RemoveUpgradeUpgrade (protected dtor).
// ??_GRemoveUpgradeUpgrade@@MAEPAXI@Z @0x004B7FD5 28B slot 0 of vtable 0x00858E20.
// Needs the ??1 row at 0x004B7F01 to exist.

// ??_GRemoveUpgradeUpgrade@@MAEPAXI@Z @0x004b7fd5
class RemoveUpgradeUpgrade { protected: __declspec(noinline) virtual ~RemoveUpgradeUpgrade(); private: int m_famgen;
  friend void famgenDelete(RemoveUpgradeUpgrade *p); };
RemoveUpgradeUpgrade::~RemoveUpgradeUpgrade() { m_famgen = 0; }
void famgenDelete(RemoveUpgradeUpgrade *p) { delete p; }
