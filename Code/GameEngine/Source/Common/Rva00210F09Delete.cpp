// cl: /DNDEBUG /MD /EHsc
// ?rva00210F09@Rva00210EF1@@UAEXXZ @0x00210F09 30B slot 1 of vtable 0x007E5118 class of ??0Rva00210EF1@@QAE@H@Z validates as StringBase<G> then virtual slot0(0) result deleted via rowed operator delete. Evidence: packet disasm call validate 0x000B3FD0 rowed plus indirect slot0 with int 0 plus ??3@YAXPAX@Z rowed.
template <typename T> class StringBase
{
	friend class Rva00210EF1;
	void validate() const;
};

class Rva003FAE68Base
{
public:
	virtual void *virt0(int v);
};

class Rva00210EF1 : public Rva003FAE68Base
{
public:
	virtual void rva00210F09();
};

void __cdecl operator delete(void *p);

void Rva00210EF1::rva00210F09()
{
	((StringBase<unsigned short> *)this)->validate();
	void *p = 0;
	if (this != 0)
		p = this->virt0(0);
	::operator delete(p);
}
