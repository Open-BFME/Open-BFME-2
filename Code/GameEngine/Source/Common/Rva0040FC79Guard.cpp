// cl: /O1 /MD
// ?guard@Rva0040FC79Host@@QAEXH@Z @0x0040FC79 71B
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual int v48();
	virtual void v49(int v);
};
extern GameWindowManager *TheWindowManager;
extern bool Rva00437EDCGet(void);
class Rva0040FC79Tail
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
};
class Rva0040FC79Host
{
public:
	void guard(int dummy);
private:
	char m_00[0x24];
	Rva0040FC79Tail *m_24;
	unsigned char m_28;
};
void Rva0040FC79Host::guard(int dummy)
{
	if (m_24 == 0)
		return;
	if (m_28 == 0)
		goto tail;
	if (TheWindowManager->v48() != 0)
		goto tail;
	if (Rva00437EDCGet() != 0)
		goto tail;
	TheWindowManager->v49((int)m_24);
tail:
	m_24->v05();
}
