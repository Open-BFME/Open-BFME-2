// cl: /MD
// ?rva0033EF86@Rva0033EEC9@@QAEXPBUCoord3D@@@Z @0x0033EF86 8B forward.
// Retail mov ecx,[ecx+8] then jmp setPosition 0x0030AA80. Evidence: leaf lane;
// neighbours ??1/??_G Rva0033EEC9; rowed Thing::setPosition; load-then-tail
// forward at /O1.
struct Coord3D;
class Thing {
public: void setPosition(const struct Coord3D *pos);
};
class Rva0033EEC9 {
public: void rva0033EF86(const struct Coord3D *pos);
private: char m_pad[8];
         Thing *m_thing;
};
void Rva0033EEC9::rva0033EF86(const struct Coord3D *pos)
{
	m_thing->setPosition(pos);
}
