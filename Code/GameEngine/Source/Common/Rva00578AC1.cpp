// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00578AC1@Rva00578AC1@@QAEXPAX@Z, retail 0x00578AC1, 24 bytes.
// Clears byte at +0x54 then broadcasts callback 0x005CB265 with arg this+4 over list at +8 via forEach 0x00578A60.
// Evidence: packet disassembly, prev forEach row, slot-3 update dispatch thunk, sibling 0x00578B4C pattern, caller 0x00578B7F.
class Rva00578A60Listener
{
public:
	virtual void notify(void *);
};

class Rva00578A60List
{
public:
	void forEach(void (Rva00578A60Listener::*notify)(void *), void *arg);
private:
	Rva00578A60Listener **m_begin;
	Rva00578A60Listener **m_end;
	Rva00578A60Listener **m_capacity;
	unsigned int m_index;
};

class AnimateWindow;
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual ~ProcessAnimateWindowSlideFromBottomTimed();
	virtual void initAnimateWindow(AnimateWindow *);
	virtual void initReverseAnimateWindow(AnimateWindow *, unsigned int);
	virtual bool updateAnimateWindow(AnimateWindow *);
	virtual bool reverseAnimateWindow(AnimateWindow *);
};


class Rva00578AC1
{
public:
	void rva00578AC1(void *arg);
	void rva00578B4C(void *arg);
private:
	int m_00;
	int m_04;
	Rva00578A60List m_list08;
	int m_18;
	Rva00578A60List m_list1C;
	char m_pad2C[0x54 - 0x2C];
	bool m_flag54;
	char m_pad55;
	bool m_flag56;
};

void Rva00578AC1::rva00578AC1(void *unused)
{
	(void)unused;
	m_flag54 = false;
	m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::updateAnimateWindow), &m_04);
}

// ?rva00578B4C@Rva00578AC1@@QAEXPAX@Z, retail 0x00578B4C, 24 bytes.
// Sets byte at +0x56 then broadcasts callback 0x005CB26A with arg this+0x18 over list at +0x1C via forEach 0x00578A60.
// Evidence: packet disassembly, sibling 0x00578AC1 pattern, target slot-4 dispatch thunk, caller 0x00578BD4.
void Rva00578AC1::rva00578B4C(void *unused)
{
	(void)unused;
	m_flag56 = true;
	m_list1C.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), &m_18);
}

// RVA 0x005CB265 is the 5-byte slot-3 dispatch (jmp [vptr+0x0C]);
// taking updateAnimateWindow emits ??_9@$BM@AE rather than slot-0 BA.
// The interface order comes from the reference ProcessAnimateWindow.h and
// the target BottomTimed ctor-installed table at VA 0x00C7481C.
// The adjacent RVA 0x005CB26A dispatches slot 4 (jmp [vptr+0x10]);
// taking reverseAnimateWindow emits its real compiler thunk as well,
// replacing the undefined free-function placeholder and union bit-pun.
