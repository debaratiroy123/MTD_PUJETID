ifeq ($(strip $(RecoJetsJetProducers_plugins)),)
RecoJetsJetProducers_plugins := self/src/RecoJets/JetProducers/plugins
PLUGINS:=yes
RecoJetsJetProducers_plugins_files := $(patsubst src/RecoJets/JetProducers/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/RecoJets/JetProducers/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/RecoJets/JetProducers/plugins/$(file). Please fix src/RecoJets/JetProducers/plugins/BuildFile.))))
RecoJetsJetProducers_plugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoJets/JetProducers/plugins/BuildFile
RecoJetsJetProducers_plugins_LOC_USE := self  RecoJets/JetProducers RecoJets/JetAlgorithms FWCore/Framework DataFormats/BTauReco DataFormats/JetReco DataFormats/VertexReco Geometry/CaloGeometry Geometry/Records CommonTools/UtilAlgos CondFormats/JetMETObjects PhysicsTools/UtilAlgos JetMETCorrections/Objects fastjet fastjet-contrib
RecoJetsJetProducers_plugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,RecoJetsJetProducers_plugins,RecoJetsJetProducers_plugins,$(SCRAMSTORENAME_LIB),src/RecoJets/JetProducers/plugins))
RecoJetsJetProducers_plugins_PACKAGE := self/src/RecoJets/JetProducers/plugins
ALL_PRODS += RecoJetsJetProducers_plugins
RecoJets/JetProducers_forbigobj+=RecoJetsJetProducers_plugins
RecoJetsJetProducers_plugins_INIT_FUNC        += $$(eval $$(call Library,RecoJetsJetProducers_plugins,src/RecoJets/JetProducers/plugins,src_RecoJets_JetProducers_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),edm))
RecoJetsJetProducers_plugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,RecoJetsJetProducers_plugins,src/RecoJets/JetProducers/plugins))
endif
ALL_COMMONRULES += src_RecoJets_JetProducers_plugins
src_RecoJets_JetProducers_plugins_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_plugins,src/RecoJets/JetProducers/plugins,PLUGINS))
ifeq ($(strip $(RecoJets/JetProducers)),)
ALL_COMMONRULES += src_RecoJets_JetProducers_src
src_RecoJets_JetProducers_src_parent := RecoJets/JetProducers
src_RecoJets_JetProducers_src_INIT_FUNC := $$(eval $$(call CommonProductRules,src_RecoJets_JetProducers_src,src/RecoJets/JetProducers/src,LIBRARY))
RecoJetsJetProducers := self/RecoJets/JetProducers
RecoJets/JetProducers := RecoJetsJetProducers
RecoJetsJetProducers_files := $(patsubst src/RecoJets/JetProducers/src/%,%,$(wildcard $(foreach dir,src/RecoJets/JetProducers/src ,$(foreach ext,$(SRC_FILES_SUFFIXES),$(dir)/*.$(ext)))))
RecoJetsJetProducers_BuildFile    := $(WORKINGDIR)/cache/bf/src/RecoJets/JetProducers/BuildFile
RecoJetsJetProducers_LOC_USE := self  boost FWCore/Framework DataFormats/JetReco DataFormats/BTauReco DataFormats/PatCandidates Geometry/CaloGeometry Geometry/CaloTopology Geometry/Records Geometry/CommonDetUnit SimDataFormats/CaloHit RecoJets/JetAlgorithms DataFormats/CastorReco CommonTools/MVAUtils fastjet vdt_headers boost_serialization CondFormats/DataRecord
RecoJetsJetProducers_EX_LIB   := RecoJetsJetProducers
RecoJetsJetProducers_EX_USE   := $(foreach d,$(RecoJetsJetProducers_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
RecoJetsJetProducers_PACKAGE := self/src/RecoJets/JetProducers/src
ALL_PRODS += RecoJetsJetProducers
RecoJetsJetProducers_CLASS := LIBRARY
RecoJets/JetProducers_forbigobj+=RecoJetsJetProducers
RecoJetsJetProducers_INIT_FUNC        += $$(eval $$(call Library,RecoJetsJetProducers,src/RecoJets/JetProducers/src,src_RecoJets_JetProducers_src,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),))
endif
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
