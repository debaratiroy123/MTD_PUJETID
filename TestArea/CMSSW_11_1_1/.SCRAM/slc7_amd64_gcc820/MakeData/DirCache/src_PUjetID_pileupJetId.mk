ifeq ($(strip $(PUjetID/pileupJetId)),)
src_PUjetID_pileupJetId := self/PUjetID/pileupJetId
PUjetID/pileupJetId  := src_PUjetID_pileupJetId
src_PUjetID_pileupJetId_BuildFile    := $(WORKINGDIR)/cache/bf/src/PUjetID/pileupJetId/BuildFile
src_PUjetID_pileupJetId_LOC_USE := clhep DataFormats/HLTReco FWCore/Framework self DataFormats/VertexReco DataFormats/HepMCCandidate CondFormats/JetMETObjects CondFormats/DataRecord rootrflx FWCore/PluginManager PhysicsTools/KinFitter L1Trigger/GlobalTriggerAnalyzer RecoMET/METAlgorithms DataFormats/TrackCandidate RecoJets/JetAlgorithms PhysicsTools/UtilAlgos SimDataFormats/GeneratorProducts DataFormats/JetReco rootmath root DataFormats/PatCandidates roottmva JetMETCorrections/Objects DataFormats/Common lhapdf rootcore DataFormats/Candidate JetMETCorrections/Modules FWCore/ServiceRegistry HLTrigger/HLTcore fastjet CondFormats/L1TObjects JetMETCorrections/Algorithms
src_PUjetID_pileupJetId_EX_USE   := $(foreach d,$(src_PUjetID_pileupJetId_LOC_USE),$(if $($(d)_EX_FLAGS_NO_RECURSIVE_EXPORT),,$d))
ALL_EXTERNAL_PRODS += src_PUjetID_pileupJetId
src_PUjetID_pileupJetId_INIT_FUNC += $$(eval $$(call EmptyPackage,src_PUjetID_pileupJetId,src/PUjetID/pileupJetId))
endif

