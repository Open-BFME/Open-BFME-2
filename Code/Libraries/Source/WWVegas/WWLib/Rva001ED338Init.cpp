// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva001ED338@Rva001ED338@@QAEXPAX@Z @0x001ED338 18B.
// Forwards to rowed INI::initFromINI 0x0002DE78 with the class FieldParse table.
// Evidence: callee rowed 0x0002DE78; table g_00BDF1D8; caller 0x001ED61C in 0x001ED580.
struct FieldParse;
class INI
{
public:
	void initFromINI(void *, const FieldParse *);
};
extern const FieldParse g_00BDF1D8[];
class Rva001ED338
{
public:
	void rva001ED338(void *);
};
void Rva001ED338::rva001ED338(void *ini)
{
	((INI *)ini)->initFromINI(this, g_00BDF1D8);
}
