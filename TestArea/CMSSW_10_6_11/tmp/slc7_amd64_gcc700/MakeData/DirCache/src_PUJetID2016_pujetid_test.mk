ALL_COMMONRULES += src_PUJetID2016_pujetid_test
src_PUJetID2016_pujetid_test_parent := PUJetID2016/pujetid
src_PUJetID2016_pujetid_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUJetID2016_pujetid_test,src/PUJetID2016/pujetid/test,TEST))
