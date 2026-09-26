// cl: /O1 /MD
// ??_GFXListAtBonePosFXNugget@@UAEPAXI@Z @0x001E107A 28B
// Deleting dtor slot 0 of vtable 0x007DD8F4; calls rowed ??1 at 0x001E1096 then rowed operator delete at 0x0002FD60.
class FXListAtBonePosFXNugget { public: __declspec(noinline) virtual ~FXListAtBonePosFXNugget(); private: int m_famgen; };
FXListAtBonePosFXNugget::~FXListAtBonePosFXNugget() { m_famgen = 0; }
void famgenDelete(FXListAtBonePosFXNugget *p) { delete p; }
