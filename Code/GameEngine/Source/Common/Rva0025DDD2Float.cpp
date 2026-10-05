// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva0025DDD2@Rva0025DDD2@@QBEMXZ @0x0025DDD2 46B: float wrapper over
// Transport::rva004D5046. Follows +0x0C to holder then +0x12024 to Transport
// per BFMEConnectionManager layout; null at either step yields 0.0f.
// Evidence: retail mov/test/je chain plus rowed call 0x004D5046 plus
// fstp/xorps/movss/fld tails; owner unproven so honest address name.
class Transport
{
public:
	float rva004D5046() const;
	float rva004D5002() const;
	float rva004D508A() const;
	float rva004D4FBE() const;
	float rva004D4F7A() const;
};

class Rva004D50CE
{
public:
	float rva004D50CE();
};

class BFMEConnectionManager
{
public:
	char m_pad[0x12024];
	Transport *m_transport12024;
};

class Rva0025DDD2
{
	char m_pad0C[0x0C];
	BFMEConnectionManager *m_mgr0C;

public:
	float rva0025DDD2() const;
	float rva0025DDA4() const;
	float rva0025DE00() const;
	float rva0025DD76() const;
	float rva0025DE2E() const;
	float rva0025DD48() const;
};

float Rva0025DDD2::rva0025DDD2() const
{
	volatile float result;
	BFMEConnectionManager *mgr = m_mgr0C;
	Transport *t = 0;
	if (mgr != 0)
		t = mgr->m_transport12024;
	if (t != 0)
		result = t->rva004D5046();
	else
		result = 0.0f;
	return result;
}

float Rva0025DDD2::rva0025DDA4() const
{
	volatile float result;
	BFMEConnectionManager *mgr = m_mgr0C;
	Transport *t = 0;
	if (mgr != 0)
		t = mgr->m_transport12024;
	if (t != 0)
		result = t->rva004D5002();
	else
		result = 0.0f;
	return result;
}

float Rva0025DDD2::rva0025DE00() const
{
	volatile float result;
	BFMEConnectionManager *mgr = m_mgr0C;
	Transport *t = 0;
	if (mgr != 0)
		t = mgr->m_transport12024;
	if (t != 0)
		result = t->rva004D508A();
	else
		result = 0.0f;
	return result;
}

float Rva0025DDD2::rva0025DD76() const
{
	volatile float result;
	BFMEConnectionManager *mgr = m_mgr0C;
	Transport *t = 0;
	if (mgr != 0)
		t = mgr->m_transport12024;
	if (t != 0)
		result = t->rva004D4FBE();
	else
		result = 0.0f;
	return result;
}

float Rva0025DDD2::rva0025DE2E() const
{
	volatile float result;
	BFMEConnectionManager *mgr = m_mgr0C;
	Rva004D50CE *t = 0;
	if (mgr != 0)
		t = (Rva004D50CE *)mgr->m_transport12024;
	if (t != 0)
		result = t->rva004D50CE();
	else
		result = 0.0f;
	return result;
}

float Rva0025DDD2::rva0025DD48() const
{
	volatile float result;
	BFMEConnectionManager *mgr = m_mgr0C;
	Transport *t = 0;
	if (mgr != 0)
		t = mgr->m_transport12024;
	if (t != 0)
		result = t->rva004D4F7A();
	else
		result = 0.0f;
	return result;
}
