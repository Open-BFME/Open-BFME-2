// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva003775F7@Rva003775F7@@QAEPAVObject@@XZ @0x003775F7 28B. Null-this guard then getPart double-deref to ObjectID plus TheGameLogic find.
// Evidence: getPart pin 0x0036F710 plus findObjectByID row 0x00049DC5 plus TheGameLogic plus 10 callers in FUN_00777613.
class Object;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
struct BfmePartCDF
{
	ObjectID *m_idPtr;
};
class Rva0018B8B0Arg
{
public:
	BfmePartCDF *getPart();
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Rva003775F7
{
public:
	Object *rva003775F7();
};

Object *Rva003775F7::rva003775F7()
{
	if (this) {
		BfmePartCDF *part = ((Rva0018B8B0Arg *)this)->getPart();
		return TheGameLogic->findObjectByID(*part->m_idPtr);
	}
	return 0;
}
