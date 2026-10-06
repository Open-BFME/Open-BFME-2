// ?rva005CCA0B@Rva005CCA0B@@QAEXPAVRva005CC9CB@@@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /MD
// ?rva005CCA0B@Rva005CCA0B@@QAEXPAVRva005CC9CB@@@Z @0x005CCA0B 76B unlock: assign plus inner forwards
// Evidence: calls rowed assign 0x005CC9CB plus forwarders 0x005CB260 0x005CB265 0x000D20D6 plus notifier thunks 0x005CB26F 0x005CB279; prev 0x005CC9F8 next 0x005CCB30.
// ?rva005CCA0B@Rva005CCA0B@@QAEXPAVRva005CC9CB@@@Z present-unmatched
class Rva005CC9CB
{
public:
	void *m_0;
	Rva005CC9CB *rva005CC9CB(Rva005CC9CB *other);
};

class Rva005CB260
{
public:
	void rva005CB260();
	void rva005CB260(int arg);
};
#pragma comment(linker, "/alternatename:?rva005CB260@Rva005CB260@@QAEXH@Z=?rva005CB260@Rva005CB260@@QAEXXZ")

class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual bool reverseAnimateWindow(AnimateWindow *w);
};

class Rva005CB26FThunk
{
public:
	void rva005CB26F(int arg);
};
#pragma comment(linker, "/alternatename:?rva005CB26F@Rva005CB26FThunk@@QAEXH@Z=??_9@$BBE@AE")

class Rva005CB279Thunk
{
public:
	void rva005CB279(int arg);
};
#pragma comment(linker, "/alternatename:?rva005CB279@Rva005CB279Thunk@@QAEXH@Z=??_9@$BBM@AE")

class Rva000D20D6
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08();
	virtual void rva000D20D6();
};

class Rva005CCA0B
{
private:
	unsigned char m_pad0[4];
	Rva005CC9CB m_assign;
	unsigned char m_8[4];
	int m_c;
	unsigned char m_gap[0x21 - 0x10];
	unsigned char m_21;
	unsigned char m_22;
public:
	void rva005CCA0B(Rva005CC9CB *arg);
};

void Rva005CCA0B::rva005CCA0B(Rva005CC9CB *arg)
{
	m_assign.rva005CC9CB(arg);
	((Rva005CB260 *)m_assign.m_0)->rva005CB260((int)this);
	((ProcessAnimateWindowSlideFromBottomTimed *)m_assign.m_0)->ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow((AnimateWindow *)&m_8);
	((Rva005CB26FThunk *)m_assign.m_0)->rva005CB26F(m_c);
	((Rva005CB279Thunk *)m_assign.m_0)->rva005CB279(m_21);
	if (!m_22)
		((Rva000D20D6 *)m_assign.m_0)->Rva000D20D6::rva000D20D6();
}
