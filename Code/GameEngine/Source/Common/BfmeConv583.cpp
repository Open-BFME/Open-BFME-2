class BfmeOwnerCDE
{
public:
	void bfmeOneCDE(void *what);
};

class BfmeThingCDE
{
public:
	void bfmeDtorCDE();
	void bfmeGoCDE();
	void *m_owner;
	void *m_ptr4;
};


void BfmeThingCDE::bfmeGoCDE()
{
	if (m_ptr4 != 0)
	{
		((BfmeOwnerCDE *)m_owner)->bfmeOneCDE(m_ptr4);
		return;
	}
	bfmeDtorCDE();
	::operator delete(this);
}
