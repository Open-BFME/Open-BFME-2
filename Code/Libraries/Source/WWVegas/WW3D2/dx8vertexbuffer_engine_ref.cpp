// cl: /G7 /DNDEBUG /MD
//
// VertexBufferClass engine-ref increment/decrement. IndexBufferClass's pair
// at 0x00138770/0x00138780 touches +8; these two retail bodies touch +0x10.

class VertexBufferClass
{
	virtual void _M_slot_00();
	int _M_pad04;
	int _M_pad08;
	int _M_pad0c;
	mutable int engine_refs;

public:
	void Add_Engine_Ref() const;
	void Release_Engine_Ref() const;
};

void VertexBufferClass::Add_Engine_Ref() const
{
	engine_refs++;
}

void VertexBufferClass::Release_Engine_Ref() const
{
	engine_refs--;
}
