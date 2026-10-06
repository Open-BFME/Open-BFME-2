// cl: /MD
// ??1Rva00437E72@@UAE@XZ @0x00437E72 18B stores vtable g_00C3D294 clears g_Va00E032FC then tail-jmps to base dtor 0x0054D2CF.
// ??_GRva00437E72@@UAEPAXI@Z @0x00437EEE 28B deleting dtor calls ??1 then operator delete on flag.
// Evidence: packet disassembly pair; base dtor pin ??1Rva0054D2CF@@UAE@XZ; vtable g_00C3D294; global g_Va00E032FC.
class Rva0054D2CF
{
public:
	virtual ~Rva0054D2CF();
};

extern const void *const g_00C3D294[];
extern int g_Va00E032FC;

class Rva00437E72 : public Rva0054D2CF
{
public:
	virtual ~Rva00437E72();
};

Rva00437E72::~Rva00437E72()
{
	g_Va00E032FC = 0;
}
