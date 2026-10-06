// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??0Rva00204612@@QAE@XZ @0x00204612 12B. Ctor wrapper over rowed base ??0Rva003B39C7.
// Evidence: calls base ctor 0x003B39C7, no vptr store, returns this; push-ctor for array in 0x00208343.
class Rva003B39C7
{
public:
	Rva003B39C7();
};
class Rva00204612 : public Rva003B39C7
{
public:
	Rva00204612();
};
Rva00204612::Rva00204612()
{
}
