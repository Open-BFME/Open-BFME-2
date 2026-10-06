// cl: /MD /GX-
//
// ?rva002AE318@Rva002AE318@@QAEXXZ @0x002AE318 17B.
// Calls rowed Rva00380200::rva0038028B on this then tail-jmps to rowed
// Player::rva002AE252 on this-8. Evidence: rowed callees, caller at 0x002AFC01,
// neighbours in PlayerRva002AE252.cpp. Owner unproven so honest address name.
class Rva00380200
{
public:
	void rva0038028B();
};

class Player
{
public:
	void rva002AE252();
};

class Rva002AE318
{
public:
	void rva002AE318();
};

void Rva002AE318::rva002AE318()
{
	((Rva00380200 *)this)->rva0038028B();
	((Player *)((char *)this - 8))->rva002AE252();
}
