#!/bin/env python

# Just a quick reflex dictionary test

from ROOT import gROOT
gROOT.SetBatch()
#import PyCintex
#import ROOT
gROOT.ProcessLine('.x $ROOTCOREDIR/scripts/load_packages.C')

from ROOT import TestTool

# Configure the TestTool
tool = TestTool('TestTool')

pmgr = tool.getPropertyMgr()
for (x, y) in pmgr.getProperties():
    print x, y


