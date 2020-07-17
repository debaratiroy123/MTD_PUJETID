#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "PUjetID/pileupJetId/plugins/JMEFlatTreeProducer.h"

using namespace std;
using namespace reco;

JMEFlatTreeProducer::JMEFlatTreeProducer(edm::ParameterSet const& cfg): 
  jetsToken(consumes<pat::JetCollection>(cfg.getParameter<edm::InputTag>("jets"))),
  muonsToken(consumes<pat::MuonCollection>(cfg.getParameter<edm::InputTag>("muons"))),
  electronsToken(consumes<pat::ElectronCollection>(cfg.getParameter<edm::InputTag>("electrons"))),
  metToken(consumes<pat::METCollection>(cfg.getParameter<edm::InputTag>("met"))),
  rhoToken(consumes<double>(cfg.getParameter<edm::InputTag>("rho"))),
  recVtxsToken(consumes<reco::VertexCollection>(cfg.getParameter<edm::InputTag>("vertices"))),
  Dim4recVtxsToken(consumes<reco::VertexCollection>(cfg.getParameter<edm::InputTag>("Dim4vertices"))),
  pileupJetIdToken(consumes<edm::ValueMap<StoredPileupJetIdentifier> >(cfg.getParameter<edm::InputTag>("pileupJetId"))),
  pileupJetIdFlagToken(consumes<edm::ValueMap<int> >(cfg.getParameter<edm::InputTag>("pileupJetIdFlag"))),
  pileupJetIdDiscriminantToken(consumes<edm::ValueMap<float> >(cfg.getParameter<edm::InputTag>("pileupJetIdDiscriminant"))),
  triggerResultsToken(consumes<edm::TriggerResults>(cfg.getParameter<edm::InputTag>("triggerResults"))),
  triggerPrescalesToken(consumes<pat::PackedTriggerPrescales>(cfg.getParameter<edm::InputTag>("triggerPrescales"))),
  pupInfoToken(consumes<edm::View<PileupSummaryInfo> >(edm::InputTag("slimmedAddPileupInfo"))),
  genEvtInfoToken(consumes<GenEventInfoProduct>(edm::InputTag("generator"))),
  genJetsToken(consumes<GenJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("genjets",edm::InputTag("")))),
  srcBtag_(cfg.getParameter<std::string>("btagger")),
  triggerNames_(cfg.getParameter<std::vector<std::string> >("triggerNames")),
  isMC_(cfg.getUntrackedParameter<bool>("isMC",false))
{
  minLepPt_  = cfg.getParameter<double>("minLepPt");
  maxLepEta_ = cfg.getParameter<double>("maxLepEta");
  minLLMass_ = cfg.getParameter<double>("minLLMass");
  maxLLMass_ = cfg.getParameter<double>("maxLLMass");
}
//////////////////////////////////////////////////////////////////////////////////////////
void JMEFlatTreeProducer::beginJob() 
{
  //--- book the trigger histograms ---------
  triggerNamesHisto_ = fs_->make<TH1F>("TriggerNames","TriggerNames",1,0,1);
  triggerNamesHisto_->SetCanExtend(TH1::kAllAxes);
  for(unsigned i=0;i<triggerNames_.size();i++) {
    triggerNamesHisto_->Fill(triggerNames_[i].c_str(),1);
  }
  triggerPassHisto_ = fs_->make<TH1F>("TriggerPass","TriggerPass",1,0,1);
  triggerPassHisto_->SetCanExtend(TH1::kAllAxes);
  
  cutFlowHisto_ = fs_->make<TH1F>("CutFlow","CutFlow",1,0,1);
  cutFlowHisto_->SetCanExtend(TH1::kAllAxes);

 //--- book the tree -----------------------
  outTree_ = fs_->make<TTree>("events","events");
  outTree_->Branch("runNo"                ,&run_               ,"run_/I");
  outTree_->Branch("evtNo"                ,&evt_               ,"evt_/I");
  outTree_->Branch("lumi"                 ,&lumi_              ,"lumi_/I");
  outTree_->Branch("npv"                  ,&nVtx_              ,"nVtx_/I");
  outTree_->Branch("pvz"                  ,&pvz_               ,"pvz_/F");
  outTree_->Branch("rho"                  ,&rho_               ,"rho_/F");
  outTree_->Branch("met"                  ,&met_               ,"met_/F");
  outTree_->Branch("sumet"                ,&sumet_             ,"sumet_/F");
  outTree_->Branch("nJets"                ,&nJets_             ,"nJets_/I");
  outTree_->Branch("nLeptons"             ,&nLeptons_          ,"nLeptons_/I");
  outTree_->Branch("llMass"               ,&llMass_            ,"llMass_/F");
  outTree_->Branch("llPt"                 ,&llPt_              ,"llPt_/F");
  outTree_->Branch("llPhi"                ,&llPhi_             ,"llPhi_/F");
  outTree_->Branch("llRapidity"           ,&llRapidity_        ,"llRapidity_/F");
  outTree_->Branch("dPhiZJ"               ,&dPhiZJ_            ,"dPhiZJ_/F");
  outTree_->Branch("Event_time"           ,&event_time_        ,"Event_time/F");
  outTree_->Branch("isZEvent"             ,&isZEvent_          ,"isZEvent_/O");
  //------------------------------------------------------------------
  pt_             = new std::vector<float>;
  btag_           = new std::vector<float>;  
  eta_            = new std::vector<float>;
  phi_            = new std::vector<float>;
  mass_           = new std::vector<float>;
  energy_         = new std::vector<float>;
  chf_            = new std::vector<float>;
  nhf_            = new std::vector<float>;
  nemf_           = new std::vector<float>;
  cemf_           = new std::vector<float>;
  phf_            = new std::vector<float>;
  muf_            = new std::vector<float>;
  elf_            = new std::vector<float>;
  hHFf_           = new std::vector<float>;
  eHFf_           = new std::vector<float>;
  dR2Mean_        = new std::vector<float>;
  majW_           = new std::vector<float>; 
  minW_           = new std::vector<float>;
  frac01_         = new std::vector<float>;
  frac02_         = new std::vector<float>;
  frac03_         = new std::vector<float>;
  frac04_         = new std::vector<float>;
  ptD_            = new std::vector<float>;
  beta_           = new std::vector<float>;
  betaStar_       = new std::vector<float>;
  pull_           = new std::vector<float>;
  jetR_           = new std::vector<float>;
  jetRchg_        = new std::vector<float>; 
  pumva_          = new std::vector<float>; 
  nParticles_     = new std::vector<int>;
  nCharged_       = new std::vector<int>;
  nNeutral_       = new std::vector<int>;
  npr_            = new std::vector<int>;
  chm_            = new std::vector<int>;
  nhm_            = new std::vector<int>;
  phm_            = new std::vector<int>;
  mum_            = new std::vector<int>;
  elm_            = new std::vector<int>;
  hHFm_           = new std::vector<int>;
  eHFm_           = new std::vector<int>;
  puIdLoose_      = new std::vector<bool>;
  puIdMedium_     = new std::vector<bool>;
  puIdTight_      = new std::vector<bool>;
  lId_            = new std::vector<int>;
  lPt_            = new std::vector<float>;
  lEta_           = new std::vector<float>;
  lPhi_           = new std::vector<float>;
  lE_             = new std::vector<float>;
  lIso_           = new std::vector<float>;
  jet_time_       = new std::vector<float>;
  PFcandtime_       = new std::vector<std::vector<float>>;
  PFcandtimerr_     = new std::vector<std::vector<float>>;
  PFcand_           = new std::vector<std::vector<TLorentzVector>>;
  Vtxtime_        = new std::vector<float>;
  Vtxtimerr_      = new std::vector<float>;

  outTree_->Branch("Jet_time"         ,"vector<float>"   ,&jet_time_);
  outTree_->Branch("PFcandtime"       ,"vector<vector<float>>" ,&PFcandtime_);     
  outTree_->Branch("PFcandtimerr_"    ,"vector<vector<float>>" ,&PFcandtimerr_);
  outTree_->Branch("PFcand_"          ,"vector<vector<TLorentzVector>>" ,&PFcand_);
  outTree_->Branch("Vtxtime_"         ,"vector<float>"  ,&Vtxtime_);
  outTree_->Branch("Vtxtimerr_"       ,"vector<float>"  ,&Vtxtimerr_);

  outTree_->Branch("jetPt"             ,"vector<float>"     ,&pt_);
  outTree_->Branch("btag"              ,"vector<float>"     ,&btag_);  
  outTree_->Branch("jetEta"            ,"vector<float>"     ,&eta_);
  outTree_->Branch("phi"               ,"vector<float>"     ,&phi_);
  outTree_->Branch("mass"              ,"vector<float>"     ,&mass_);
  outTree_->Branch("energy"            ,"vector<float>"     ,&energy_);
  outTree_->Branch("chf"               ,"vector<float>"     ,&chf_);
  outTree_->Branch("cemf"              ,"vector<float>"     ,&cemf_);
  outTree_->Branch("nemf"              ,"vector<float>"     ,&nemf_);
  outTree_->Branch("nhf"               ,"vector<float>"     ,&nhf_);
  outTree_->Branch("phf"               ,"vector<float>"     ,&phf_);
  outTree_->Branch("muf"               ,"vector<float>"     ,&muf_);
  outTree_->Branch("elf"               ,"vector<float>"     ,&elf_);
  outTree_->Branch("HFHadf"            ,"vector<float>"     ,&hHFf_);
  outTree_->Branch("HFEmf"             ,"vector<float>"     ,&eHFf_);
  outTree_->Branch("dR2Mean"           ,"vector<float>"     ,&dR2Mean_);
  outTree_->Branch("majW"              ,"vector<float>"     ,&majW_);
  outTree_->Branch("minW"              ,"vector<float>"     ,&minW_);
  outTree_->Branch("frac01"            ,"vector<float>"     ,&frac01_);
  outTree_->Branch("frac02"            ,"vector<float>"     ,&frac02_);
  outTree_->Branch("frac03"            ,"vector<float>"     ,&frac03_);
  outTree_->Branch("frac04"            ,"vector<float>"     ,&frac04_);
  outTree_->Branch("ptD"               ,"vector<float>"     ,&ptD_);
  outTree_->Branch("beta"              ,"vector<float>"     ,&beta_);
  outTree_->Branch("betaStar"          ,"vector<float>"     ,&betaStar_);
  outTree_->Branch("pull"              ,"vector<float>"     ,&pull_);
  outTree_->Branch("jetR"              ,"vector<float>"     ,&jetR_);
  outTree_->Branch("jetRchg"           ,"vector<float>"     ,&jetRchg_);
  outTree_->Branch("pumva"             ,"vector<float>"     ,&pumva_);
  outTree_->Branch("nParticles"        ,"vector<int>"       ,&nParticles_);
  outTree_->Branch("nCharged"          ,"vector<int>"       ,&nCharged_);
  outTree_->Branch("nNeutral"          ,"vector<int>"       ,&nNeutral_);
  outTree_->Branch("npr"               ,"vector<int>"       ,&npr_);
  outTree_->Branch("chm"               ,"vector<int>"       ,&chm_);
  outTree_->Branch("nhm"               ,"vector<int>"       ,&nhm_);
  outTree_->Branch("phm"               ,"vector<int>"       ,&phm_);
  outTree_->Branch("mum"               ,"vector<int>"       ,&mum_);
  outTree_->Branch("elm"               ,"vector<int>"       ,&elm_);
  outTree_->Branch("HFHadm"            ,"vector<int>"       ,&hHFm_);
  outTree_->Branch("HFEmm"             ,"vector<int>"       ,&eHFm_);
  outTree_->Branch("puIdLoose"         ,"vector<bool>"      ,&puIdLoose_);
  outTree_->Branch("puIdMedium"        ,"vector<bool>"      ,&puIdMedium_);
  outTree_->Branch("puIdTight"         ,"vector<bool>"      ,&puIdTight_);
  outTree_->Branch("lepId"             ,"vector<int>"       ,&lId_);
  outTree_->Branch("lepPt"             ,"vector<float>"     ,&lPt_);
  outTree_->Branch("lepEta"            ,"vector<float>"     ,&lEta_);
  outTree_->Branch("lepPhi"            ,"vector<float>"     ,&lPhi_);
  outTree_->Branch("lepEnergy"         ,"vector<float>"     ,&lE_);
  outTree_->Branch("lepIso"            ,"vector<float>"     ,&lIso_);
  triggerBit_ = new std::vector<bool>;
  triggerPre_ = new std::vector<int>;
  outTree_->Branch("triggerBit"           ,"vector<bool>"      ,&triggerBit_);
  outTree_->Branch("triggerPre"           ,"vector<int>"       ,&triggerPre_);
  if (isMC_) {
    genDR_        = new std::vector<float>;
    genPt_        = new std::vector<float>; 
    flavorParton_ = new std::vector<int>;
    flavorHadron_ = new std::vector<int>;
    outTree_->Branch("dRMatch"              ,"vector<float>"     ,&genDR_);
    outTree_->Branch("jetGenPt"             ,"vector<float>"     ,&genPt_);
    outTree_->Branch("jetFlavorParton"      ,"vector<int>"       ,&flavorParton_);
    outTree_->Branch("jetFlavorHadron"      ,"vector<int>"       ,&flavorHadron_);
    outTree_->Branch("nTrueInt"             ,&npu_               ,"npu_/I");
    outTree_->Branch("genEvtWeight"         ,&genEvtWeight_      ,"genEvtWeight_/F");
  }
  cout<<"Begin job finished"<<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
void JMEFlatTreeProducer::endJob() 
{  
  delete jet_time_;
  delete PFcandtime_;
  delete PFcandtimerr_;
  delete PFcand_;
  delete Vtxtime_;
  delete Vtxtimerr_;
  delete pt_;
  delete btag_;
  delete eta_;
  delete phi_;
  delete mass_;
  delete energy_;
  delete chf_;
  delete cemf_;
  delete nemf_;
  delete nhf_;
  delete phf_;
  delete muf_;
  delete elf_;
  delete hHFf_;
  delete eHFf_;
  delete npr_;
  delete chm_;
  delete nhm_;
  delete phm_;
  delete mum_;
  delete elm_;
  delete hHFm_;
  delete eHFm_;
  delete dR2Mean_;
  delete majW_;
  delete minW_;
  delete frac01_;
  delete frac02_;
  delete frac03_;
  delete frac04_;
  delete ptD_;
  delete beta_;
  delete betaStar_;
  delete pull_;
  delete jetR_;
  delete jetRchg_;
  delete pumva_;
  delete nParticles_;
  delete nCharged_;
  delete nNeutral_;
  delete puIdLoose_;
  delete puIdMedium_;
  delete puIdTight_;
  delete triggerBit_;
  delete triggerPre_;
  delete lId_;
  delete lIso_;
  delete lPt_;
  delete lEta_;
  delete lPhi_;
  delete lE_;
  if (isMC_) {
    delete genDR_;
    delete genPt_;
    delete flavorParton_;
    delete flavorHadron_;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
bool JMEFlatTreeProducer::isGoodMuon(const pat::Muon &mu,const reco::Vertex &vtx)
{
  bool res = true; // by default is good, unless fails a cut bellow
  if(mu.pt() < minLepPt_) res = false;
  if(fabs(mu.eta()) > maxLepEta_) res = false;
  if(!mu.isTightMuon(vtx)) res = false;
  if (!mu.passed(reco::Muon::PFIsoTight)) res = false; 
  //return res;
  res = false;
  return res; // skipping muons/leptons for QCD
}
//////////////////////////////////////////////////////////////////////////////////////////
bool JMEFlatTreeProducer::isGoodElectron(const pat::Electron &el)
{
  bool res = true; // by default is good, unless fails a cut bellow
  if(el.pt() < minLepPt_) res = false;
  if(fabs(el.eta()) > maxLepEta_ && res == true) res = false;
  //return res;
  return false; // skipping electrons for now
}
//////////////////////////////////////////////////////////////////////////////////////////
void JMEFlatTreeProducer::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup) 
{
  initialize();

  iEvent.getByToken(jetsToken,jets);
  
  iEvent.getByToken(muonsToken,muons);
  iEvent.getByToken(electronsToken,electrons);
  
  iEvent.getByToken(metToken,met);
  iEvent.getByToken(rhoToken,rho);
  iEvent.getByToken(recVtxsToken,recVtxs);
  iEvent.getByToken(Dim4recVtxsToken,Dim4recVtxs);
  iEvent.getByToken(pileupJetIdToken,pileupJetId);  
  iEvent.getByToken(pileupJetIdFlagToken,pileupJetIdFlag);  
  iEvent.getByToken(pileupJetIdDiscriminantToken,pileupJetIdDiscriminant);  
  iEvent.getByToken(triggerResultsToken,triggerResults);  
  iEvent.getByToken(triggerPrescalesToken,triggerPrescales);

  //-------------- Trigger Info -----------------------------------
  triggerPassHisto_->Fill("totalEvents",1);
  
  bool passTrigger(false);
  const edm::TriggerNames &names = iEvent.triggerNames(*triggerResults);  
  for(unsigned int k=0;k<triggerNames_.size();k++) {
    bool bit(false);
    int pre(1);
    for(unsigned int itrig=0;itrig<triggerResults->size();itrig++) {
      string trigger_name = string(names.triggerName(itrig));
      //--- erase the last character, i.e. the version number----
      // trigger_name.pop_back();
      if (trigger_name.find(triggerNames_[k]) == 0) {
        bit = triggerResults->accept(itrig); 
        pre = triggerPrescales->getPrescaleForIndex(itrig);
        if (bit) {
          triggerPassHisto_->Fill(triggerNames_[k].c_str(),1);
        } 
      }
    }
    passTrigger += bit;
    triggerBit_->push_back(bit); 
    triggerPre_->push_back(pre);   
    }
  if (!iEvent.isRealData()) { 
    iEvent.getByToken(genEvtInfoToken,genEvtInfo);
    iEvent.getByToken(pupInfoToken,pupInfo);
    iEvent.getByToken(genJetsToken,genjets);
    
    genEvtWeight_ = genEvtInfo->weight();
 
    edm::View<PileupSummaryInfo>::const_iterator PUI;
    for(PUI = pupInfo->begin(); PUI != pupInfo->end(); ++PUI) {
      if (PUI->getBunchCrossing() == 0) {
        npu_ = PUI->getTrueNumInteractions();
	//std::cout << " npu JME " << npu_ << std::endl;
      }
    }
  }
  vector<const reco::Candidate *> myLeptons;

  if (recVtxs->size() > 0) {

    pvz_ = (*recVtxs)[0].z();
    //----- loop over leptons --------------------
    for (const pat::Muon &mu : *muons) {
      if (isGoodMuon(mu,(*recVtxs)[0])) myLeptons.push_back(&mu);
    }
    for (const pat::Electron &el : *electrons) {
      if (isGoodElectron(el)) myLeptons.push_back(&el);
    }
    std::sort(myLeptons.begin(),myLeptons.end(),[](const reco::Candidate *a,const reco::Candidate *b){return a->pt() > b->pt();});
    nLeptons_ = (int)myLeptons.size();
    for(int ii = 0 ; ii < nLeptons_; ii++) {
      lPt_->push_back(myLeptons[ii]->pt());
      lEta_->push_back(myLeptons[ii]->eta());
      lPhi_->push_back(myLeptons[ii]->phi());
      lE_->push_back(myLeptons[ii]->energy());
      lId_->push_back(myLeptons[ii]->pdgId());
     // lIso_->push_back(LeptonRelIso(myLeptons[ii],*rho));
    }
  }
  if (nLeptons_ > 1) {
    TLorentzVector p4lep1(0.0,0.0,0.0,0.0),p4lep2(0.0,0.0,0.0,0.0);
    p4lep1.SetPtEtaPhiE((*lPt_)[0],(*lEta_)[0],(*lPhi_)[0],(*lE_)[0]); 
    p4lep2.SetPtEtaPhiE((*lPt_)[1],(*lEta_)[1],(*lPhi_)[1],(*lE_)[1]);
    llMass_     = (p4lep1 + p4lep2).M();
    llPt_       = (p4lep1 + p4lep2).Pt();
    llPhi_      = (p4lep1 + p4lep2).Phi();
    llRapidity_ = (p4lep1 + p4lep2).Rapidity();
  }
  
   for(unsigned int vtx = 0; vtx < Dim4recVtxs->size(); ++vtx) 
    {
      Vtxtime_->push_back((*Dim4recVtxs)[vtx].t());
      Vtxtimerr_->push_back((*Dim4recVtxs)[vtx].tError());
    }
   
   //----- PF jets ------------------------------
   float event_time       = 0;
   float event_timeWeight = 0;
   float event_timeNtk    = 0;
   
   

   for(pat::JetCollection::const_iterator ijet =jets->begin();ijet != jets->end(); ++ijet) {
     //try with different access//
     std::cout << " daughters " << ijet->numberOfDaughters() << std::endl;
     for (unsigned int i = 0; i <  ijet->numberOfDaughters(); i++) {
       const pat::PackedCandidate* PackedCandidate = dynamic_cast<const pat::PackedCandidate*>(ijet->daughter(i));
       if ( !PackedCandidate ) continue;
       if ( PackedCandidate->charge() == 0 ) continue;
       auto track = PackedCandidate->bestTrack();
       if ( !track ) continue;
       //float track_dxy = track->dxy(pv->position());
       //float track_dz  = track->dz(pv->position());
       float track_time    = track->t0();
       float track_timeError = track->covt0t0();
       std::cout << " track_time " << track_time << " " << " track_timeError " << track_timeError << std::endl;
     }
   }
   /*
     std::vector<reco::CandidatePtr> daus(ijet->daughterPtrVector());
     std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });
     for (unsigned int i2 = 0; i2 < daus.size(); ++i2) {
       const pat::PackedCandidate &cand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
       if (cand.charge() != 0) {
	 auto track = cand.bestTrack();
	 if ( track ) {
	   
	   float track_dxy = track->dxy((*recVtxs)[0].position());
	   float track_dz  = track->dz((*recVtxs)[0].position());
	   float track_time    = track->t0();
	   float track_timeError = track->covt0t0();
	   //if (track_timeError != -1.) std::cout << " track_timeError " << track_timeError << std::endl;
	   float track_pt    = track->pt();
	   float time_weight = track_pt * track_pt;
	   
	   if ( track_timeError > 0. && abs(track_time) < 1 && abs(track_dxy) < 0.05 && abs(track_dz) < 0.10 ) {
	   //if ( track_timeError > 0. && abs(track_dxy) < 0.05 && abs(track_dz) < 0.10 ) {  
	     if (abs(track_time) < 1 && fabs(track_dxy) < 0.05 && fabs(track_dz) < 0.10 ) {
	       event_timeNtk    += 1;
	       event_timeWeight += time_weight;
	       event_time       += track_time * time_weight;
	     }
	   }
	 }
       }
     }
   */
   //std::cout << " event_timeNtk " << event_timeNtk << std::endl;
   //if ( event_timeNtk > 0 ) event_time /= event_timeWeight;
   //else                     event_time = -1;
   //event_time_ = event_time;

   for(pat::JetCollection::const_iterator ijet =jets->begin();ijet != jets->end(); ++ijet) {  

     float jet_time       = 0;
     float jet_timeWeight = 0;
     float jet_timeNtk    = 0;

     std::vector<float> PFijetcandtime, PFijetcandtimerr;
     std::vector<TLorentzVector> candv;
     std::vector<reco::CandidatePtr> daus(ijet->daughterPtrVector());
     
     std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); });
       for (unsigned int i2 = 0; i2 < daus.size(); ++i2) {
	 const pat::PackedCandidate &cand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
	 if (cand.charge() != 0) {
	   auto track = cand.bestTrack();
	   if ( track ) {
	     float track_time    = track->t0();
	     float track_timeError = track->covt0t0();
	     float track_pt    = track->pt();
	     float time_weight = track_pt * track_pt;
	     
	     if ( track_timeError > 0. && abs(track_time) < 1 ) {
	       jet_timeNtk += 1;
	       jet_timeWeight += time_weight;
	       jet_time += track_time * time_weight;
	     }
	   }
	 }

	 PFijetcandtime.push_back(cand.time());
	 PFijetcandtimerr.push_back(cand.timeError());
	 TLorentzVector cand_kin;
	 cand_kin.SetPtEtaPhiE(cand.pt(),cand.eta(),cand.phi(),cand.energy());
	 candv.push_back(cand_kin);
       }
       
       //  if ( jet_timeNtk > 0 && event_timeNtk > 0 ) {
       //jet_time = jet_time / jet_timeWeight - event_time;
       //jet_time = TMath::Abs(jet_time);
       //}
       //else jet_time = -1;
       //jet_time_->push_back(jet_time);
   
       bool isLeptonMatched(false);
       float DRmax = 0.4;
       for(auto & lep: myLeptons) if( deltaR(lep->eta(),lep->phi(),ijet->eta(),ijet->phi()) < DRmax ) isLeptonMatched = true;
       if (isLeptonMatched) continue;
       chf_           ->push_back(ijet->chargedHadronEnergyFraction());
       cemf_          ->push_back(ijet->chargedEmEnergyFraction());
       nemf_          ->push_back(ijet->neutralEmEnergyFraction());
       nhf_           ->push_back(ijet->neutralHadronEnergyFraction());
       phf_           ->push_back(ijet->photonEnergyFraction());
       elf_           ->push_back(ijet->electronEnergyFraction());
       muf_           ->push_back(ijet->muonEnergyFraction());
       hHFf_          ->push_back(ijet->HFHadronEnergyFraction());
       eHFf_          ->push_back(ijet->HFEMEnergyFraction());
       npr_           ->push_back(ijet->neutralMultiplicity()+ijet->chargedMultiplicity());
       chm_           ->push_back(ijet->chargedHadronMultiplicity());
       nhm_           ->push_back(ijet->neutralHadronMultiplicity());
       phm_           ->push_back(ijet->photonMultiplicity());
       elm_           ->push_back(ijet->electronMultiplicity());
       mum_           ->push_back(ijet->muonMultiplicity());
       hHFm_          ->push_back(ijet->HFHadronMultiplicity());
       eHFm_          ->push_back(ijet->HFEMMultiplicity());
       pt_            ->push_back(ijet->pt());
       phi_           ->push_back(ijet->phi());
       eta_           ->push_back(ijet->eta());
       mass_          ->push_back(ijet->mass());
       energy_        ->push_back(ijet->energy());
       btag_          ->push_back(ijet->bDiscriminator(srcBtag_.c_str()));
       
       edm::RefToBase<pat::Jet> jetRef(edm::Ref<pat::JetCollection>(jets, ijet-jets->begin()));
       
       pumva_         ->push_back((*pileupJetIdDiscriminant)[jetRef]);
       int idflag = (*pileupJetIdFlag)[jetRef];
       puIdLoose_     ->push_back(PileupJetIdentifier::passJetId(idflag, PileupJetIdentifier::kLoose));
       puIdMedium_    ->push_back(PileupJetIdentifier::passJetId(idflag, PileupJetIdentifier::kMedium));
       puIdTight_     ->push_back(PileupJetIdentifier::passJetId(idflag, PileupJetIdentifier::kTight));
       dR2Mean_       ->push_back((*pileupJetId)[jetRef].dR2Mean());
       majW_          ->push_back((*pileupJetId)[jetRef].majW());
       minW_          ->push_back((*pileupJetId)[jetRef].minW());
       frac01_        ->push_back((*pileupJetId)[jetRef].frac01());
       frac02_        ->push_back((*pileupJetId)[jetRef].frac02());
       frac03_        ->push_back((*pileupJetId)[jetRef].frac03());
       frac04_        ->push_back((*pileupJetId)[jetRef].frac04());
       ptD_           ->push_back((*pileupJetId)[jetRef].ptD());
       beta_          ->push_back((*pileupJetId)[jetRef].beta());
       betaStar_      ->push_back((*pileupJetId)[jetRef].betaStar());
       pull_          ->push_back((*pileupJetId)[jetRef].pull());
       jetR_          ->push_back((*pileupJetId)[jetRef].jetR());
       jetRchg_       ->push_back((*pileupJetId)[jetRef].jetRchg());
       nParticles_    ->push_back((*pileupJetId)[jetRef].nParticles());
       nCharged_      ->push_back((*pileupJetId)[jetRef].nCharged());
       nNeutral_      ->push_back(ijet->neutralMultiplicity());
   
       if (!iEvent.isRealData()) {
	 float dRmin = 100.;
	 float ptGen = -1.0;
	 for(reco::GenJetCollection::const_iterator igen = genjets->begin();igen != genjets->end(); ++igen) {
	   float dR = deltaR(ijet->eta(),ijet->phi(),igen->eta(),igen->phi());
	   if (dR < dRmin) {
	     dRmin = dR;
	     ptGen = igen->pt();
	   }
	 }
	 genDR_->push_back(dRmin);
	 genPt_->push_back(ptGen); 
	 flavorParton_  ->push_back(ijet->partonFlavour());
	 flavorHadron_  ->push_back(ijet->hadronFlavour());
       }
       PFcandtime_->push_back(PFijetcandtime);
       PFcandtimerr_->push_back(PFijetcandtimerr);
       PFcand_->push_back(candv);
   }// jet loop 
     
   nJets_  = pt_->size();    
   rho_    = *rho;
   met_    = (*met)[0].et();
   sumet_  = (*met)[0].sumEt();
   nVtx_   = recVtxs->size();
   run_    = iEvent.id().run();
   evt_    = iEvent.id().event();
   lumi_   = iEvent.id().luminosityBlock();
   if ((nLeptons_ > 1) && (llMass_ > minLLMass_) && (llMass_ < maxLLMass_)) {
  if ((*lId_)[0]*(*lId_)[1]/fabs((*lId_)[0]*(*lId_)[1]) == -1) {
    isZEvent_ = true; 
     }
   }
   cutFlowHisto_->Fill("all",1);
   if ((nJets_ > 0)) {outTree_->Fill();}
   if (passTrigger) {
     cutFlowHisto_->Fill("trigger",1);
     if (isZEvent_) {
       cutFlowHisto_->Fill("Z",1);
       if ((nJets_ > 0)) {
	 cutFlowHisto_->Fill("nJets",1);
	 dPhiZJ_ = fabs(deltaPhi(llPhi_,(*phi_)[0]));
	 //outTree_->Fill();  
       }
     }
   }
}
//////////////////////////////////////////////////////////////////////////////////////////
void JMEFlatTreeProducer::initialize()
{
  run_            = -1;
  evt_            = -1;
  lumi_           = -1;
  nVtx_           = -1;
  pvz_            = -999;
  rho_            = -1;
  met_            = -1;
  sumet_          = -1;
  nJets_          = -1;
  nLeptons_       = -1;
  llMass_         = -1;
  llPt_           = -1;
  llPhi_          = -10;
  llRapidity_     = -10;
  dPhiZJ_         = -1;
  event_time_     = 0;
  isZEvent_       = false;
  jet_time_       ->clear();
  PFcandtime_     ->clear();
  PFcandtimerr_   ->clear();
  PFcand_         ->clear();
  Vtxtime_        ->clear();
  Vtxtimerr_      ->clear();
  pt_             ->clear();
  eta_            ->clear();
  phi_            ->clear();
  mass_           ->clear();
  energy_         ->clear();
  chf_            ->clear();
  cemf_           ->clear();
  nemf_           ->clear();
  nhf_            ->clear();
  phf_            ->clear();
  elf_            ->clear();
  muf_            ->clear();
  hHFf_           ->clear();
  eHFf_           ->clear();
  npr_            ->clear();
  chm_            ->clear();
  nhm_            ->clear();
  phm_            ->clear();
  elm_            ->clear();
  mum_            ->clear();
  hHFm_           ->clear();
  eHFm_           ->clear();
  btag_           ->clear();
  dR2Mean_        ->clear();
  majW_           ->clear();
  minW_           ->clear();
  frac01_         ->clear();
  frac02_         ->clear();
  frac03_         ->clear();
  frac04_         ->clear();
  ptD_            ->clear();
  beta_           ->clear();
  betaStar_       ->clear();
  pull_           ->clear();
  jetR_           ->clear();
  jetRchg_        ->clear();
  pumva_          ->clear();
  nParticles_     ->clear();
  nCharged_       ->clear();
  nNeutral_       ->clear(); 
  puIdLoose_      ->clear(); 
  puIdMedium_     ->clear();
  puIdTight_      ->clear();
  triggerBit_     ->clear();
  triggerPre_     ->clear();
  lId_            ->clear();
  lIso_           ->clear();
  lPt_            ->clear();
  lEta_           ->clear();
  lPhi_           ->clear();
  lE_             ->clear();
  //----- MC -------
  if (isMC_) {
    npu_ = -1;
    genEvtWeight_ = -999;
    genDR_->clear();
    genPt_->clear(); 
    flavorParton_->clear();
    flavorHadron_->clear();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
JMEFlatTreeProducer::~JMEFlatTreeProducer() 
{
}

DEFINE_FWK_MODULE(JMEFlatTreeProducer);
