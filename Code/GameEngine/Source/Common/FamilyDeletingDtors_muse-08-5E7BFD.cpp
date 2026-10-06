// cl: /MD
// ??_GRva005E7529@@QAEPAXI@Z @0x005E7BFD 28B: scalar deleting dtor calls the rowed ??1 at 0x005E7529 plus rowed operator delete 0x0002FD60.
class Rva005E7529 {
public:
	~Rva005E7529();
};

void Rva005E7529_Delete(Rva005E7529 *p) { delete p; }
