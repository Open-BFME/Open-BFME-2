// cl: /DNDEBUG /MD
//
// ?rva002630F5@AIUpdateInterface@@QAEPAVRadarObject@@XZ, retail 0x002630F5, 8 bytes.
// Tail forwarder beside AIUpdateInterface tail: loads m_object at +0x08 then
// tail-jmps to rowed friend_getRadarData 0x00313EAF. Callers at
// 0x34EE32 0x34F082 0x3500C4. Single callee already rowed.

class RadarObject;
class Object
{
public:
	RadarObject *friend_getRadarData();
};

class AIUpdateInterface
{
	char m_pad00[8];
	Object *m_object;
public:
	RadarObject *rva002630F5();
};

RadarObject *AIUpdateInterface::rva002630F5()
{
	return m_object->friend_getRadarData();
}
