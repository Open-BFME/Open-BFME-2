// cl: /MD
// ?rva007401A3@Rva007401A3@@QAEXHH@Z, retail 0x007401A3, 66 bytes.
// Setter caching two ints then notifying via vtable slot 0xB4 with float conversion.
// Evidence: callers 0x00740AAB 0x00740BA7; callee virtual slot 0xB4; uses SSE cvtsi2ss.
class NotifyTarget
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void Notify(void *p, float f, int i);
};
class Rva007401A3
{
public:
	void rva007401A3(int a, int b);
private:
	NotifyTarget *m_p0;
	void *m_p1;
	int m_08;
	int m_0C;
};
void Rva007401A3::rva007401A3(int a, int b)
{
	if (!m_p0)
		return;
	if (!m_p1)
		return;
	if (m_0C == a && m_08 == b)
		return;
	m_08 = b;
	m_0C = a;
	m_p0->Notify(m_p1, (float)a, b);
}
