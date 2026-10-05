// cl: /O1 /MD
//
// Listener broadcast at retail 0x0041E717 (27B). Walks the pointer range at
// +0x1C/+0x20 and invokes virtual slot 1 on each element through its own
// vtable (indirect call, no pins). Names are address-derived.
class Rva0041E717Listener
{
public:
	virtual void v00() = 0;
	virtual void onNotify() = 0; // slot 1, offset 4
};

class Rva0041E717Broadcast
{
public:
	void notifyAll(); // retail 0x0041E717

private:
	char m_00[0x1C];
	Rva0041E717Listener **m_1C; // +0x1C range begin
	Rva0041E717Listener **m_20; // +0x20 range end
};

void Rva0041E717Broadcast::notifyAll()
{
	for (Rva0041E717Listener **p = m_1C; p != m_20; p++) {
		(*p)->onNotify();
	}
}
