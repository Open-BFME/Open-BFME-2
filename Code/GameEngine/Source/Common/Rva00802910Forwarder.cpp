// Open-BFME: BFME1 forwarding body transferred for BFME2 verification.

class Rva00802910Interface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void prepare(void) = 0;
};

class Rva007F6740Receiver
{
public:
	typedef __int64 Int64;

	void call(void *context, int a1, int a2, int a3, int a4, int a5,
		int a6, int a7, int a8, const Int64 *int64Parts,
		unsigned int64Count, const char **stringParts,
		unsigned stringCount, int a13, int a14);
};

class Rva00802910Owner : public Rva00802910Interface
{
public:
	void forward(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, const Rva007F6740Receiver::Int64 *int64Parts,
		unsigned int64Count, const char **stringParts,
		unsigned stringCount, int a13, int a14);

private:
	Rva007F6740Receiver *m_receiver;
	void *m_context;
};

void Rva00802910Owner::forward(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, int a8,
	const Rva007F6740Receiver::Int64 *int64Parts, unsigned int64Count,
	const char **stringParts, unsigned stringCount, int a13, int a14)
{
	prepare();
	m_receiver->call(m_context, a1, a2, a3, a4, a5, a6, a7, a8,
		int64Parts, int64Count, stringParts, stringCount, a13, a14);
}
