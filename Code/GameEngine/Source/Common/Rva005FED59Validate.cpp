// cl: /MD
//
// ?rva005FED59@Rva005FED59@@QBEXXZ @0x005FED59 8B
// Tail-jmp to rowed ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0
// via member at +8. Evidence: add ecx-8 plus jmp, 3 callers,
// prev/next neighbours, honest address name.
template <typename T> class StringBase
{
	friend class Rva005FED59;
	void validate() const;
};

class Rva005FED59
{
public:
	void rva005FED59() const;
private:
	char m_pad00[8];
};

void Rva005FED59::rva005FED59() const
{
	((StringBase<unsigned short> *)((char *)this + 8))->validate();
}
