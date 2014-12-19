#!/bin/env python

import PyCintex
from ROOT import gROOT
gROOT.ProcessLine('.x $ROOTCOREDIR/scripts/load_packages.C')

from ROOT import ObjWrapper

o = ObjWrapper()
