// cl: /O1 /DNDEBUG /MD
// ?Rva0033939F@@YAXPBDPAX@Z @0x0033939F 64B.
// Audio token gate: run Rva00339235 then throw INIException when store is not -1.
// Evidence: retail push ebp frame; call 0x00339235 pin with (token; store);
// cmp [esi],-1 je ret else INIException(3, EVA literal, token) + _CxxThrowException;
// caller 0x00339407 FieldParse proc; pin ?Rva0033939F@@YAXPBDPAX@Z.
void Rva00339235(const char *token, void *store);

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

void Rva0033939F(const char *token, void *store)
{
	Rva00339235(token, store);
	if (*(int *)store != -1)
		throw INIException(3, "This is not a valid place to use the EVA: sound syntax: %s", token);
}
