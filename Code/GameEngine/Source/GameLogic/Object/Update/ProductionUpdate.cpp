// cl: /O1 /EHsc /MD /arch:SSE
// ProductionUpdate.cpp -- ProductionUpdate members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function
// (vtable pairing); retail supplies the bytes. Zero Hour's
// cancelAndRefundAllProduction loop, which BFME2 brackets with a
// "cancelling everything" flag at +0xFD and runs until the queue is empty;
// unit-type entries (types 1 and 3) cancel through interface slot 10 with the
// production id at +0x10, upgrade entries (type 2) through slot 4 with the
// upgrade at +0x0C. Unknown types stop the loop.

typedef int Int;
typedef bool Bool;

class UpgradeTemplate;

enum ProductionType { PRODUCTION_INVALID = 0, PRODUCTION_UNIT, PRODUCTION_UPGRADE, PRODUCTION_HORDE_UNIT };

struct ProductionEntry
{
	unsigned char m_pad00[4];
	ProductionType m_type;			// +0x04
	unsigned char m_pad08[4];
	const UpgradeTemplate *m_upgradeToResearch;	// +0x0C
	Int m_productionID;			// +0x10
};

class ProductionUpdate
{
public:
	virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
	virtual void cancelUpgrade(const UpgradeTemplate *upgrade);	// +0x10
	virtual void i05(); virtual void i06(); virtual void i07(); virtual void i08();
	virtual void i09();
	virtual void cancelUnitCreate(Int productionID);		// +0x28
	virtual void cancelAndRefundAllProduction();

private:
	unsigned char m_pad04[4];
	ProductionEntry *m_productionQueue;	// +0x08
	unsigned char m_pad0C[0xfd - 0xc];
	Bool m_cancellingAll;			// +0xFD
};

// ProductionUpdate::cancelAndRefundAllProduction, retail 0x0049CE6E.
void ProductionUpdate::cancelAndRefundAllProduction()
{
	m_cancellingAll = true;
	while (m_productionQueue)
	{
		switch (m_productionQueue->m_type)
		{
		case PRODUCTION_UNIT:
		case PRODUCTION_HORDE_UNIT:
			cancelUnitCreate(m_productionQueue->m_productionID);
			continue;
		case PRODUCTION_UPGRADE:
			cancelUpgrade(m_productionQueue->m_upgradeToResearch);
			continue;
		}
		break;
	}
	m_cancellingAll = false;
}
