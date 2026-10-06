// cl: /MD
// ??_GRva0040B77E@@QAEPAXI@Z @ 0x0040BA17 (28B). Deleting dtor via rowed dtor 0x0040B77E plus rowed delete 0x0002FD60.
// Evidence: chain lane calls rowed dtor 0x0040B77E; same 28B shape as family QAE deleters.
class Rva0040B77E
{
public:
	~Rva0040B77E();
};
void famgenDelete(Rva0040B77E *p)
{
	delete p;
}
