import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

from FWCore.ParameterSet.VarParsing import VarParsing
import os

process = cms.Process("TrackTree",eras.Run2_2017)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '94X_mc2017_realistic_v11', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_v7', '')

process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/Services_cff')
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#    "srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/kskovpen/Trackella/063B4CD9-D552-E711-ADC5-02163E011BF0.root" # RAW data
    "srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/kskovpen/Trackella/001654EA-898D-E711-9163-02163E01A447.root" # RAW data
    #"srm://maite.iihe.ac.be:8443//pnfs/iihe/cms/store/user/kskovpen/Trackella/E8BB30A8-262C-E811-9AAD-34E6D7E05F01.root" # GEN-SIM-RECODEBUG mc
    )
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("output.root"))

process.options = cms.untracked.PSet(
     wantSummary = cms.untracked.bool(False),
     allowUnscheduled = cms.untracked.bool(True)
)

process.TrackTree = cms.EDAnalyzer('TrackAnalysis',

                   generalTracksInput = cms.InputTag("generalTracks::TrackTree"),
                   offlinePrimaryVerticesInput = cms.InputTag("offlinePrimaryVertices::TrackTree"),
                   offlineBeamSpotInput = cms.InputTag("offlineBeamSpot::TrackTree")
)

process.p = cms.Path(process.RawToDigi*
                     process.reconstruction*
                     process.TrackTree)
