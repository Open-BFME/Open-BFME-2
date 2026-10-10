// ?rva0046BACD@HordeContain@@UAEXXZ
// partial score=0.97 date=2026-10-10
// Bank for 0x0046BACD (107B, HordeContain +0x20 slot): two-loop walk (pair
// list, then +0x170 set via the +0x150 view) calling Object::rva0029A12B.
// Best shape scores .99: everything exact except loop-1 init stages the
// items pin through eax (`mov eax,[ebp-4]; mov ebx,eax`) where retail loads
// ebx directly (`mov ebx,[ebp-4]`). Tried: plain for over p.m04 (reloads
// end each iter, slot-51 shape), items local (extra mov), empty() guard
// (reshuffles all regs), do/while (same extra mov), same-valued PHI pin
// (fixes the pin but swaps ebx<->edi roles globally: this->ebx, items->edi
// where retail has this->edi, items->ebx). The sister body 0x0046BA56
// (119B) wants exactly the swapped assignment, so this file's shape lands
// there; for 0x0046BACD the mirror (this->edi + direct items->ebx) is open.
// The (items?items:items) PHI + late self assignment is the closest start.
struct HordeContainIface20ViewBacd
{
	unsigned char m_pad00[0x150];
	_STL::set<int> m_ids;
};
void HordeContain::rva0046BACD()
{
	Rva0046247DPair p;
	((Rva0046247D *)((char *)this - 0x20))->rva0046247D(p);
	const _STL::list<Object *> *items = p.m04;
	const _STL::list<Object *> *pin = (items ? items : items);
	for (_STL::list<Object *>::const_iterator it = pin->begin(); it != pin->end(); ++it)
		(*it)->rva0029A12B();
	HordeContainIface20ViewBacd *self = (HordeContainIface20ViewBacd *)this;
	for (_STL::set<int>::iterator k = self->m_ids.begin(); k != self->m_ids.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			obj->rva0029A12B();
	}
}
