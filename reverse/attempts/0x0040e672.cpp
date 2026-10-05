// ?findOrApply@Rva0040E672Host@@QAEHHH@Z
// partial score=0.88 date=2026-10-06
// cl: /O1 /MD
// ?findOrApply@Rva0040E672Host@@QAEHHH@Z @0x0040E672 50B
class Rva0040CB3AIndexedField
{
public:
	int find(int key) const;
};
class Rva0040E672Host : public Rva0040CB3AIndexedField
{
public:
	int findOrApply(int a, int b);
	void apply(int a, int r); // pinned retail 0x0040DD3A
};
int Rva0040E672Host::findOrApply(int a, int b)
{
	volatile int _eh;
	_eh &= 0;
	int r = find(b);
	if (r < 0) {
		*(int *)a = 0;
		return a;
	}
	apply(a, r);
	return a;
}
