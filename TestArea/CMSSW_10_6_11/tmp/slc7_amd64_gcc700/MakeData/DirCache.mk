ALL_SUBSYSTEMS+=RecoJets
subdirs_src_RecoJets = src_RecoJets_JetProducers
ALL_PACKAGES += RecoJets/JetProducers
subdirs_src_RecoJets_JetProducers := src_RecoJets_JetProducers_data src_RecoJets_JetProducers_doc src_RecoJets_JetProducers_interface src_RecoJets_JetProducers_plugins src_RecoJets_JetProducers_python src_RecoJets_JetProducers_src src_RecoJets_JetProducers_test
ifeq ($(strip $(PyRecoJetsJetProducers)),)
PyRecoJetsJetProducers := self/src/RecoJets/JetProducers/python
src_RecoJets_JetProducers_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/RecoJets/JetProducers/python)
PyRecoJetsJetProducers_files := $(patsubst src/RecoJets/JetProducers/python/%,%,$(wildcard $(foreach dir,src/RecoJets/JetProducers/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyRecoJetsJetProducers_LOC_USE := self  
PyRecoJetsJetProducers_PACKAGE := self/src/RecoJets/JetProducers/python
ALL_PRODS += PyRecoJetsJetProducers
PyRecoJetsJetProducers_INIT_FUNC        += $$(eval $$(call PythonProduct,PyRecoJetsJetProducers,src/RecoJets/JetProducers/python,src_RecoJets_JetProducers_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyRecoJetsJetProducers,src/RecoJets/JetProducers/python))
endif
ALL_COMMONRULES += src_RecoJets_JetProducers_python
src_RecoJets_JetProducers_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_python,src/RecoJets/JetProducers/python,PYTHON))
ALL_COMMONRULES += src_RecoJets_JetProducers_test
src_RecoJets_JetProducers_test_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_test,src/RecoJets/JetProducers/test,TEST))
ALL_SUBSYSTEMS+=PUJetID2016
subdirs_src_PUJetID2016 = src_PUJetID2016_pujetid
ALL_PACKAGES += PUJetID2016/pujetid
subdirs_src_PUJetID2016_pujetid := src_PUJetID2016_pujetid_plugins src_PUJetID2016_pujetid_python src_PUJetID2016_pujetid_test
ifeq ($(strip $(PyPUJetID2016pujetid)),)
PyPUJetID2016pujetid := self/src/PUJetID2016/pujetid/python
src_PUJetID2016_pujetid_python_parent := 
ALL_PYTHON_DIRS += $(patsubst src/%,%,src/PUJetID2016/pujetid/python)
PyPUJetID2016pujetid_files := $(patsubst src/PUJetID2016/pujetid/python/%,%,$(wildcard $(foreach dir,src/PUJetID2016/pujetid/python ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PyPUJetID2016pujetid_LOC_USE := self  
PyPUJetID2016pujetid_PACKAGE := self/src/PUJetID2016/pujetid/python
ALL_PRODS += PyPUJetID2016pujetid
PyPUJetID2016pujetid_INIT_FUNC        += $$(eval $$(call PythonProduct,PyPUJetID2016pujetid,src/PUJetID2016/pujetid/python,src_PUJetID2016_pujetid_python,1,1,$(SCRAMSTORENAME_PYTHON),$(SCRAMSTORENAME_LIB),,))
else
$(eval $(call MultipleWarningMsg,PyPUJetID2016pujetid,src/PUJetID2016/pujetid/python))
endif
ALL_COMMONRULES += src_PUJetID2016_pujetid_python
src_PUJetID2016_pujetid_python_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUJetID2016_pujetid_python,src/PUJetID2016/pujetid/python,PYTHON))
ALL_COMMONRULES += src_PUJetID2016_pujetid_test
src_PUJetID2016_pujetid_test_parent := PUJetID2016/pujetid
src_PUJetID2016_pujetid_test_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUJetID2016_pujetid_test,src/PUJetID2016/pujetid/test,TEST))
