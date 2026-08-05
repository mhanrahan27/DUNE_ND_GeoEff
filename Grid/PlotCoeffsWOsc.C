void PlotCoeffsWOsc(){

	// read in the file; CHANGE THIS FILE TO YOUR OWN
	TFile* FileGeoEff = new TFile("AllOAPosWithFDEvRateForEtrue_EtrimSummed_histograms_AllCoeffFDEvRateOptions_Osc.root", "READ");
	FileGeoEff->cd();

	// read in our no coeffs, w/ FD Event rate 2d histo (sometimes referred to as original/Ioana histo)
    TH2D* SelectedEvGeoEff = (TH2D*) FileGeoEff->Get("SelectedEventsTwoDHisto_FDEvt_0");
	SelectedEvGeoEff->SetDirectory(0);

	// now read in my histos
	// no coeffs:
    // read in NO FD Event rate histo:
	TH1D* EtrimPmuWeightedNoCoeffsNoFDEvtRate = (TH1D*) FileGeoEff->Get("NuOscHistEtrimPmuWeightedAllVtxXNoCoeffNoFDEvRateAtND_FDEvt_0"); 
	EtrimPmuWeightedNoCoeffsNoFDEvtRate->SetDirectory(0);
	// read in histo WITH FD Event Rate:
	TH1D* EtrimPmuWeightedNoCoeffswFDEvtRate = (TH1D*) FileGeoEff->Get("NuOscHistEtrimPmuWeightedAllVtxXNoCoeffWithFDEvRateAtND_FDEvt_0"); 
	EtrimPmuWeightedNoCoeffswFDEvtRate->SetDirectory(0);

	// w/ coeffs:
	// read in NO FD Event rate histo:
	TH1D* EtrimPmuWeightedCoeffsNoFDEvtRate = (TH1D*) FileGeoEff->Get("NuOscHistEtrimPmuWeightedAllVtxXTimesCoeffNoFDEvRate_FDEvt_0"); 
	EtrimPmuWeightedCoeffsNoFDEvtRate->SetDirectory(0);
	// read in histo WITH FD Event Rate:
	TH1D* EtrimPmuWeightedCoeffswFDEvtRate = (TH1D*) FileGeoEff->Get("NuOscHistEtrimPmuWeightedAllVtxXTimesCoeffWithFDEvRateAtND_FDEvt_0"); 
	EtrimPmuWeightedCoeffswFDEvtRate->SetDirectory(0);


	//this is the file with the PRISM Prediction, i.e what we want to be able to match with.
	TFile* PRISMFile = new TFile("PRISMPred_EdepWithNeutronEnergy_NoSysts_WithOsc_FlatRunPlan.root", "READ");
	PRISMFile->cd();
	// ==this is the linearly combined Selected ND Events (vs Ereco) after ND background subtraction i.e from NDData we subtract the background and then we apply the coefficients
	// == this will be as a function of reconstructed energy in the ND = deposited hadron energy + true muon energy for this file
	//==this is what we want to match with our FD events translated to the ND
	TH1D* PRISMDataTimesCoeff = (TH1D*) PRISMFile->Get("numu_EvMatch_nom/FD_nu_numu/NDLinearComb");
	PRISMDataTimesCoeff->SetDirectory(0);
	//===these are the coefficients vs off-axis position
	TH1D* Coeffs293kA = (TH1D*)PRISMFile->Get("numu_EvMatch_nom/FD_nu_numu/NDFDWeightings_293kA");
	Coeffs293kA->SetDirectory(0);
	//TH1D* Coeffs280kA = (TH1D*)PRISMFile->Get("numu_EvMatch_nom/FD_nu_numu/NDFDWeightings_280kA");
	//Coeffs280kA->SetDirectory(0);


	// now I need to convert the Etrim histos from MeV to GeV
	// this step just initializes the histo structure for each
	//no coeffs:
	// create a 1d histo to scale into GeV for no FD Event Rate:
    TH1D* EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV = new TH1D("EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV", "EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV",
             PRISMDataTimesCoeff->GetNbinsX(), // doesn't matter that this is TimesCoeff, I'm just getting the binning structure
             PRISMDataTimesCoeff->GetXaxis()->GetXbins()->GetArray()); // get the x-axis binning array from old histo
	EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->SetDirectory(0);
	EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->GetXaxis()->SetTitle("EtrimPmuWeightedNoCoeffsNoFDEvtRate [GeV]");

	// create a 1d histo to scale into GeV for w/ FD Event Rate:
	TH1D* EtrimPmuWeightedNoCoeffswFDEvtRateGeV = new TH1D("EtrimPmuWeightedNoCoeffswFDEvtRateGeV", "EtrimPmuWeightedNoCoeffswFDEvtRateGeV",
             PRISMDataTimesCoeff->GetNbinsX(), // doesn't matter that this is TimesCoeff, I'm just getting the binning structure
             PRISMDataTimesCoeff->GetXaxis()->GetXbins()->GetArray()); // get the x-axis binning array from old histo
	EtrimPmuWeightedNoCoeffswFDEvtRateGeV->SetDirectory(0);
	EtrimPmuWeightedNoCoeffswFDEvtRateGeV->GetXaxis()->SetTitle("EtrimPmuWeightedNoCoeffswFDEvtRate [GeV]");

	// w/ coeffs:
	// create a 1d histo to scale into GeV for no FD Event Rate:
    TH1D* EtrimPmuWeightedCoeffsNoFDEvtRateGeV = new TH1D("EtrimPmuWeightedCoeffsNoFDEvtRateGeV", "EtrimPmuWeightedCoeffsNoFDEvtRateGeV",
             PRISMDataTimesCoeff->GetNbinsX(),
             PRISMDataTimesCoeff->GetXaxis()->GetXbins()->GetArray()); // get the x-axis binning array from old histo
	EtrimPmuWeightedCoeffsNoFDEvtRateGeV->SetDirectory(0);
	EtrimPmuWeightedCoeffsNoFDEvtRateGeV->GetXaxis()->SetTitle("EtrimPmuWeightedCoeffsNoFDEvtRate [GeV]");

	// create a 1d histo to scale into GeV for w/ FD Event Rate:
	TH1D* EtrimPmuWeightedCoeffswFDEvtRateGeV = new TH1D("EtrimPmuWeightedCoeffswFDEvtRateGeV", "EtrimPmuWeightedCoeffswFDEvtRateGeV",
             PRISMDataTimesCoeff->GetNbinsX(),
             PRISMDataTimesCoeff->GetXaxis()->GetXbins()->GetArray()); // get the x-axis binning array from old histo
	EtrimPmuWeightedCoeffswFDEvtRateGeV->SetDirectory(0);
	EtrimPmuWeightedCoeffswFDEvtRateGeV->GetXaxis()->SetTitle("EtrimPmuWeightedCoeffswFDEvtRate [GeV]");


	// now loop over MeV bins in my original histos, scale to GeV, then add to the GeV histos e just initialized
	// no coeffs: 
    // this is for no FD Event Rate:
	for (int i = 1; i <= EtrimPmuWeightedNoCoeffsNoFDEvtRate->GetNbinsX(); i++) { // for each bin in the original histo:
		// convert the original bin center to GeV:
		double eNoCoeffsNoFDEvtRateGeV = EtrimPmuWeightedNoCoeffsNoFDEvtRate->GetBinCenter(i) / 1000.0;
		// find/define the matching bin in my GeV histo:
		int binNoCoeffsNoFDEvtRateGeV = EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->FindBin(eNoCoeffsNoFDEvtRateGeV);
		// then add the MeV bin content to the matching GeV bin:
		EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->AddBinContent(binNoCoeffsNoFDEvtRateGeV, EtrimPmuWeightedNoCoeffsNoFDEvtRate->GetBinContent(i)); 
	}
	// this is for with FD Event Rate:
	for (int i = 1; i <= EtrimPmuWeightedNoCoeffswFDEvtRate->GetNbinsX(); i++) { // for each bin in the original histo:
		// convert the original bin center to GeV:
		double eNoCoeffswFDEvtRateGeV = EtrimPmuWeightedNoCoeffswFDEvtRate->GetBinCenter(i) / 1000.0;
		// find/define the matching bin in my GeV histo:
		int binNoCoeffswFDEvtRateGeV = EtrimPmuWeightedNoCoeffswFDEvtRateGeV->FindBin(eNoCoeffswFDEvtRateGeV);
		// then add the MeV bin content to the matching GeV bin:
		EtrimPmuWeightedNoCoeffswFDEvtRateGeV->AddBinContent(binNoCoeffswFDEvtRateGeV, EtrimPmuWeightedNoCoeffswFDEvtRate->GetBinContent(i)); 
	}

	// w/ coeffs:
	// this is for no FD Event Rate:
	for (int i = 1; i <= EtrimPmuWeightedCoeffsNoFDEvtRate->GetNbinsX(); i++) { // for each bin in the original histo:
		// convert the original bin center to GeV:
		double eCoeffsNoFDEvtRateGeV = EtrimPmuWeightedCoeffsNoFDEvtRate->GetBinCenter(i) / 1000.0;
		// find/define the matching bin in my GeV histo:
		int binCoeffsNoFDEvtRateGeV = EtrimPmuWeightedCoeffsNoFDEvtRateGeV->FindBin(eCoeffsNoFDEvtRateGeV);
		// then add the MeV bin content to the matching GeV bin:
		EtrimPmuWeightedCoeffsNoFDEvtRateGeV->AddBinContent(binCoeffsNoFDEvtRateGeV, EtrimPmuWeightedCoeffsNoFDEvtRate->GetBinContent(i)); 
	}
	// this is for with FD Event Rate:
	for (int i = 1; i <= EtrimPmuWeightedCoeffswFDEvtRate->GetNbinsX(); i++) { // for each bin in the original histo:
		// convert the original bin center to GeV:
		double eCoeffswFDEvtRateGeV = EtrimPmuWeightedCoeffswFDEvtRate->GetBinCenter(i) / 1000.0;
		// find/define the matching bin in my GeV histo:
		int binCoeffswFDEvtRateGeV = EtrimPmuWeightedCoeffswFDEvtRateGeV->FindBin(eCoeffswFDEvtRateGeV);
		// then add the MeV bin content to the matching GeV bin:
		EtrimPmuWeightedCoeffswFDEvtRateGeV->AddBinContent(binCoeffswFDEvtRateGeV, EtrimPmuWeightedCoeffswFDEvtRate->GetBinContent(i)); 
	}

	// now we can just plot


	// this is the old canvas showing the value of the coefficients vs OA Pos
	TCanvas* CanvasCoeff = new TCanvas("CanvasCoeff", "");
	Coeffs293kA->Draw("hist");


	//scale all histos to bin width, i.e events / GeV, and then scale so the integral=1
	// original pink line comparison
	SelectedEvGeoEff->Scale(1, "width");
	//project on the x-axis -> get selected events vs energy
	TH1D* SelectedEvGeoEffVsE = (TH1D*) SelectedEvGeoEff->ProjectionX();
	SelectedEvGeoEffVsE->SetDirectory(0);
	SelectedEvGeoEffVsE->Scale(1.0/SelectedEvGeoEffVsE->Integral());

	// no coeffs:
	// no FD Event Rate:
	EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->Scale(1, "width");
	EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->Scale(1.0 / EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->Integral());
	// with FD Event Rate:
    EtrimPmuWeightedNoCoeffswFDEvtRateGeV->Scale(1, "width");
	EtrimPmuWeightedNoCoeffswFDEvtRateGeV->Scale(1.0 / EtrimPmuWeightedNoCoeffswFDEvtRateGeV->Integral());
	
	// w/ coeffs:
	// no FD Event Rate:
	EtrimPmuWeightedCoeffsNoFDEvtRateGeV->Scale(1, "width");
	EtrimPmuWeightedCoeffsNoFDEvtRateGeV->Scale(1.0 / EtrimPmuWeightedCoeffsNoFDEvtRateGeV->Integral());
	// with FD Event Rate:
    EtrimPmuWeightedCoeffswFDEvtRateGeV->Scale(1, "width");
	EtrimPmuWeightedCoeffswFDEvtRateGeV->Scale(1.0 / EtrimPmuWeightedCoeffswFDEvtRateGeV->Integral());
	
	// comparison data; do not need to scale by width:
	PRISMDataTimesCoeff->Scale(1.0 / PRISMDataTimesCoeff->Integral());


	// now create my canvas
	TCanvas* CanvasCoeffs = new TCanvas("CanvasCoeffs", "CanvasCoeffs");
	CanvasCoeffs->cd();
	CanvasCoeffs->DrawFrame(0.0, 0.0, 10, 0.043);

	// some specs
	// original pink line comparison:
	SelectedEvGeoEffVsE->SetLineColor(6);
	SelectedEvGeoEffVsE->SetLineWidth(2);
	// no coeffs:
	// no FD Event Rate:
	EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->SetLineColor(7);
	EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->SetLineWidth(2);
	// with FD Event Rate:
	EtrimPmuWeightedNoCoeffswFDEvtRateGeV->SetLineColor(3);
	EtrimPmuWeightedNoCoeffswFDEvtRateGeV->SetLineWidth(2);
	// w/ coeffs:
	// no FD Event Rate:
	EtrimPmuWeightedCoeffsNoFDEvtRateGeV->SetLineColor(2);
	EtrimPmuWeightedCoeffsNoFDEvtRateGeV->SetLineWidth(2);
	// with FD Event Rate:
	EtrimPmuWeightedCoeffswFDEvtRateGeV->SetLineColor(1);
	EtrimPmuWeightedCoeffswFDEvtRateGeV->SetLineWidth(2);
	// comparison data:
	PRISMDataTimesCoeff->SetLineColor(4);
	PRISMDataTimesCoeff->SetLineWidth(2);

    // print the means of the data as a sanity check that they're not the exact same lines:
	cout << "SelectedEvGeoEffVsE mean = " << SelectedEvGeoEffVsE->GetMean() << endl;
	cout << "EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV mean = " << EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->GetMean() << endl;
	cout << "EtrimPmuWeightedNoCoeffswFDEvtRateGeV mean = " << EtrimPmuWeightedNoCoeffswFDEvtRateGeV->GetMean() << endl;
	cout << "EtrimPmuWeightedCoeffsNoFDEvtRateGeV mean = " << EtrimPmuWeightedCoeffsNoFDEvtRateGeV->GetMean() << endl;
	cout << "EtrimPmuWeightedCoeffswFDEvtRateGeV mean = " << EtrimPmuWeightedCoeffswFDEvtRateGeV->GetMean() << endl;
	cout << "PRISMDataTimesCoeff mean = " << PRISMDataTimesCoeff->GetMean() << endl;

	// now draw them:
	SelectedEvGeoEffVsE->Draw("hist same");
	//EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->Draw("hist same");
	//EtrimPmuWeightedNoCoeffswFDEvtRateGeV->Draw("hist same");
	//EtrimPmuWeightedCoeffsNoFDEvtRateGeV->Draw("hist same");
	//EtrimPmuWeightedCoeffswFDEvtRateGeV->Draw("hist same");
	PRISMDataTimesCoeff->Draw("hist same");

	// make a legend:
	TLegend* legend = new TLegend();
	legend->AddEntry(SelectedEvGeoEffVsE, "FD Geo-Corrected in ND", "l");
	//legend->AddEntry(EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV, "No Coeffs, No FD Event Rate", "l");
	//legend->AddEntry(EtrimPmuWeightedNoCoeffswFDEvtRateGeV, "No Coeffs, w/ FD Event Rate", "l");
	//legend->AddEntry(EtrimPmuWeightedCoeffsNoFDEvtRateGeV, "w/ Coeffs, No FD Event Rate", "l");
	//legend->AddEntry(EtrimPmuWeightedCoeffswFDEvtRateGeV, "w/ Coeffs, w/ FD Event Rate", "l");
	legend->AddEntry(PRISMDataTimesCoeff, "ND Lin Comb PRISM Prediction", "l");
	legend->Draw();
	gPad->Update();


	// now make the ratio plot b/n my histos & no coeffs w/ FD (original/Ioana histo)
	// make a canvas
	TCanvas* CanvasCoeffsRatio = new TCanvas("CanvasCoeffsRatio", "CanvasCoeffsRatio");
	CanvasCoeffsRatio->cd();
	CanvasCoeffsRatio->DrawFrame(0.0, 0.994, 12, 1.007);

	// first clone all the histos before dividing anything
	TH1D* NoCoeffsNoFDvsIoanaRatio = (TH1D*) EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->Clone("NoCoeffsNoFDvsIoanaRatio");
	TH1D* NoCoeffswFDvsIoanaRatio = (TH1D*) EtrimPmuWeightedNoCoeffswFDEvtRateGeV->Clone("NoCoeffswFDvsIoanaRatio");
	TH1D* wCoeffsNoFDvsIoanaRatio = (TH1D*) EtrimPmuWeightedCoeffsNoFDEvtRateGeV->Clone("wCoeffsNoFDvsIoanaRatio");

    // now divide all histos by the original/Ioana histo:
	NoCoeffsNoFDvsIoanaRatio->Divide(SelectedEvGeoEffVsE);
	NoCoeffswFDvsIoanaRatio->Divide(SelectedEvGeoEffVsE);
	wCoeffsNoFDvsIoanaRatio->Divide(SelectedEvGeoEffVsE);

	// some specs: 
	NoCoeffsNoFDvsIoanaRatio->SetLineColor(7);
	NoCoeffsNoFDvsIoanaRatio->SetLineWidth(2);
	NoCoeffswFDvsIoanaRatio->SetLineColor(3);
	NoCoeffswFDvsIoanaRatio->SetLineWidth(2);
	wCoeffsNoFDvsIoanaRatio->SetLineColor(2);
	wCoeffsNoFDvsIoanaRatio->SetLineWidth(2);
	
	// now draw them:
	NoCoeffsNoFDvsIoanaRatio->Draw("hist same");
	NoCoeffswFDvsIoanaRatio->Draw("hist same");
	wCoeffsNoFDvsIoanaRatio->Draw("hist same");
	
	// add a legend:
	TLegend* RatioLeg = new TLegend();
	RatioLeg->AddEntry(NoCoeffsNoFDvsIoanaRatio, "No Coeffs, No FD Event Rate / Ioana (no coeffs, w/ FD)", "l");
	RatioLeg->AddEntry(NoCoeffswFDvsIoanaRatio, "No Coeffs, w/ FD Event Rate / Ioana (no coeffs, w/ FD)", "l");
	RatioLeg->AddEntry(wCoeffsNoFDvsIoanaRatio, "w/ Coeffs, No FD Event Rate / Ioana (no coeffs, w/ FD)", "l");
	RatioLeg->Draw();
    gPad->Update();


	// now make the ratio plot b/n my histos & ND Lin Comb histo:
	// make a canvas:
	TCanvas* CanvasLinCombRatio = new TCanvas("CanvasLinCombRatio", "CanvasLinCombRatio");
	CanvasLinCombRatio->cd();
	CanvasLinCombRatio->DrawFrame(0.0, 0.15, 12, 2);

	// first clone all histos before dividing anything:
	TH1D* NoCoeffsNoFDvsLinCombRatio = (TH1D*) EtrimPmuWeightedNoCoeffsNoFDEvtRateGeV->Clone("NoCoeffsNoFDvsLinCombRatio");
	TH1D* NoCoeffswFDvsLinCombRatio = (TH1D*) EtrimPmuWeightedNoCoeffswFDEvtRateGeV->Clone("NoCoeffswFDvsLinCombRatio");
	TH1D* wCoeffsNoFDvsLinCombRatio = (TH1D*) EtrimPmuWeightedCoeffsNoFDEvtRateGeV->Clone("wCoeffsNoFDvsLinCombRatio");

    // now divide all histos by ND Lin comb histo:
	NoCoeffsNoFDvsLinCombRatio->Divide(PRISMDataTimesCoeff);
	NoCoeffswFDvsLinCombRatio->Divide(PRISMDataTimesCoeff);
	wCoeffsNoFDvsLinCombRatio->Divide(PRISMDataTimesCoeff);

	// some specs:
	NoCoeffsNoFDvsLinCombRatio->SetLineColor(7);
	NoCoeffsNoFDvsLinCombRatio->SetLineWidth(2);
	NoCoeffswFDvsLinCombRatio->SetLineColor(3);
	NoCoeffswFDvsLinCombRatio->SetLineWidth(2);
	wCoeffsNoFDvsLinCombRatio->SetLineColor(2);
	wCoeffsNoFDvsLinCombRatio->SetLineWidth(2);
	
	// now draw them:
	NoCoeffsNoFDvsLinCombRatio->Draw("hist same");
	NoCoeffswFDvsLinCombRatio->Draw("hist same");
	wCoeffsNoFDvsLinCombRatio->Draw("hist same");
	
	// add a legend:
	TLegend* LinCombLeg = new TLegend();
	LinCombLeg->AddEntry(NoCoeffsNoFDvsLinCombRatio, "No Coeffs, No FD Event Rate / ND Lin Comb", "l");
	LinCombLeg->AddEntry(NoCoeffswFDvsLinCombRatio, "No Coeffs, w/ FD Event Rate / ND Lin Comb", "l");
	LinCombLeg->AddEntry(wCoeffsNoFDvsLinCombRatio, "w/ Coeffs, No FD Event Rate / ND Lin Comb", "l");
	LinCombLeg->Draw();
    gPad->Update();
}

