// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00578AC1@Rva00578AC1@@QAEXPAX@Z, retail 0x00578AC1, 24 bytes.
// Clears byte at +0x54 then broadcasts callback 0x005CB265 with arg this+4 over list at +8 via forEach 0x00578A60.
// Evidence: native callback bytes (mov eax,[ecx]; jmp [eax+0x0C]), prev
// forEach row, sibling 0x00578B4C pattern, and caller 0x00578B7F.
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

// Opaque dispatch view, not the original callback receiver class. Retail's
// five-byte callbacks dispatch slots +0x0C and +0x10 respectively. The earlier
// slots are unknown placeholders; this view is never instantiated and those
// methods are never called. Taking the callback addresses emits the same
// vcall providers used by independently verified notifier siblings.
class Rva005CB265DispatchView
{
public:
	virtual void unknown00();
	virtual void unknown04();
	virtual void unknown08();
	virtual void callback0C(void *);
	virtual void callback10(void *);
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
	m_list08.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(
		&Rva005CB265DispatchView::callback0C), &m_04);
}

// ?rva00578B4C@Rva00578AC1@@QAEXPAX@Z, retail 0x00578B4C, 24 bytes.
// Sets byte at +0x56 then broadcasts callback 0x005CB26A with arg this+0x18 over list at +0x1C via forEach 0x00578A60.
// Evidence: native slot +0x10 forwarder bytes, sibling 0x00578AC1 pattern,
// existing vcall thunk pin, and caller 0x00578BD4.
void Rva00578AC1::rva00578B4C(void *unused)
{
	(void)unused;
	m_flag56 = true;
	m_list1C.forEach(reinterpret_cast<void (Rva00578A60Listener::*)(void *)>(
		&Rva005CB265DispatchView::callback10), &m_18);
}
