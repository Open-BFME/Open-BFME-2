// cl: /EHsc /MD
// ??1Rva00567960@@UAE@XZ @0x00567960 60B
// Evidence: MI dtor calls second-base ??1Rva005C7CBB on +8; final store base vtable 0x007C6F20 via empty inline base; caller 0x00567D54 deleting dtor.
class Rva005C7CBB
{
public:
	virtual ~Rva005C7CBB();
};

class Rva00567960Base
{
public:
	virtual ~Rva00567960Base() {}
	int m_4;
};

class Rva00567960 : public Rva00567960Base, public Rva005C7CBB
{
public:
	virtual ~Rva00567960();
};

Rva00567960::~Rva00567960()
{
}
