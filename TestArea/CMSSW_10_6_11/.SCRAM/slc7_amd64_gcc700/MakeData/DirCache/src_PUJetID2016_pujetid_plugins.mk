ifeq ($(strip $(PUJetID2016pujetidAuto)),)
PUJetID2016pujetidAuto := self/src/PUJetID2016/pujetid/plugins
PLUGINS:=yes
PUJetID2016pujetidAuto_files := $(patsubst src/PUJetID2016/pujetid/plugins/%,%,$(wildcard $(foreach dir,src/PUJetID2016/pujetid/plugins ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
PUJetID2016pujetidAuto_BuildFile    := $(WORKINGDIR)/cache/bf/src/PUJetID2016/pujetid/plugins/BuildFile
PUJetID2016pujetidAuto_LOC_USE := self  FWCore/Framework FWCore/PluginManager FWCore/ParameterSet DataFormats/ParticleFlowCandidate DataFormats/ParticleFlowReco DataFormats/JetReco DataFormats/METReco CommonTools/UtilAlgos CommonTools/RecoAlgos DataFormats/CLHEP DataFormats/Common DataFormats/Candidate DataFormats/HLTReco JetMETCorrections/JetCorrector FWCore/Common DataFormats/HcalRecHit DataFormats/EgammaCandidates DataFormats/MuonReco DataFormats/VertexReco DataFormats/HcalDigi DataFormats/HcalDetId CalibFormats/HcalObjects DPGAnalysis/Skims GeneratorInterface/Pythia8Interface root JetMETCorrections/Modules DataFormats/PatCandidates CondFormats/JetMETObjects SimDataFormats/GeneratorProducts fastjet fastjet-contrib
PUJetID2016pujetidAuto_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PUJetID2016pujetidAuto,PUJetID2016pujetidAuto,$(SCRAMSTORENAME_LIB),src/PUJetID2016/pujetid/plugins))
PUJetID2016pujetidAuto_PACKAGE := self/src/PUJetID2016/pujetid/plugins
ALL_PRODS += PUJetID2016pujetidAuto
PUJetID2016/pujetid_forbigobj+=PUJetID2016pujetidAuto
PUJetID2016pujetidAuto_INIT_FUNC        += $$(eval $$(call Library,PUJetID2016pujetidAuto,src/PUJetID2016/pujetid/plugins,src_PUJetID2016_pujetid_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),edm))
PUJetID2016pujetidAuto_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PUJetID2016pujetidAuto,src/PUJetID2016/pujetid/plugins))
endif
ALL_COMMONRULES += src_PUJetID2016_pujetid_plugins
src_PUJetID2016_pujetid_plugins_parent := PUJetID2016/pujetid
src_PUJetID2016_pujetid_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUJetID2016_pujetid_plugins,src/PUJetID2016/pujetid/plugins,PLUGINS))
