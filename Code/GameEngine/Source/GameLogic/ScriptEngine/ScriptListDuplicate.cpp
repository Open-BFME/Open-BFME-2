// cl: /MD /EHsc
//
// ?duplicate@ScriptList@@QBEPAV1@XZ, retail 0x003B8945, 55 bytes.
// ScriptList deep-copy factory (donor BFME1 Scripts.cpp duplicate, same
// mangled name): news 0x4C (ScriptList size from the rowed swap TU at
// 0x003B58DF) through the rowed operator new at 0x0002FDA0 then
// copy-constructs through the pinned copy ctor at 0x003B88DA. Null-checked
// new with EH state 0 to delete on copy throw.
class ScriptList
{
public:
	ScriptList(const ScriptList &other);
	ScriptList *duplicate() const;

private:
	char m_data[0x4C];
};

ScriptList *ScriptList::duplicate() const
{
	return new ScriptList(*this);
}
