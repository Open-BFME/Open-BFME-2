// cl: /MD
// ??_GRva0041579E@@QAEPAXI@Z @0x00415782 28B chain via rowed ??1Rva0041579E.
// Deleting dtor: calls rowed ??1Rva0041579E then operator delete 0x0002FD60.
// Evidence: call to rowed 0x004156FC at 0x00415785, test [esp+8] 1, call to
// rowed ??3@YAXPAX@Z at 0x00415792. Same shape as FamilyDeletingDtors precedents.
class Rva0041579E
{
public:
	~Rva0041579E();
};
void famgenDelete(Rva0041579E *p)
{
	delete p;
}
