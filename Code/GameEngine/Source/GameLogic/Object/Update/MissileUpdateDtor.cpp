// cl: /MD /EHsc
// ??1MissileUpdate@@MAE@XZ @0x004A76DE 84B: restores five vtables then clear 0x4A7512 then pinned base 0x45BF6E; caller 0x4A789C deleting dtor; then 0x4A789C
class Thing;
class ModuleData;
class Rva004A76DEBase0 { public: virtual ~Rva004A76DEBase0(); unsigned char m_pad[8]; };
class Rva004A76DEBase1 { public: virtual ~Rva004A76DEBase1(); };
class Rva004A76DEBase2 { public: virtual ~Rva004A76DEBase2(); unsigned char m_pad[12]; };
class Rva004A76DEBase3 { public: virtual ~Rva004A76DEBase3(); };
class Rva004A76DEBase4 { public: virtual ~Rva004A76DEBase4(); };
class BezierProjectileBehavior : public Rva004A76DEBase0, public Rva004A76DEBase1, public Rva004A76DEBase2, public Rva004A76DEBase3, public Rva004A76DEBase4
{
public:
	virtual ~BezierProjectileBehavior();
protected:
	unsigned char m_pad28[0x88 - 0x28];
};
class MissileUpdate : public BezierProjectileBehavior
{
protected:
	virtual ~MissileUpdate();
public:
	void Rva004A7512Clear();
private:
	int m_88;
	unsigned int m_frame;
	int m_90;
	int m_94;
	int m_98;
	int m_9C;
	unsigned char m_padA0[0x24];
	int m_C4;
	int m_C8;
	unsigned char m_CC;
	unsigned char m_CD;
	unsigned char m_CE;
};
MissileUpdate::~MissileUpdate()
{
	Rva004A7512Clear();
}
