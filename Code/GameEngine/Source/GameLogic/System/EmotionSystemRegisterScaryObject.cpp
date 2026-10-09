// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// BF1 clean donor EmotionSystemObjectIDAdd.cpp at 2f243e26d. Target
// WB C94690 independently names RegisterScaryObject; native ObjectID74 and
// scary-object vector24/28/2C. Only that bounded view is claimed here.
#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_prefix[ 0x74 ];
	ObjectID m_id;
};

class EmotionNugget;

class EmotionSystem
{
public:
	void RegisterScaryObject( Object *object );

private:
	unsigned char m_targetPrefix[ 0x24 ];
	_STL::vector<ObjectID> m_objectIDs;
};

void EmotionSystem::RegisterScaryObject( Object *object )
{
	_STL::vector<ObjectID>::iterator iter = m_objectIDs.begin();
	_STL::vector<ObjectID>::iterator end = m_objectIDs.end();
	for( ; iter != end; ++iter )
	{
		if( *iter == object->getID() )
			return;
	}

	m_objectIDs.push_back( object->getID() );
}
