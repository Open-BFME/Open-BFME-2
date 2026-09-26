// cl: /O1 /MD
// ??_GHordeWorkerAIUpdate@@UAEPAXI@Z @0x0049AD9B
// Deleting dtor slot 0 of vtable 0xC508C8; calls the rowed ??1 at 0x49AC94.
class HordeWorkerAIUpdate { public: __declspec(noinline) virtual ~HordeWorkerAIUpdate(); private: int m_famgen; };
HordeWorkerAIUpdate::~HordeWorkerAIUpdate() { m_famgen = 0; }
void famgenDelete(HordeWorkerAIUpdate *p) { delete p; }
