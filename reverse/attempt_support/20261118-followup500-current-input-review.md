# Current input review

{
  "consumers": 500,
  "private_actual_include_receipts": 2000,
  "distinct_current_opened_headers": 2159,
  "all_source_and_header_hashes_current": true,
  "verified_existing_reference": "f956f041626b7cdedec401bbe55282ccee1a3fe8",
  "reference_rechecked_this_session": false,
  "reason": "Prior successful account verification remains within168h; committed input is unchanged",
  "source_tasks_counted": 0
}

## Upstream header change

{
  "base": "53b35fb75b1069ea45bba5b3a2eefbd979b6b5cf",
  "reviewed_tip": "19ece6b24e3528c3ec821eab0d9778cb3be770d0",
  "headers": {
    "Code/GameEngine/Include/Common/MonitorConditionUpdate.h": {
      "old_sha256": "1b1cf9d86a64350466783f80ad175f37df30884bb62b562d792d015aaf4ec6ee",
      "new_sha256": "869a912407c4275287f12fbeab05db99354d5cb4493f1f1a8af309c3bf146307"
    },
    "Code/GameEngine/Include/GameLogic/Module/BoneFXDamageClass.h": {
      "old_sha256": "4052a199bb22bbb3e723afc71ac28f2f3dd96af39cd519d01dae10fc602155cd",
      "new_sha256": "b4d5793475cf1eb08a72c03e73af5efd08c3dba823456ce047c88c3c0203d195"
    }
  },
  "affected": [
    {
      "source": "Code/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp",
      "batch": 8,
      "opened_headers": [
        "W:\\OpenBFME\\Open-BFME-2\\Code\\GameEngine\\Include\\GameLogic\\Module\\BoneFXDamageClass.h"
      ]
    }
  ],
  "requires_native_reproof": true,
  "reason": "Reviewed new virtual overrides; only StealthDetectorUpdate.cpp opens BoneFXDamageClass.h in all2000 original real include receipts. Full original/candidate native, diagnostic and binding proofs must refresh before publication.",
  "finished": [
    {
      "source": "Code/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp",
      "batch": 8,
      "retained_rows": 22,
      "current_header_hashes_verified": true,
      "source_tasks_added": 0
    }
  ],
  "all_required_proofs_refreshed": true,
  "additional_source_tasks": 0
}

Only StealthDetectorUpdate.cpp opened either changed header in the2000 actual include receipts. Its original and adopted source were both rebuilt through the ordinary native verifier against the new header; full ordinary runtime, complete original type graph, primitive pointer bindings and sizeof witnesses were reverified. The refreshed four private receipts replace only this consumer's earlier proof; the previous proof is preserved locally. All500 current source/header chains pass. This revalidation adds zero source tasks or function/link/runtime credit. The existing reference pin and its successful account verification remain unchanged.
