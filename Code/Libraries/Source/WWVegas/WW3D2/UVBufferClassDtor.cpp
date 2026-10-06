// cl: /DNDEBUG /MD
//
// ??1UVBufferClass@@UAE@XZ retail 0x000D2118 5 bytes. UVBuffer empty dtor
// tail-jmps to the rowed ShareBufferClass<Vector2> base dtor at 0x000D1DC8.
// No vptr stores so novtable suppresses the derived store retail lacks.
// Identity is vtable 0x007CE338 of the rowed copy ctor 0x0015D0F0 plus sole
// caller ??_G at 0x000D20FC slot 1. Shape follows ReplaceSelfUpgradeDtor.

class Vector2;

template <class T>
class ShareBufferClass
{
public:
	virtual ~ShareBufferClass();
};

class __declspec(novtable) UVBufferClass : public ShareBufferClass<Vector2>
{
public:
	virtual ~UVBufferClass();
};

UVBufferClass::~UVBufferClass()
{
}
