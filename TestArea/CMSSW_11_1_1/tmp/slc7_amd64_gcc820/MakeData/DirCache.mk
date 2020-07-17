ALL_SUBSYSTEMS+=PUjetID
subdirs_src_PUjetID = src_PUjetID_pileupJetId
ALL_PACKAGES += PUjetID/pileupJetId
subdirs_src_PUjetID_pileupJetId := src_PUjetID_pileupJetId_test src_PUjetID_pileupJetId_plugins
ALL_COMMONRULES += src_PUjetID_pileupJetId_test
src_PUjetID_pileupJetId_test_parent := PUjetID/pileupJetId
src_PUjetID_pileupJetId_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUjetID_pileupJetId_test,src/PUjetID/pileupJetId/test,TEST))
