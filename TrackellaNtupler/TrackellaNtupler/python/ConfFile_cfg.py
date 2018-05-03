import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing
import os

process = cms.Process("TrackTree")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    "srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/kskovpen/Trackella/E8BB30A8-262C-E811-9AAD-34E6D7E05F01.root"
    #"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/kskovpen/Trackella/2E1B79B9-A766-E711-AF2B-02163E013594.root"
    )
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("output.root"))

process.options = cms.untracked.PSet(
     wantSummary = cms.untracked.bool(False),
     allowUnscheduled = cms.untracked.bool(True)
)

process.TrackTree = cms.EDAnalyzer('TrackAnalysis',

                   generalTracksInput = cms.InputTag("generalTracks","","RECO")
)
    
process.p = cms.Path(process.TrackTree)
