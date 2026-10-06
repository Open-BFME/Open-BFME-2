// cl: /MD
// ??_GRva0054D8D8@@QAEPAXI@Z at 0x0054D958 (28B). Scalar deleting dtor calls rowed ??1 at 0x0054D8D8 plus rowed operator delete 0x0002FD60. Evidence: chain lane all callees rowed.
class Rva0054D8D8 {
public:
	~Rva0054D8D8();
};

void Rva0054D8D8_Delete(Rva0054D8D8 *p) { delete p; }
