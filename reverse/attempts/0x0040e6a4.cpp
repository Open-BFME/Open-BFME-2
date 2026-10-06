// ?findOrApply@Rva0040E6A4Host@@QAEHHH@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD
// ?findOrApply@Rva0040E6A4Host@@QAEHHH@Z @0x0040E6A4 50B. Sibling of 0x0040E672
// (same 50B shape; linear Rva0040C351-equality search 0x0040CB79 instead of
// the binary 0x0040CB3A, same apply 0x0040DD3A). Best-known 0.88: everything
// matches except the prolog `and [ebp-4],0` (retail and 4B before push esi)
// vs volatile `mov [ebp-4],0` (7B, scheduled after). See re_attempts.log.
class Rva0040C351
{
public:
	bool rva0040C3BB(const Rva0040C351 *other);
};
struct Rva0040CB3AEntry
{
	int first;
	int second;
};
class Rva0040CB3AIndexedField
{
public:
	int rva0040CB79(Rva0040C351 *key) const;
private:
	char m_pad[0x40];
	Rva0040CB3AEntry *m_begin;
	Rva0040CB3AEntry *m_end;
};
class Rva0040E6A4Host : public Rva0040CB3AIndexedField
{
public:
	int findOrApply(int a, int b);
	void apply(int a, int r);
};
int Rva0040E6A4Host::findOrApply(int a, int b)
{
	volatile int _eh;
	_eh &= 0;
	int r = rva0040CB79((Rva0040C351 *)b);
	if (r < 0) {
		*(int *)a = 0;
		return a;
	}
	apply(a, r);
	return a;
}
