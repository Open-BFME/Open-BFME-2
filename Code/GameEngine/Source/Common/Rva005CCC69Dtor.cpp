// cl: /MD
// ??1Rva005CCC69@@UAE@XZ retail 0x005CCC69 11B: derived dtor stores vtable 0x00874F24 then tail-jmps to rowed base ??1Rva005CCC07@@UAE@XZ at 0x005CCC07.
// Evidence: mov [ecx] vtable then jmp base shape; caller chain to deleting dtor 0x005CCC98; base landed 0x005CCC07.

class Rva005CCC07
{
public:
	virtual ~Rva005CCC07();
};

class Rva005CCC69 : public Rva005CCC07
{
public:
	virtual ~Rva005CCC69();
};

Rva005CCC69::~Rva005CCC69()
{
}
