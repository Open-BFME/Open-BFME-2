// cl: /EHsc /MD
// ?Rva005C7889Init@@YAXXZ, retail 0x005C7889 64B.
// Void initializer with function-local static Rva005C7792 (guard plus
// ctor via row 0x005C7792 plus _atexit). Evidence: EH_prolog frame,
// guard byte at VA 0x00E065DC with object at VA 0x00E065D8, ctor row
// ??0Rva005C7792@@QAE@XZ, _atexit row, 8 callers need void init.
class Rva005C7792
{
public:
	Rva005C7792();
	~Rva005C7792();
};

void __cdecl Rva005C7889Init(void)
{
	static Rva005C7792 s;
}
