// cl: /O1 /MD

// ??_GFireWeaponCollide@@UAEPAXI@Z @0x4bb806
class FireWeaponCollide { public: __declspec(noinline) virtual ~FireWeaponCollide(); private: int m_famgen; };
FireWeaponCollide::~FireWeaponCollide() { m_famgen = 0; }
void famgenDelete(FireWeaponCollide *p) { delete p; }
