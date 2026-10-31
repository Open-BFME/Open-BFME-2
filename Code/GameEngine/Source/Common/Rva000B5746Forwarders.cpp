// cl: /MD
// Four 8-byte forwarders at 0x000B5746, 0x000B574E, 0x000B5756 and
// 0x000B575E: each loads the object pointer at +4 and tail-jumps, with the
// caller's one stack argument, into a rowed lookup of the condition-state
// table in Rva000B4BED.cpp: ?rva000B4B23 (ModelConditionFlags query),
// ?rva000B4BED, ?rva000B4C9D and ?rva000B4CBE (opaque entry pointer). The
// four sit in the W3DModelDraw run ahead of 0x000B5766; no direct caller
// reaches them in retail, so the owner and names stay address-derived.
class ModelConditionFlags;

class Rva000B4B23
{
public:
	void *rva000B4B23(const ModelConditionFlags &query);
};

class Rva000B4BED
{
public:
	void *rva000B4BED(const void *query);
	void *rva000B4C9D(const void *entry);
	void *rva000B4CBE(const void *entry);
};

class Rva000B5746
{
public:
	void *rva000B5746(const ModelConditionFlags &query);
	void *rva000B574E(const void *query);
	void *rva000B5756(const void *entry);
	void *rva000B575E(const void *entry);
private:
	void *m_00;
	void *m_conditionStates;	// the condition-state table
};

void *Rva000B5746::rva000B5746(const ModelConditionFlags &query)
{
	return ((Rva000B4B23 *)m_conditionStates)->rva000B4B23(query);
}

void *Rva000B5746::rva000B574E(const void *query)
{
	return ((Rva000B4BED *)m_conditionStates)->rva000B4BED(query);
}

void *Rva000B5746::rva000B5756(const void *entry)
{
	return ((Rva000B4BED *)m_conditionStates)->rva000B4C9D(entry);
}

void *Rva000B5746::rva000B575E(const void *entry)
{
	return ((Rva000B4BED *)m_conditionStates)->rva000B4CBE(entry);
}
