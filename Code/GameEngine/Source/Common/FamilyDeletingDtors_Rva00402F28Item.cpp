// cl: /MD
// ??_GRva00402F28Item@@QAEPAXI@Z @0x00402F55 28B: scalar deleting dtor calls rowed ??1Rva00402F28Item at 0x00402F23 plus rowed operator delete 0x0002FD60.
// Non-virtual public QAE shape like ??_GPushButtonData precedent; gap between ??0Rva00402F28Item and ??1Rva00403055 in Rva00403055CopyCtor.cpp.

class Rva00402F28Item { public: ~Rva00402F28Item(); };
void famgenDelete(Rva00402F28Item *p) { delete p; }
