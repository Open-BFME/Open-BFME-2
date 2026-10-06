// cl: /MD /EHsc
// ??1Rva001F4D22@@UAE@XZ @ 0x001F4D22 (11B):
// Virtual dtor stores its vtable then tail-jmps to rowed base
// ??1Rva001F4C67@@UAE@XZ. Evidence: mov [ecx] 0xBE174C then jmp 0x1F4C67;
// caller at 0x001F61E8; unblocks 0x001F61E5.
class Rva001F4C67
{
public:
	virtual ~Rva001F4C67();
};
class Rva001F4D22 : public Rva001F4C67
{
public:
	virtual ~Rva001F4D22();
};
Rva001F4D22::~Rva001F4D22()
{
}
