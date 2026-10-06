// cl: /DNDEBUG /MD
// ?rva000A4826@Rva000A4826@@QAEXMMMMMH@Z retail 0x000A4826 79B.
// Virtual forwarder: calls slot 0xD4 then slot 0xEC with same five floats plus int
// then slot 0x100; x87 fld/fstp spills with EBP frame and ret 0x18.
// Evidence: callees are vtable slots 53/59/64; callers 0x000A4F58 0x000A5617 0x000A5C37;
// neighbour Rva000A4999Get 0x000A4999 same flags.
// ?rva000A47DE@Rva000A4826@@QAEXMMMMH@Z retail 0x000A47DE 72B.
// Sibling forwarder in same class: slot 0xD4 then slot 0xE8 with four floats plus int
// then slot 0x100; same x87 shape with ret 0x14.
// Evidence: caller 0x000A5A99; prev byte getter 0x000A47A7 same neighbourhood.
class Rva000A4826
{
public:
	void rva000A4826(float a, float b, float c, float d, float e, int f);
	void rva000A47DE(float a, float b, float c, float d, int e);
	void rva000A4875(float a, float b, float c, float d, float e, int f);
	void rva000A48C4(int a, float b, float c, float d, float e, float f, int g);
private:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054(); virtual void v055(); virtual void v056(); virtual void v057();
	virtual void v058(float a, float b, float c, float d, int e);
	virtual void v059(float a, float b, float c, float d, float e, int f);
	virtual void v060(float a, float b, float c, float d, float e, int f);
	virtual void v061(int a, float b, float c, float d, float e, float f, int g); virtual void v062(); virtual void v063();
	virtual void v064();
};

void Rva000A4826::rva000A4826(float a, float b, float c, float d, float e, int f)
{
	v053();
	v059(a, b, c, d, e, f);
	v064();
}

void Rva000A4826::rva000A47DE(float a, float b, float c, float d, int e)
{
	v053();
	v058(a, b, c, d, e);
	v064();
}

void Rva000A4826::rva000A4875(float a, float b, float c, float d, float e, int f)
{
	v053();
	v060(a, b, c, d, e, f);
	v064();
}

void Rva000A4826::rva000A48C4(int a, float b, float c, float d, float e, float f, int g)
{
	v053();
	v061(a, b, c, d, e, f, g);
	v064();
}
