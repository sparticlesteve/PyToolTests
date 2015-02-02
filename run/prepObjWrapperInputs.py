#!/bin/env python

import ROOT

f = ROOT.TFile('ObjWrapperInput.root', 'recreate')

hist = ROOT.TH1F('hist', 'hist', 10, 0, 10)
graph = ROOT.TGraph(10)
graph.SetName('graph')
func = ROOT.TF1('func', 'gaus(0)', 0, 10)

hist.Write()
graph.Write()
func.Write()

f.Close()

