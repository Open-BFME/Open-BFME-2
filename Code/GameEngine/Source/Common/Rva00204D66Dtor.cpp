// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva00204D66@@QAE@XZ @0x00204D66 5B. Dtor tail-jmp to rowed base ??1Rva003B39C7.
// Evidence: 5B jmp to base dtor 0x002045AB; push-dtor for array in 0x00208343.
class Rva003B39C7
{
public:
	~Rva003B39C7();
};
class Rva00204D66 : public Rva003B39C7
{
public:
	~Rva00204D66();
};
Rva00204D66::~Rva00204D66()
{
}
