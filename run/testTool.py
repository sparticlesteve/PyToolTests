#!/bin/env python

# Just a quick reflex dictionary test

from ROOT import gROOT
gROOT.SetBatch()
import PyCintex
import ROOT
gROOT.ProcessLine('.x $ROOTCOREDIR/scripts/load_packages.C')

from ROOT import JetCleaningTool

# Configure the JetCleaningTool
jetCleaning = JetCleaningTool('JetCleaningTool')
jetCleaning.setProperty('OutputLevel', 2)
jetCleaning.initialize()

pmgr = jetCleaning.getPropertyMgr()
for (x, y) in pmgr.getProperties():
    print x, y


