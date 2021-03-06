import FWCore.ParameterSet.Config as cms 
process = cms.Process('myprocess')
#process.TFileService=cms.Service("TFileService",fileName=cms.string('mc_flatTreecmssw11Time.root'))
#process.TFileService=cms.Service("TFileService",fileName=cms.string('mc_testTimev2NoPU.root'))
#process.TFileService=cms.Service("TFileService",fileName=cms.string('mc_testTimev3NoPU.root'))
#process.TFileService=cms.Service("TFileService",fileName=cms.string('mc_testTimev3200PU_btagvar.root'))
process.TFileService=cms.Service("TFileService",fileName=cms.string('btagvar.root'))
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#process.GlobalTag.globaltag = '106X_mc2017_realistic_v7'
#process.GlobalTag.globaltag = '110X_mcRun4_realistic_v3'
process.GlobalTag.globaltag = '106X_upgrade2023_realistic_v3'

#from CondCore.CondDB.CondDB_cfi import CondDB
#CondDBJECFile = CondDB.clone(connect = cms.string('sqlite:Summer19UL17_V4_MC.db'))
#process.jec = cms.ESSource(
#    'PoolDBESSource', CondDBJECFile,
#    toGet = cms.VPSet(
#        cms.PSet(record = cms.string('JetCorrectionsRecord'),
#                 tag = cms.string('JetCorrectorParametersCollection_Summer19UL17_V4_MC_AK4PFchs'),
#                 label = cms.untracked.string('AK4PFchs')),
#        cms.PSet(record = cms.string('JetCorrectionsRecord'),
#                 tag = cms.string('JetCorrectorParametersCollection_Summer19UL17_V4_MC_AK4PFchs'), # FIX LATER
#                 label = cms.untracked.string('AK4PFPuppi'))
#    )
#)

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
   "root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt_80to120_TuneCP5_14TeV_pythia8/MINIAODSIM/PU200_106X_upgrade2023_realistic_v3-v1/10000/F6B0FDEE-D8EE-6E47-B522-8709EC3DE44A.root"
      # "root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt-15to3000_TuneCP5_Flat_14TeV-pythia8/MINIAODSIM/PU200_castor_106X_upgrade2023_realistic_v3-v2/30000/98794CC0-82CB-6441-9F2D-29B8682935E8.root",
  #"root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt-15to3000_TuneCP5_Flat_14TeV-pythia8/MINIAODSIM/PU200_castor_106X_upgrade2023_realistic_v3-v2/30000/F73A0D3B-B337-F347-9CE1-1389658ED9BF.root",
  #"root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt-15to3000_TuneCP5_Flat_14TeV-pythia8/MINIAODSIM/PU200_castor_106X_upgrade2023_realistic_v3-v2/30000/C6A9BA3F-A6CA-CF45-8540-7E377A43799C.root",
  #"root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt-15to3000_TuneCP5_Flat_14TeV-pythia8/MINIAODSIM/PU200_castor_106X_upgrade2023_realistic_v3-v2/60000/CFD31224-725E-0045-9C74-E71C76647A7D.root"    
  #"root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt-15to3000_TuneCP5_Flat_14TeV-pythia8/MINIAODSIM/PU200_castor_106X_upgrade2023_realistic_v3-v2/30000/F56A1062-F1F5-964C-AE92-1B829DE5BD88.root",
  #"root://cmsxrootd.fnal.gov//store/mc/PhaseIITDRSpring19MiniAOD/QCD_Pt-15to3000_TuneCP5_Flat_14TeV-pythia8/MINIAODSIM/PU200_castor_106X_upgrade2023_realistic_v3-v2/30000/D1185F2F-FA0F-F24F-93D6-A06873E0D7CB.root"    
#  "root://cmsxrootd.fnal.gov//store/relval/CMSSW_11_1_0_pre6/RelValQCD_Pt15To7000_Flat_14/MINIAODSIM/110X_mcRun4_realistic_v3_2026D49noPU-v1/20000/EB07E29D-6504-9649-B969-DCDD971A8A5D.root"
  # "root://cmsxrootd.fnal.gov//store/relval/CMSSW_11_1_0_pre6/RelValQCD_Pt15To7000_Flat_14/MINIAODSIM/PU25ns_110X_mcRun4_realistic_v3_2026D49PU200-v1/20000/A4D0EB1F-E579-E04E-827B-707675238708.root",
   #"root://cmsxrootd.fnal.gov//store/relval/CMSSW_11_1_0_pre6/RelValQCD_Pt15To7000_Flat_14/MINIAODSIM/PU25ns_110X_mcRun4_realistic_v3_2026D49PU200-v1/20000/00C8256D-526C-4943-AEA0-60CE0E2F9C5A.root"
  )
)
#############   Format MessageLogger #################
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000




#--- re-apply JEC from the GT -------------------------
process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")

# Add an ESPrefer to override JEC that might be available from the global tag
#process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')

process.patJetCorrFactorsReapplyJEC = process.updatedPatJetCorrFactors.clone(
  src = cms.InputTag("slimmedJets"),
  levels = ['L1FastJet','L2Relative','L3Absolute'],
  payload = 'AK4PFchs' 
)

process.patJetCorrFactorsReapplyJECPuppi = process.updatedPatJetCorrFactors.clone(
  src = cms.InputTag("slimmedJetsPuppi"),
  levels = ['L1FastJet','L2Relative','L3Absolute'],
  payload = 'AK4PFPuppi'
)

process.patJetsReapplyJEC = process.updatedPatJets.clone(
  jetSource = cms.InputTag("slimmedJets"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
)

process.patJetsReapplyJECPuppi = process.updatedPatJets.clone(
  jetSource = cms.InputTag("slimmedJetsPuppi"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJECPuppi"))
)

#--- define the good jets -------------------------------
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets
process.goodJets = selectedPatJets.clone(src='patJetsReapplyJEC', cut='pt > 20 && abs(eta) < 5.0')
process.goodJetsPuppi = selectedPatJets.clone(src='patJetsReapplyJECPuppi', cut='pt > 20 && abs(eta) < 5.0')

#---- Tight JetID -----------------------------------------------------
tight_abs_eta_2p6_chs_puppi = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.90 && numberOfDaughters > 1)
&& (chargedHadronEnergyFraction > 0 && chargedMultiplicity > 0) && abs(eta) <= 2.6)"""

tight_abs_eta_2p6_2p7_chs = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.99 && chargedMultiplicity > 0)  && abs(eta) > 2.6 && abs(eta) <= 2.7)"""

tight_abs_eta_2p7_3p0_chs = """(neutralEmEnergyFraction > 0.01 && neutralEmEnergyFraction < 0.99 && neutralMultiplicity > 2
&& abs(eta) > 2.7 && abs(eta) <= 3.0 )"""

tight_abs_eta_3p0_chs = """(neutralHadronEnergyFraction > 0.2 && neutralEmEnergyFraction < 0.90 && neutralMultiplicity > 10 && abs(eta) > 3.0 )"""

tight_abs_eta_2p6_2p7_puppi = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.99)  && abs(eta) > 2.6 && abs(eta) <= 2.7)"""

tight_abs_eta_2p7_3p0_puppi = """(neutralHadronEnergyFraction < 1.0 && abs(eta) > 2.7 && abs(eta) <= 3.0 )"""

tight_abs_eta_3p0_puppi = """(neutralHadronEnergyFraction > 0.02 && neutralEmEnergyFraction < 0.90
&& neutralMultiplicity > 2 && neutralMultiplicity < 15 && abs(eta) > 3.0 )"""

process.tightIdJets = cms.EDFilter("PATJetSelector",
        src = cms.InputTag("goodJets"),
        cut = cms.string(tight_abs_eta_2p6_chs_puppi + " || " + tight_abs_eta_2p6_2p7_chs + " || " + tight_abs_eta_2p7_3p0_chs + " || " + tight_abs_eta_3p0_chs)
        )

process.tightIdJetsPuppi = cms.EDFilter("PATJetSelector",
        src = cms.InputTag("goodJetsPuppi"),
        cut = cms.string(tight_abs_eta_2p6_chs_puppi + "||" + tight_abs_eta_2p6_2p7_puppi + " || " + tight_abs_eta_2p7_3p0_puppi + " || " + tight_abs_eta_3p0_puppi)
        )

#--- define the pileup id -------------------------------
#from RecoJets.JetProducers.PileupJetID_cfi import _chsalgos_94x
process.load("RecoJets.JetProducers.PileupJetID_cfi")
#process.pileupJetId.jets = cms.InputTag("tightIdJets")
process.pileupJetId.jets = cms.InputTag("goodJets")
process.pileupJetId.inputIsCorrected = True
process.pileupJetId.applyJec = False
process.pileupJetId.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices") 
#process.pileupJetId.algos = cms.VPSet(_chsalgos_94x)


#process.pileupJetIdPuppi = process.pileupJetId.clone(jets = "tightIdJetsPuppi")
process.pileupJetIdPuppi = process.pileupJetId.clone(jets = "goodJetsPuppi")

##-------------------- User analyzers  --------------------------------
process.jmechs            = cms.EDAnalyzer('JMEFlatTreeProducer',
  #jets                    = cms.InputTag('tightIdJets'),
  jets                    = cms.InputTag('goodJets'),                                         
  muons                   = cms.InputTag('slimmedMuons'),
  electrons               = cms.InputTag('slimmedElectrons'),
  met                     = cms.InputTag('slimmedMETs'),
  vertices                = cms.InputTag('offlineSlimmedPrimaryVertices'),
  Dim4vertices              = cms.InputTag('offlineSlimmedPrimaryVertices4D'),                                         
  pileupJetId             = cms.InputTag('pileupJetId'),
  pileupJetIdFlag         = cms.InputTag('pileupJetId:fullId'),
  pileupJetIdDiscriminant = cms.InputTag('pileupJetId:fullDiscriminant'),
  rho                     = cms.InputTag('fixedGridRhoFastjetAll'),
  btagger                 = cms.string('pfCombinedInclusiveSecondaryVertexV2BJetTags'),
  triggerNames            = cms.vstring(
    'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v'
  ),
  triggerResults   = cms.InputTag('TriggerResults','','HLT'),
  triggerPrescales = cms.InputTag('patTrigger'),
  minLepPt         = cms.double(20),
  maxLepEta        = cms.double(2.4),
  minLLMass        = cms.double(70),
  maxLLMass        = cms.double(110),
  isMC             = cms.untracked.bool(True),
  genjets          = cms.untracked.InputTag('slimmedGenJets')
)

process.jmepuppi = process.jmechs.clone(
  #jets                    = "tightIdJetsPuppi",
  jets                    = "goodJetsPuppi",  
  met                     = "slimmedMETsPuppi",
  pileupJetId             = "pileupJetIdPuppi",
  pileupJetIdFlag         = "pileupJetIdPuppi:fullId",
  pileupJetIdDiscriminant = "pileupJetIdPuppi:fullDiscriminant"
)

process.eventCounter = cms.EDAnalyzer("EventCounter")

process.p = cms.Path(
   process.eventCounter +
   process.patJetCorrFactorsReapplyJEC +
   process.patJetCorrFactorsReapplyJECPuppi +
   process.patJetsReapplyJEC +
   process.patJetsReapplyJECPuppi +
   process.goodJets +
   process.goodJetsPuppi +
   #process.tightIdJets +
   #process.tightIdJetsPuppi +
   process.pileupJetId +
   process.pileupJetIdPuppi +
   process.jmechs +
   process.jmepuppi
)
