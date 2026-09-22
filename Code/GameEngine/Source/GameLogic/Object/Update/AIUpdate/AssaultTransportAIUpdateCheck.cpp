// cl: /O1 /DNDEBUG /MD
//
// ?Rva0048F61ACheck@AssaultTransportAIUpdate@@QAE_NXZ, retail 0x0048F61A
// (52 bytes). Readiness gate over the +0x41A passenger flags: the +0x08
// object must carry status 0x16 (rowed Object::testStatus) and every flag
// for the +0x43C count must be set. Any failure returns false; the count may
// be zero (vacuous true).

enum ObjectStatusTypes;

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
};

class AssaultTransportAIUpdate
{
public:
	bool Rva0048F61ACheck();

private:
	unsigned char m_pad00[8];
	Object *m_object08;
	unsigned char m_pad0C[0x41A - 0x0C];
	unsigned char m_array41A[10];
	unsigned char m_pad424[0x43C - 0x424];
	int m_count43C;
};

bool AssaultTransportAIUpdate::Rva0048F61ACheck()
{
	if (!m_object08->testStatus((ObjectStatusTypes)0x16))
		return false;
	for (int index = 0; index < m_count43C; ++index)
	{
		if (m_array41A[index] == 0)
			return false;
	}
	return true;
}
