// cl: /DNDEBUG /MD
//
// HordeAIUpdate's private-command overrides. Slots 13 and 23 of the vftable
// 0x00C505F8 whose slot-2 name getter returns "HordeAIUpdate" replace the
// AIUpdateInterface entries every other AI module keeps there (the rowed
// privateMoveToPosition 0x0026B487 and bfmePrivateCommand42 0x0026D56C);
// each runs the base command only when the owner has the provider at
// Object+0x250 answering slot 31 (the rowed Object::rva0028C197).
//
// ?privateMoveToPosition@HordeAIUpdate@@MAEXPBUCoord3D@@MW4CommandSourceType@@@Z, retail 0x0049A93B, 56 bytes.
// Slot 13 (HordeWorkerAIUpdate 0x00C508C8 inherits it); the provider test
// is inlined.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Rva0028C197Provider
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual void *s31();
};

class Object
{
public:
	__forceinline void *providedEntry() const
	{
		Rva0028C197Provider *provider = m_250;
		return provider ? provider->s31() : 0;
	}
private:
	char m_unrecovered00[0x250];
	Rva0028C197Provider *m_250;
};

class AIUpdateInterface
{
protected:
	virtual void privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource);
	Object *getObject() const { return m_object; }
private:
	void *m_moduleData;
	Object *m_object;
};

class HordeAIUpdate : public AIUpdateInterface
{
protected:
	virtual void privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource);
};

// ?privateMoveToPosition@HordeAIUpdate@@MAEXPBUCoord3D@@MW4CommandSourceType@@@Z @0x0049A93B
void HordeAIUpdate::privateMoveToPosition(const Coord3D *pos, float speed, CommandSourceType cmdSource)
{
	if (getObject()->providedEntry())
		AIUpdateInterface::privateMoveToPosition(pos, speed, cmdSource);
}
