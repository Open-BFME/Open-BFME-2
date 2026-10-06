// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva0046D733@@QAE@XZ @0x0046D733 5B novtable empty dtor over rowed base 0x0046AB1B
// Evidence: 5B jmp to ??1Rva0046A93E row; prev next HordeContain same TU; caller Unwind
class Rva0046A93E {
public:
	~Rva0046A93E();
};
class __declspec(novtable) Rva0046D733 : public Rva0046A93E {
public:
	~Rva0046D733();
};
Rva0046D733::~Rva0046D733() {}
