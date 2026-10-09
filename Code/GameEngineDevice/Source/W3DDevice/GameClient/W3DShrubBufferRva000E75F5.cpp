// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DShrubBuffer::removeTreeAtIndex, retail 0x000E75F5 (195 bytes, ret 4). Open-BFME-1 twin:
// W3DShrubBuffer_removeTreeAtIndex.cpp (0x0071D020), here in plain form: a tree in the toppling state snaps to its
// upright type (or the toppled type while a push-aside model exists), drops its topple and push-aside models (a
// shrub with none resets the rows that share its key) and leaves the toppling state. BFME2 layout: 2000 records
// of 0xA0 at +0x1958, count +0x4FB58, changed byte +0x4FB5C.
typedef int Int;

class Rva000E75F5RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void);
	virtual void Remove(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

struct Rva000E75F5Tree
{
	unsigned char m_pad00[0x40];
	Int m_treeType;
	unsigned char m_pad44[0x58 - 0x44];
	Int m_key;
	unsigned char m_pad5c[0x84 - 0x5c];
	Int m_state;
	Int m_uprightType;
	Int m_toppledType;
	unsigned char m_pad90[0x94 - 0x90];
	Rva000E75F5RenderObjClass *m_topple;
	Rva000E75F5RenderObjClass *m_pushAside;
	unsigned char m_pad9c[0xa0 - 0x9c];
};

class W3DShrubBuffer
{
public:
	void rva000E75F5(Int index);
	void rva000E70D9(Int key);

private:
	unsigned char m_pad0000[0x1958];
	Rva000E75F5Tree m_trees[2000];
	Int m_numTrees;
	unsigned char m_anythingChanged;
};

void W3DShrubBuffer::rva000E75F5(Int index)
{
	if (index >= m_numTrees)
		return;
	if (m_trees[index].m_treeType < 0)
		return;
	if (m_trees[index].m_state == 1) {
		if (m_trees[index].m_pushAside != 0)
			m_trees[index].m_treeType = m_trees[index].m_toppledType;
	} else {
		m_trees[index].m_treeType = m_trees[index].m_uprightType;
	}
	if (m_trees[index].m_topple != 0) {
		m_trees[index].m_topple->Remove();
		if (m_trees[index].m_topple != 0) {
			m_trees[index].m_topple->Release_Ref();
			m_trees[index].m_topple = 0;
		}
	}
	if (m_trees[index].m_pushAside != 0) {
		m_trees[index].m_pushAside->Remove();
		if (m_trees[index].m_pushAside != 0) {
			m_trees[index].m_pushAside->Release_Ref();
			m_trees[index].m_pushAside = 0;
		}
	} else {
		rva000E70D9(m_trees[index].m_key);
	}
	m_trees[index].m_state = 0;
	m_anythingChanged = true;
}
