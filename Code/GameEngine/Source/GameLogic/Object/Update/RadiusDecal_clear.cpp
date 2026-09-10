// cl: /O1 /DNDEBUG /MD
//
// RadiusDecal::clear, retail 0x00330DBA, 28 bytes.
// Zero the object pointer at +0, Release the holder at +4 (vtable+8),
// then store 1 in the byte at +8.

class RadiusDecalObject
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void Release();
};

class RadiusDecal
{
	void *_M_unused0;
	RadiusDecalObject *m_object;
	bool m_empty;

public:
	void clear();
};

void RadiusDecal::clear()
{
	RadiusDecalObject *object = m_object;
	_M_unused0 = 0;
	if (object)
		object->Release();
	m_object = 0;
	m_empty = true;
}
