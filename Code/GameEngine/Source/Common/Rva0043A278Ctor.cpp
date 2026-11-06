// cl: /MD
// ??0Rva0043A278@@QAE@XZ @0x0043A278 18B
// Evidence: leaf ctor calls pinned base ??0Rva00490470 then stores vtable 0x0083D478; caller 0x0023DD9A; neighbours share layout.
class Rva00355D66
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
};

class Rva0043A278 : public Rva00355D66
{
public:
	Rva0043A278();
	// Retail 0x0043A351, defined in AptLoadScreen.cpp; declaring it keeps this unit
	// from emitting a second, implicit copy.
	virtual ~Rva0043A278();
};

Rva0043A278::Rva0043A278()
{
}
