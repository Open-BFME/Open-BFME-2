// cl: /MD
class Rva0036CA00Str
{
public:
	Rva0036CA00Str();
	~Rva0036CA00Str();
};
class Drawable
{
public:
	void stopAmbientSound();
	Rva0036CA00Str rva0027824D(int selector);
};
class Rva000A8C9B
{
public:
	void clear();
};
class Rva002783F6Host
{
public:
	void rva002783F6(int v);
};
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
class Rva00279354Host
{
public:
	void rva00279354(bool v);
	void setCustomSoundAmbientInfo(const OpaqueRefElement4 &v);
private:
	unsigned char m_pad[0x10C];
	Rva000A8C9B m_10C;
};
// ?rva00279354@Rva00279354Host@@QAEX_N@Z
void Rva00279354Host::rva00279354(bool v)
{
	((Drawable *)this)->stopAmbientSound();
	m_10C.clear();
	if (v != 0)
		((Rva002783F6Host *)this)->rva002783F6(0);
}
void Rva00279354Host::setCustomSoundAmbientInfo(const OpaqueRefElement4 &opaqueRefElement4)
{
	rva00279354(false);
	*(OpaqueRefElement4 *)((char *)this + 0x10C) = opaqueRefElement4;
	((Rva002783F6Host *)this)->rva002783F6(0);
}

class Rva0027937BInner
{
public:
	virtual int v00();
	virtual int v04();
	virtual int v08();
	virtual int v0C();
	virtual int v10();
	virtual int v14();
	virtual int v18();
	virtual int v1C();
	virtual int v20();
};
struct Rva0027937BMid
{
	unsigned char m_pad[0x254];
	Rva0027937BInner *m_254;
};
class Rva0027937BHost
{
public:
	Rva0036CA00Str rva0027937B();
private:
	unsigned char m_pad[0xFC];
	Rva0027937BMid *m_fc;
};
Rva0036CA00Str Rva0027937BHost::rva0027937B()
{
	int selector = 0;
	Rva0027937BMid *mid = m_fc;
	if (mid != 0)
		selector = mid->m_254->v20();
	return ((Drawable *)this)->rva0027824D(selector);
}
