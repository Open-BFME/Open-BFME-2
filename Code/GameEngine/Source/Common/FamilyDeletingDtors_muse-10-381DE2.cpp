// cl: /MD
// ??_GRva0054D974@@QAEPAXI@Z at 0x00381DE2 (28B). Scalar deleting dtor calls rowed ??1 at 0x0054D974 plus rowed operator delete 0x0002FD60. Evidence: chain lane all callees rowed.
class Rva0054D974 {
public:
	~Rva0054D974();
};

void Rva0054D974_Delete(Rva0054D974 *p) { delete p; }
