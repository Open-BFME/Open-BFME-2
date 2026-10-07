// cl: /MD /O1 /arch:SSE /G7
// ?rva0021F797@CreateAHeroManager@@QAEPAVRva0040A3F9@@XZ @0x0021F797 16 bytes.
// Target evidence: calls the CRC routine with the incoming this, then returns
// this + 0x174. Caller declarations identify the manager and return type;
// the CRC routine's same-this call supports its zero-offset base relationship.

class Rva0040A3F9
{
};

class CreateAHeroCRC
{
public:
	void rva0021F47E();
};

class CreateAHeroManager : public CreateAHeroCRC
{
public:
	Rva0040A3F9 *rva0021F797();

private:
	char m_pad001[0x174];
	Rva0040A3F9 m_entries;
};

Rva0040A3F9 *CreateAHeroManager::rva0021F797()
{
	rva0021F47E();
	return &m_entries;
}
