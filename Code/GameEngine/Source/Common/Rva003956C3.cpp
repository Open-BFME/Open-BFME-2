// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?GetArmyIDFromClosestObject@CastleBehavior@@QAEPAXXZ RVA 0x003956C3 size 37 chain via 0x002AB22A rowed plus getControllingPlayer rowed pos at obj+0x38 field at best+0x45c caller 0x00399984.
class Player;
class Object
{
public:
	Player* getControllingPlayer() const;
};
class Player
{
public:
	class Object* findClosestObjectToPosWithValidLivingWorldArmyID(const void* pos) const;
};
class CastleBehavior
{
public:
	void* GetArmyIDFromClosestObject();
private:
	unsigned char m_pad[8];
	Object* m_obj;
};
void* CastleBehavior::GetArmyIDFromClosestObject()
{
	Object* obj = m_obj;
	Player* player = obj->getControllingPlayer();
	Object* best = player->findClosestObjectToPosWithValidLivingWorldArmyID((const void*)((char*)obj + 0x38));
	if (best != 0)
		return *(void**)((char*)best + 0x45c);
	return 0;
}
