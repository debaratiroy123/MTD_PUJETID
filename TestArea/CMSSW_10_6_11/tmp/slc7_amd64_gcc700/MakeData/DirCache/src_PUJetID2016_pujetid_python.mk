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
