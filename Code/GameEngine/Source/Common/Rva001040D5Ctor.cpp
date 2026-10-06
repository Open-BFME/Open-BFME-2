// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva001040D5@@QAE@XZ retail 0x001040D5 18B.
// Evidence: calls pinned base 0x00142960 then installs vtable 0x00BCF6F0; neighbours Sub and VslotSmallBodiesAJ.
class Rva00142960Base
{
public:
	Rva00142960Base();
	virtual ~Rva00142960Base();
};

class Rva001040D5 : public Rva00142960Base
{
public:
	Rva001040D5();
	virtual ~Rva001040D5();
};

Rva001040D5::Rva001040D5()
{
}
