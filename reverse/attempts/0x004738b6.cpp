// ?rva004738B6@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.82 date=2026-10-10
// Full TU context: Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp (slot-63 override; needs gap63 renamed, gap65 as int-returning, GlobalData m_1230/m_1234, AICommandInterface::rva0026C347, Rva0046A2ECSlot39 view, Rva00468F0FInRange stdcall decl).
void HordeContain::rva004738B6(Object *target)
{
	HordeContain *self = this;
	int remaining = TheWritableGlobalData->m_1230;
	_STL::set<int>::iterator k = self->m_170.begin();
	Object *obj;
	_STL::set<int>::iterator next;
	Rva0046A2ECContain *contain;
	AIUpdateInterface *ai;
	if (k == self->m_170.end())
		return;
	do
	{
		obj = TheGameLogic->findObjectByID((ObjectID)*k);
		next = ++k;
		if (!obj)
			continue;
		if (Rva00468F0FInRange(obj, target) == 1)
		{
			contain = target->m_250;
			if (contain)
				((Rva0046A2ECSlot39 *)contain)->slot39(obj);
			continue;
		}
		if (self->gap65() == 0)
			goto AI_PART;
		if (remaining == 0)
			goto AI_PART;
		if (TheGameLogic->m_frame - self->gap65() <= (unsigned int)TheWritableGlobalData->m_1234)
			goto AI_PART;
		contain = target->m_250;
		if (contain)
			((Rva0046A2ECSlot39 *)contain)->slot39(obj);
		--remaining;
		continue;
	AI_PART:
		ai = obj->m_ai;
		if (!ai)
			continue;
		if (!ai->rva0047306ESlot110())
			continue;
		((AICommandInterface *)((char *)ai + 0x20))->rva0026C347(target, CMD_FROM_AI);
	} while (next != self->m_170.end());
}
