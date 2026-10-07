// cl: /O1 /arch:SSE /G7 /MD

class Rva000A4969
{
public:
	Rva000A4969(void *);
	virtual ~Rva000A4969();
};

// ??0Rva0008FF3E@@QAE@PAX@Z @0x0008FF3E 24B
// Target evidence: called by the adjacent dispatcher; calls rowed
// Rva000A4969 ctor then stores vtable 0x007C7DC8. Class identity is
// address-derived; base relationship is inferred from the constructor call.
class Rva0008FF3E : public Rva000A4969
{
public:
	Rva0008FF3E(void *);
	virtual ~Rva0008FF3E();
};

Rva0008FF3E::Rva0008FF3E(void *argument)
	: Rva000A4969(argument)
{
}
