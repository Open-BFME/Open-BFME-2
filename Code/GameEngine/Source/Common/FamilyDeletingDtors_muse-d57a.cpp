// cl: /O1 /MD
// ??_GQueueProductionExitUpdate@@MAEPAXI@Z @0x004A0178
// Deleting dtor slot 0 of vtable 0x008519C8; calls the rowed ??1 at 0x0049FFF7.
class QueueProductionExitUpdate { protected: __declspec(noinline) virtual ~QueueProductionExitUpdate(); private: int m_famgen;
  friend void famgenDelete(QueueProductionExitUpdate *p); };
QueueProductionExitUpdate::~QueueProductionExitUpdate() { m_famgen = 0; }
void famgenDelete(QueueProductionExitUpdate *p) { delete p; }
