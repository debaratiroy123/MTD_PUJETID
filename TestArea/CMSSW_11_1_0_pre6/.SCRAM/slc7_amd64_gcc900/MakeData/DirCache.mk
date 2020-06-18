ifeq ($(strip $(PUjetID/pileupJetId)),)
src_PUjetID_pileupJetId := self/PUjetID/pileupJetId
PUjetID/pileupJetId  := src_PUjetID_pileupJetId
src_PUjetID_pileupJetId_BuildFile    := $(WORKINGDIR)/cache/bf/src/PUjetID/pileupJetId/BuildFile
src_PUjetID_pileupJetId_LOC_USE := clhep DataFormats/HLTReco FWCore/Framework self DataFormats/VertexReco DataFormats/HepMCCandidate CondFormats/JetMETObjects CondFormats/DataRecord rootrflx FWCore/PluginManager PhysicsTools/KinFitter L1Trigger/GlobalTriggerAnalyzer RecoMET/METAlgorithms DataFormats/TrackCandidate RecoJets/JetAlgorithms PhysicsTools/UtilAlgos SimDataFormats/GeneratorProducts DataFormats/JetReco rootmath root DataFormats/PatCandidates roottmva JetMETCorrections/Objects DataFormats/Common lhapdf rootcore DataFormats/Candidate JetMETCorrections/Modules FWCore/ServiceRegistry HLTrigger/HLTcore fastjet CondFormats/L1TObjects JetMETCorrections/Algorithms
src_PUjetID_pileupJetId_EX_USE   := $(foreach d,$(src_PUjetID_pileupJetId_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ALL_EXTERNAL_PRODS += src_PUjetID_pileupJetId
src_PUjetID_pileupJetId_INIT_FUNC += $$(eval $$(call EmptyPackage,src_PUjetID_pileupJetId,src/PUjetID/pileupJetId))
endif

ifeq ($(strip $(PUjetID_plugins)),)
PUjetID_plugins := self/src/PUjetID/pileupJetId/plugins
PLUGINS:=yes
PUjetID_plugins_files := $(patsubst src/PUjetID/pileupJetId/plugins/%,%,$(foreach file,*.cc,$(eval xfile:=$(wildcard src/PUjetID/pileupJetId/plugins/$(file)))$(if $(xfile),$(xfile),$(warning No such file exists: src/PUjetID/pileupJetId/plugins/$(file). Please fix src/PUjetID/pileupJetId/plugins/BuildFile.))))
PUjetID_plugins_BuildFile    := $(WORKINGDIR)/cache/bf/src/PUjetID/pileupJetId/plugins/BuildFile
PUjetID_plugins_LOC_USE := self  root rootrflx rootcore roottmva rootmath RecoMET/METAlgorithms JetMETCorrections/Algorithms JetMETCorrections/Modules RecoJets/JetAlgorithms SimDataFormats/GeneratorProducts DataFormats/JetReco DataFormats/VertexReco DataFormats/Candidate DataFormats/PatCandidates DataFormats/Common DataFormats/HepMCCandidate DataFormats/TrackCandidate DataFormats/HLTReco PhysicsTools/UtilAlgos PhysicsTools/KinFitter JetMETCorrections/Objects FWCore/Framework FWCore/PluginManager FWCore/ServiceRegistry clhep HLTrigger/HLTcore L1Trigger/GlobalTriggerAnalyzer CondFormats/L1TObjects CondFormats/DataRecord CondFormats/JetMETObjects fastjet lhapdf
PUjetID_plugins_PRE_INIT_FUNC += $$(eval $$(call edmPlugin,PUjetID_plugins,PUjetID_plugins,$(SCRAMSTORENAME_LIB),src/PUjetID/pileupJetId/plugins))
PUjetID_plugins_PACKAGE := self/src/PUjetID/pileupJetId/plugins
ALL_PRODS += PUjetID_plugins
PUjetID/pileupJetId_forbigobj+=PUjetID_plugins
PUjetID_plugins_INIT_FUNC        += $$(eval $$(call Library,PUjetID_plugins,src/PUjetID/pileupJetId/plugins,src_PUjetID_pileupJetId_plugins,$(SCRAMSTORENAME_BIN),,$(SCRAMSTORENAME_LIB),$(SCRAMSTORENAME_LOGS),edm))
PUjetID_plugins_CLASS := LIBRARY
else
$(eval $(call MultipleWarningMsg,PUjetID_plugins,src/PUjetID/pileupJetId/plugins))
endif
ALL_COMMONRULES += src_PUjetID_pileupJetId_plugins
src_PUjetID_pileupJetId_plugins_parent := PUjetID/pileupJetId
src_PUjetID_pileupJetId_plugins_INIT_FUNC += $$(eval $$(call CommonProductRules,src_PUjetID_pileupJetId_plugins,src/PUjetID/pileupJetId/plugins,PLUGINS))
