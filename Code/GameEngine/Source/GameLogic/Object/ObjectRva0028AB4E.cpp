// cl: /O1 /DNDEBUG /MD
// ?rva0028AB4E@Object@@QBEXXZ @0x0028AB4E 39B: Object module scan through +0x244 array via +0x0C sub-object slot 3 then result slot 2.
// Evidence: +0x244 Module** list (ObjectFindModule precedent); +0x0C second-base lea (ObjectRva0028B265 precedent); callers 1; neighbours Object rows.
class Rva0028AB4EResult
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
};
class Rva0028AB4EFace
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual Rva0028AB4EResult *slot03();
};
class BfmeObjectModule
{
public:
	virtual void slot0();
private:
	unsigned int m_data[2];
};
class BehaviorModule : public BfmeObjectModule, public Rva0028AB4EFace
{
};
class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;
public:
	void rva0028AB4E() const;
};
void Object::rva0028AB4E() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028AB4EResult *r = (*m)->slot03();
		if (r != 0)
			r->slot02();
	}
}
