ALL_COMMONRULES += src_PUjetID_pileupJetId_test
src_PUjetID_pileupJetId_test_parent := PUjetID/pileupJetId
src_PUjetID_pileupJetId_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUjetID_pileupJetId_test,src/PUjetID/pileupJetId/test,TEST))
