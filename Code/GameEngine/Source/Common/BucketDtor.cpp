// cl: /O1 /MD
//
// Bucket::~Bucket, retail 0x00148B19, 14 bytes. Dedicated TU so
// NameKeyGenerator.cpp keeps its matched bodies. Sets the vtable then
// tail-calls the AsciiString member destructor at plus 0x0C.

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class Bucket
{
public:
	virtual ~Bucket();

private:
	void *m_nextInSocket;
	int m_key;
	AsciiStringMember m_nameString;
};

Bucket::~Bucket()
{
}
