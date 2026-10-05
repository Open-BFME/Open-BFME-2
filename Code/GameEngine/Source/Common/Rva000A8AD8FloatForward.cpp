// cl: /O1 /MD
// ?rva000A8AD8@Rva000A8AD8@@QAEXM@Z @0x000A8AD8 22B
// ?rva000A8AEE@Rva000A8AEE@@QAEXM@Z @0x000A8AEE 22B
// Null-guarded float forwards through a member pointer: when [this] is null
// the body is just ret 4, else the float argument is passed (via the x87
// fld/fstp stack-slot dance retail uses) to the pinned callee 0x0010FC58 /
// 0x0010FCDB, both unrowed EH factory bodies taking this+float. Owner and
// callee identities are unproven; a third shape twin at 0x00437EC4 proved to
// be a global-dispatch thunk fragment, not a function, and is logged blocked.
class Rva000A8AD8Target
{
public:
	void rva0010FC58(float f);
};

class Rva000A8AD8
{
	Rva000A8AD8Target *m_target;
public:
	void rva000A8AD8(float f);
};

void Rva000A8AD8::rva000A8AD8(float f)
{
	if (!m_target)
		return;
	m_target->rva0010FC58(f);
}

class Rva000A8AEETarget
{
public:
	void rva0010FCDB(float f);
};

class Rva000A8AEE
{
	Rva000A8AEETarget *m_target;
public:
	void rva000A8AEE(float f);
};

void Rva000A8AEE::rva000A8AEE(float f)
{
	if (!m_target)
		return;
	m_target->rva0010FCDB(f);
}
