#!/bin/env python

import PyCintex
import ROOT
from ROOT import gROOT
gROOT.ProcessLine('.x $ROOTCOREDIR/scripts/load_packages.C')

from ROOT import SH, EL
from ROOT import MyELAlg
from ROOT import xAOD
from ROOT import JetCleaningTool
from ROOT import JERTool, JERSmearingTool

# xAOD event store
event = xAOD.TEvent()

# Submit directory
submitDir = 'submitDir'

# Sampler handler
sh = SH.SampleHandler()

# Scan for files in directory
#SH.scanDir(sh, '/afs/cern.ch/atlas/project/PAT/xAODs/r5591')
l = SH.DiskListLocal('/afs/cern.ch/atlas/project/PAT/xAODs/r5591/mc14_8TeV.117050.PowhegPythia_P2011C_ttbar.recon.AOD.e1727_s1933_s1911_r5591/')
SH.scanSingleDir(sh, 'ttbar', l)
sh.setMetaString('nc_tree', 'CollectionTree')

# The job
job = EL.Job()
job.sampleHandler(sh)

# Our algorithm
GeV = 1000.
alg = MyELAlg()

# Add the algorithm to the job
job.algsAdd(alg)

# Configure the jet cleaning tool
jetCleaning = ROOT.JetCleaningTool('JetCleaningTool')
jetCleaning.setProperty('CutLevel', 'MediumBad')
jetCleaning.initialize()

# Configure the jet smearing tool
jerTool = ROOT.JERTool('JERTool')
jerSmearing = ROOT.JERSmearingTool('JERSmearingTool')
jerSmearing.setProperty('JERToolName', jerTool.name())
jerTool.initialize()
jerSmearing.initialize()

# Job driver
driver = EL.DirectDriver()

# Submit the job
driver.submit(job, submitDir)

# Crashes otherwise...
del jerTool
