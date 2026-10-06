// cl: /MD
// ??_GRva00469D86@@QAEPAXI@Z, retail 0x0046AA4D 28B: scalar deleting dtor calls the rowed ??1 at 0x00469D86 plus rowed operator delete 0x0002FD60.
class Rva00469D86 {
public:
	~Rva00469D86();
};

void Rva00469D86_Delete(Rva00469D86 *p) { delete p; }
