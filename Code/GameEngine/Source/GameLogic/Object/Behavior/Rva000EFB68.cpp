// cl: /MD
// ?rva000EFB68@Rva000EFB68@@QAEXHHPAX@Z @0x000EFB68 49B: Array slot copy of 12B struct via this plus ((aTimes160 plus b plus 384) times 12). Evidence: linkbody lane abuts prev 0x000EFB5A plus caller 0x000F093D plus imul-lea-imul-add shape.
struct Rva000EFB68Triple { unsigned u00; unsigned u04; unsigned u08; };
class Rva000EFB68
{
public:
	void rva000EFB68(int a, int b, void *src);
};
void Rva000EFB68::rva000EFB68(int a, int b, void *src)
{
	Rva000EFB68Triple *dst = (Rva000EFB68Triple *)((char *)this + ((a * 160 + b + 0x180) * 12));
	Rva000EFB68Triple *s = (Rva000EFB68Triple *)src;
	dst->u00 = s->u00;
	dst->u04 = s->u04;
	dst->u08 = s->u08;
}
