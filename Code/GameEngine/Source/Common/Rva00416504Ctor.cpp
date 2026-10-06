// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??0Rva00416504@@QAE@PBHABVGen_004E9FD0@@@Z @0x00416504 (29B): int+Gen copy ctor.
// Copies int at +0 via deref of first arg then constructs Gen at +4 via rowed
// copy ctor ??0Gen_004E9FD0@@QAE@ABV0@@Z at 0x00415FAB. Caller at 0x00416C1F.
// Prev _Construct next list _M_create_node.
class Gen_004E9FD0
{
public:
	Gen_004E9FD0(const Gen_004E9FD0 &other);
private:
	char m_data[28];
};

struct Rva00416504
{
	int m_00;
	Gen_004E9FD0 m_gen;
	Rva00416504(const int *a, const Gen_004E9FD0 &b);
};

Rva00416504::Rva00416504(const int *a, const Gen_004E9FD0 &b)
	: m_00(*a), m_gen(b)
{
}
