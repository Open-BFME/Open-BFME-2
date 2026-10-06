// ?run@Rva0042B038Host@@QAEHHHHH@Z
// partial score=0.875 date=2026-10-06
// cl: /O1 /MD /Oy-
// ?run@Rva0042B038Host@@QAEHHHHH@Z @0x0042B038 48B
extern void **__stdcall Rva00239D02Insert(void **out, void *pos, void **allocArg);
class Rva0042B038Host
{
public:
	int run(int a, int b, int end, int d);
};
int Rva0042B038Host::run(int a, int b, int end, int d)
{
	int cur = b;
	while (cur != end) {
		Rva00239D02Insert((void **)&b, (void *)this, (void **)(cur + 8));
		cur = *(int *)cur;
	}
	return 0;
}
