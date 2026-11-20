# Reproof after independent upstream alias retirement

{
  "source": "Code/GameEngine/Source/Common/BfmeConv908.cpp",
  "bank": 17,
  "upstream_commit": "7b45533945b0ee31bf2e5b0bc51f3eb0cd0b40d6",
  "original_initial_source_sha256": "e80235893ac04a38ccf1fb4a80b0d26695b8869f23fca7687ec74df2811a7af5",
  "old_local_candidate_sha256": "668373cd4e9fa29c43a23714b1f150cee3bf314a5969fd430f3a3d32a1515045",
  "upstream_source_sha256": "dc7570d11025ba8f7f3402bd5340f49c3ccf64679eee526588c01374691d5ba9",
  "merged_source_sha256": "1d90313c19a658d1de2ac4f43b45a34a6e923cb2bcb907f8287b797ad5ee364c",
  "only_reviewed_foreign_edits": true,
  "foreign_and_own_edits_commute": true,
  "own_declaration_targets": [
    "bfmeOneRB",
    "bfmeTwoRB",
    "bfmeGoRB"
  ],
  "foreign_edits": "Exactly four reviewed existing alternatename directives removed upstream; no body, flag or type edit. Own cleanup removes the same three unused void prototypes and commutes exactly.",
  "task_credit": 0,
  "new_semantic_identity": false,
  "ordinary_runtime_and_full_type_graph_retained_against_upstream": true,
  "claimed_file_lease": "2e6bdeeb284f414baff10645dd503c8b"
}

Upstream removes exactly four existing alternatename directives. Our same three unused void prototypes are disjoint, and both edit orders produce exactly the same candidate. Ordinary native before/after gates, full ordinary code/data/relocations/directives/weak/COMDAT inventories, complete native type graphs, private pointer-environment control and all four actual input receipts pass again at the real source filename. The source snapshot override records provenance only; no Retail baseline, pin, alias admission, row identity or native check is changed. All other499 source operations and all opened header hashes stay unchanged. The66 incoming source files also pass545/545 native rows. This integration reproof counts zero extra tasks and gives zero new function, linked-byte or runtime credit.
