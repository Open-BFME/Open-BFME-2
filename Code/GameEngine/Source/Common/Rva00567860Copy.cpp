// cl: /MD
// ??0Rva00567860@@QAE@ABV0@@Z @0x00567860 11B
// Evidence: copy ctor stores vtable 0x0086CEB4 returns this ret 4 arg ignored; caller 0x00567CAF.
class Rva00567860
{
public:
	Rva00567860(const Rva00567860 &that);
	virtual void slot00();
};

Rva00567860::Rva00567860(const Rva00567860 &that)
{
}

