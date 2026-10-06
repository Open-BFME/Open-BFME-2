// cl: /MD
// ??_GRva00448089@@QAEPAXI@Z @0x004480F7 28B: deleting dtor calls rowed ??1 at 0x00448089 then operator delete 0x0002FD60 on flag; public QAE non-virtual so QAEPAXI.
class Rva00448089 {
public:
	~Rva00448089();
};
void Rva00448089_Delete(Rva00448089 *p) { delete p; }
