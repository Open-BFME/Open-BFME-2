// cl: /MD /EHsc
// ??0Rva005F6941@@QAE@XZ, RVA 0x005F6924, 29B. Unlock lane ctor stores vtable plus zeroes.
// Calls: none. Evidence: vtable 0x00879790 at [this] plus zeroes at +4 +8 +0xC +0x10 +0x14 plus byte +0x18, caller 0x005F7776, next dtor 0x005F6941 59B.
class Rva005F6941
{
public:
	virtual ~Rva005F6941();
	Rva005F6941();
private:
	void *m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	bool m18;
};
Rva005F6941::Rva005F6941() : m04(0), m08(0), m0C(0), m10(0), m14(0), m18(false) {}
