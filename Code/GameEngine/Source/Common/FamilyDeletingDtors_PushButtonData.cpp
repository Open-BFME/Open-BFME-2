// cl: /MD
// ??_GPushButtonData@@QAEPAXI@Z @0x00328338 28B: scalar deleting dtor calls rowed ??1PushButtonData at 0x00327E50 plus rowed operator delete 0x0002FD60.
// Non-virtual public QAE shape like ??_GRva004F6986 precedent; prev/next PushButtonDataDtor and GadgetButtonSetText.

class PushButtonData { public: ~PushButtonData(); };
void famgenDelete(PushButtonData *p) { delete p; }
