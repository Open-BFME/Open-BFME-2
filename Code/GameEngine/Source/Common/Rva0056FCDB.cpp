// cl: /O1 /arch:SSE /G7 /Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva0056FCDB@Rva0056FCDB@@QAEXF@Z @0x0056FCDB 24B. Address-derived class and method; call target and field store are packet evidence.
int Rva0056F690Hook(int, int);

class Rva0056FCDB
{
public:
	void rva0056FCDB(short value);
	int m_unknown;
	int m_value;
};

void Rva0056FCDB::rva0056FCDB(short value)
{
	m_value = Rva0056F690Hook(value, value);
}
