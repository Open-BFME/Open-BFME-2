// cl: /O1 /MD
// ?rva005EE250@Rva005EE250@@QAEXH@Z @0x005EE250 8B
// Ticker delegate: forwards to rowed setPlayerCountRva005EE11E through the
// pointer at +4. Evidence: mov ecx,[ecx+4] plus tail-jmp to rowed 0x005EE11E,
// caller 0x005D13F6.
class Rva005EE11EPlayerCount
{
public:
	void setPlayerCountRva005EE11E(int count);
};

class Rva005EE250
{
public:
	void rva005EE250(int count);
private:
	char m_pad[4];
	Rva005EE11EPlayerCount *m_04;	// +4
};

void Rva005EE250::rva005EE250(int count)
{
	return m_04->setPlayerCountRva005EE11E(count);
}
