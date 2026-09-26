// cl: /O1 /MD
// ??_GWinInstanceData@@UAEPAXI@Z @0x00322414
class WinInstanceData { public: __declspec(noinline) virtual ~WinInstanceData(); private: int m_famgen; };
WinInstanceData::~WinInstanceData() { m_famgen = 0; }
void famgenDelete(WinInstanceData *p) { delete p; }
