// cl: /O1 /MD
//
// ??1Rva0056DC6B@@UAE@XZ retail 0x0056DC6B 11B.
// Store vtable 0x0086DB78 then tail-jmp base dtor ??1Rva005248D0@@UAE@XZ.
// Evidence: pin base dtor; vtable store plus jmp; callers include Unwind
// funclets; prev ConstIntGetters TU flags.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva0056DC6B : public Rva005248D0
{
public:
	virtual ~Rva0056DC6B();
};

Rva0056DC6B::~Rva0056DC6B()
{
}
