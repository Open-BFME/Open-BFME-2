// cl: /O1 /MD
// ??_GQueueProductionExitUpdate@@MAEPAXI@Z @0x004A0178
// Deleting dtor slot 0 of vtable 0x008519C8; calls the rowed ??1 at 0x0049FFF7.
class QueueProductionExitUpdate { protected: __declspec(noinline) virtual ~QueueProductionExitUpdate(); private: int m_famgen;
  friend void famgenDelete(QueueProductionExitUpdate *p); };
QueueProductionExitUpdate::~QueueProductionExitUpdate() { m_famgen = 0; }
void famgenDelete(QueueProductionExitUpdate *p) { delete p; }

// ??_GCommandPointsUpgrade@@UAEPAXI@Z @0x004B8692
// Deleting dtor slot 0 of vtable 0x008590A8; calls the rowed ??1 at 0x004B85D4.
class CommandPointsUpgrade { public: __declspec(noinline) virtual ~CommandPointsUpgrade(); private: int m_famgen; };
CommandPointsUpgrade::~CommandPointsUpgrade() { m_famgen = 0; }
void famgenDelete(CommandPointsUpgrade *p) { delete p; }
