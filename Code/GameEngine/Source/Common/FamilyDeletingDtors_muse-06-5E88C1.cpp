// cl: /MD
// ??_GRva005E888A@@QAEPAXI@Z @0x005E88C1 28B: scalar deleting dtor calls the rowed ??1 at 0x005E888A plus rowed operator delete 0x0002FD60.
class Rva005E888A {
public:
	~Rva005E888A();
};

void Rva005E888A_Delete(Rva005E888A *p) { delete p; }
