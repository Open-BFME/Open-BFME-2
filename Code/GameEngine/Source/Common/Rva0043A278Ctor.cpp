// cl: /O1 /MD
// ??0Rva0043A278@@QAE@XZ @0x0043A278 18B
// Evidence: leaf ctor calls pinned base ??0Rva00490470 then stores vtable 0x0083D478; caller 0x0023DD9A; neighbours share layout.
class Rva00490470
{
public:
	Rva00490470();
	virtual ~Rva00490470();
};

class Rva0043A278 : public Rva00490470
{
public:
	Rva0043A278();
};

Rva0043A278::Rva0043A278()
{
}
