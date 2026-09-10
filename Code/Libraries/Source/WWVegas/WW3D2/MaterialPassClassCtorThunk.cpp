// cl: /DNDEBUG /MD /EHsc
//
// MaterialPassClass constructor, retail 0x0013EDD0, 104 bytes.
// A refcount base, an array of eight stage wrappers, then four fields.
// The tail is written in retail store order: +0x28, +0x2C, +0x34, then +0x30.

class RefCountClass
{
public:
	RefCountClass() : m_numRefs(1) {}

	virtual ~RefCountClass();

	int m_numRefs;
};

class MaterialPassStage
{
public:
	MaterialPassStage();
	~MaterialPassStage();

private:
	void *m_ptr;
};

class MaterialPassClass : public RefCountClass
{
public:
	MaterialPassClass();

private:
	MaterialPassStage m_stages[8];
	int m_28;
	int m_2c;
	bool m_30;
	int m_34;
};

MaterialPassClass::MaterialPassClass()
{
	m_28 = 0;
	m_2c = 0;
	m_34 = 0;
	m_30 = true;
}
