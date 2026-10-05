// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00578AC1@Rva00578AC1@@QAEXPAX@Z, retail 0x00578AC1, 24 bytes.
// Clears byte at +0x54 then broadcasts callback 0x005CB265 with arg this+4 over list at +8 via forEach 0x00578A60.
// Evidence: packet disassembly, prev forEach row, reverseAnimateWindow row, sibling 0x00578B4C pattern, caller 0x00578B7F.
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
	virtual bool reverseAnimateWindow(AnimateWindow *);
};

class Rva00578AC1
{
public:
	void rva00578AC1(void *arg);
private:
	int m_00;
	int m_04;
	Rva00578A60List m_list08;
	char m_pad18[0x54 - 0x18];
	bool m_flag54;
};

void Rva00578AC1::rva00578AC1(void *unused)
{
	(void)unused;
	m_flag54 = false;
	m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(&ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow), &m_04);
}
