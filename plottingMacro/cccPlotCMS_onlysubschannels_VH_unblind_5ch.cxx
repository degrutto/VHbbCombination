#include "TStyle.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TLatex.h"
#include "TBox.h"
#include "TStyle.h"
#include "TROOT.h"


void cccPlotCMS_onlysubschannels_VH_unblind_5ch(const char *poi = "r", double rMax=17, const char *filename="compatibility3_VH_unblind_5ch.pdf") {
  gROOT->LoadMacro("tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

    //setTDRStyle();
    gStyle->SetPadTickX(0);
    //gStyle->SetPadTickY(0);
    gStyle->SetTickLength(0., "Y");

    TCanvas *c1 = new TCanvas("c1");
    c1->SetLeftMargin(0.35);
    c1->SetGridx(0);

    /*
    
    if (gFile == 0) { std::cout << "No input file open" << std::endl; return; }
    RooFitResult *fit_nominal   = (RooFitResult *) gFile->Get("fit_nominal");
    RooFitResult *fit_alternate = (RooFitResult *) gFile->Get("fit_alternate");
    if (fit_nominal == 0 || fit_alternate == 0) { std::cout << "Input file " << gFile->GetName() << " does not contain fit_nominal or fit_alternate" << std::endl; return; }
    RooRealVar *rFit = (RooRealVar *) fit_nominal->floatParsFinal().find(poi);
    if (rFit == 0)  { std::cout << "Nominal fit does not contain parameter " << poi << std::endl; return; }

    TString prefix =  TString::Format("_ChannelCompatibilityCheck_%s_", poi);


    int nChann = 0;
    TIterator *iter = fit_alternate->floatParsFinal().createIterator();
    for (RooAbsArg *a = (RooAbsArg *) iter->Next(); a != 0; a = (RooAbsArg *) iter->Next()) {
        if (TString(a->GetName()).Index(prefix) == 0) nChann++;
    }
    TH2F frame("frame",";Best fit #sigma/#sigma_{SM};",1,-2,4,nChann+1,0,nChann+1);
    //TH2F frame("frame",";best fit #sigma/#sigma_{SM};",1,rFit->getMin(),TMath::Min(rFit->getMax(),rMax),nChann,0,nChann);

    iter->Reset(); int iChann = 0; TGraphAsymmErrors points(nChann);
    for (RooAbsArg *a = (RooAbsArg *) iter->Next(); a != 0; a = (RooAbsArg *) iter->Next()) {
        if (TString(a->GetName()).Index(prefix) == 0) {
            RooRealVar *ri = (RooRealVar *) a;
            TString channel = a->GetName(); channel.ReplaceAll(prefix,"");
            points.SetPoint(iChann,       ri->getVal(), iChann+0.5);
            points.SetPointError(iChann, -ri->getAsymErrorLo(), ri->getAsymErrorHi(), 0, 0);
            iChann++;
            //std::cout << channel.Data() << std::endl;
            channel.ReplaceAll("Wln",TString::Format("#splitline{#scale[0.95]{W(l#nu)H(bb)}  }{#scale[0.7]{#mu = %.2f_{ %.2f}^{ +%.2f}}}",ri->getVal(),ri->getAsymErrorLo(),ri->getAsymErrorHi()));
            channel.ReplaceAll("Znn",TString::Format("#splitline{#scale[0.95]{Z(#nu#nu)H(bb)}  }{#scale[0.7]{#mu = %.2f_{ %.2f}^{ +%.2f}}}",ri->getVal(),ri->getAsymErrorLo(),ri->getAsymErrorHi()));
            channel.ReplaceAll("Zll",TString::Format("#splitline{#scale[0.95]{Z(l^{-}l^{+})H(bb)}  }{#scale[0.7]{#mu = %.2f_{ %.2f}^{ +%.2f}}}",ri->getVal(),ri->getAsymErrorLo(),ri->getAsymErrorHi()));
            c1->SetTickx(0);
            frame.GetYaxis()->SetBinLabel(iChann, channel);
        }
    }
    */

   int  nChann =5;
   //    TH2F frame("analysis topologies",";Best fit #sigma/#sigma_{SM};analysis topologies",1,-2,4,nChann+1,0,nChann+1);
   //    TH2F frame("analysis topologies",";Best fit #sigma/#sigma_{SM};",1,-2,4,nChann+1,0,nChann+1);
    TH2F frame("analysis_topologies",";Best fit #mu;",1,-1,3.5,nChann+1,0,nChann+1);
    frame.GetYaxis()->SetTitleOffset(2.5);
   


    TGraphAsymmErrors points(nChann);
   

    for (int iChann=0; iChann < nChann; iChann++){
   
      if (iChann==2) {

      TString channel = "XXX";         
      /*
   Nominal fit: r fixed at  1.1900                                                                             
        Alternate fit: r =  1.9216  -0.6003/+0.6078   in channel WlnHbb                                          
        Alternate fit: r =  1.7745  -0.5948/+0.6300   in channel ZllHbb                                          
        Alternate fit: r =  0.0332  -0.5342/+0.5336   in channel ZnnHbb       
      */
      //Expected ∆µ 0.66 0.62 0.58 0.37
      channel.ReplaceAll("XXX",TString::Format("#splitline{#scale[0.95]{0 lept.}  }{#scale[0.7]{#mu = %.1f #pm %.1f}}",0.03,0.54));   
      //       Best fit r: 1.50889  -0.660401/+3.3624  (68% CL)

      points.SetPoint(iChann,  0.03, iChann+0.5);
      points.SetPointError(iChann, 0.53 , 0.54, 0, 0);                                                                                 
	
      // c1->SetTickx(0);
  frame.GetYaxis()->SetBinLabel(iChann+1, channel);  
      }



      if (iChann==0) {

      TString channel = "XXX";         

      channel.ReplaceAll("XXX",TString::Format("#splitline{#scale[0.95]{2 lept.}  }{#scale[0.7]{#mu = %.1f #pm %.1f}}",1.77,0.61));   
      //Best fit r: 1.57375  -101.574/+0.660129  (68% CL)

      points.SetPoint(iChann,  1.77, iChann+0.5);
      points.SetPointError(iChann, 0.60 , 0.61, 0, 0);                                                                                 
      frame.GetYaxis()->SetBinLabel(iChann+1, channel);  
      }


      if (iChann==1) {

      TString channel = "XXX";         
      
      channel.ReplaceAll("XXX",TString::Format("#splitline{#scale[0.95]{1 lept.}}{#scale[0.7]{#mu =  %.1f #pm %.1f}}",1.92,+0.63)); 
      //     Best fit r: 0.659487  -100.659/+0.706337  (68% CL)
  
      points.SetPoint(iChann,  1.92, iChann+0.5);
      points.SetPointError(iChann, +0.59 , +0.63, 0, 0);                                                                                 
      frame.GetYaxis()->SetBinLabel(iChann+1, channel);  
      }


      if (iChann==3) {

	/*      r_WH :    +1.731   -0.681/+0.704 (68%)
	  r_ZH :    +0.921   -0.450/+0.480 (68%)
	*/
      TString channel = "XXX";         
      channel.ReplaceAll("XXX",TString::Format("#splitline{#scale[0.95]{WH(bb)}}{#scale[0.7]{#mu =  %.1f #pm %.1f}}",1.73,0.70));    
      points.SetPoint(iChann,  1.73, iChann+0.5);
      points.SetPointError(iChann, 0.68 , 0.70, 0, 0);                                                                                 
      frame.GetYaxis()->SetBinLabel(iChann+1, channel);  
      }    

      if (iChann==4) {

      TString channel = "XXX";         
      channel.ReplaceAll("XXX",TString::Format("#splitline{#scale[0.95]{ZH(bb)}  }{#scale[0.7]{#mu =  %.1f #pm %.1f}}",0.92,0.48));    
      points.SetPoint(iChann,  1, iChann+0.5);
      points.SetPointError(iChann, 0.45 , +0.48, 0, 0);                                                                                 
      frame.GetYaxis()->SetBinLabel(iChann+1, channel);  
      }

      if (iChann==5) {

      TString channel = "XXX";         
      channel.ReplaceAll("XXX",TString::Format("#splitline{#scale[0.95]{ggZH(bb)}  }{#scale[0.7]{#mu =  %.2f #pm %.2f}}",1.,0.68));    
      points.SetPoint(iChann,  1, iChann+0.5);
      points.SetPointError(iChann, 0.68 , +0.68, 0, 0);                                                                                 
      frame.GetYaxis()->SetBinLabel(iChann+1, channel);  
      }




      }



    points.SetLineColor(kRed);
    points.SetLineWidth(5);
    points.SetMarkerStyle(21);
    points.SetMarkerSize(1.7);
    frame.GetXaxis()->SetTitleSize(0.05);
    frame.GetXaxis()->SetLabelSize(0.04);
    frame.GetXaxis()->SetNdivisions(505);
    frame.GetYaxis()->SetLabelSize(0.06);
    frame.Draw(); gStyle->SetOptStat(0);
    TBox globalFitBand(1.19 -0.38, 0, 1.19 + 0.40, nChann);
    //globalFitBand.SetFillStyle(3013);
    globalFitBand.SetFillStyle(1001);
    //globalFitBand.SetFillColor(65);
    globalFitBand.SetFillColor(kGreen);
    globalFitBand.SetLineStyle(0);
    globalFitBand.DrawClone();
    TLine globalFitLine(1.19, 0, 1.19, nChann);
    globalFitLine.SetLineWidth(4);
    //globalFitLine.SetLineColor(214);
    globalFitLine.SetLineColor(1);
    globalFitLine.DrawClone();


    TLine sepLine(-1, 3., 3.5, 3. );
    sepLine.SetLineWidth(1);
    //globalFitLine.SetLineColor(214);
    sepLine.SetLineColor(1);
    sepLine.SetLineStyle(kDashed);

    sepLine.DrawClone();



    points.Draw("P SAME");
    frame.Draw("AXIS SAME");

    //TLatex l;
    //l.SetNDC();
    //l.SetTextAlign(12);
    //l.SetTextSize(0.032);
    //l.DrawLatex(0.73,0.90,"CMS Preliminary");
    //TLatex ll;
    //ll.SetNDC();
    //ll.SetTextAlign(12);
    //ll.SetTextFont(42);
    //ll.SetTextSize(0.026);
    ////ll.DrawLatex(0.73,0.86,"#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
    //ll.DrawLatex(0.73,0.86,"#sqrt{s} = 8 TeV, L = 12.1 fb^{-1}");
    //ll.DrawLatex(0.73,0.82,"m_{H} = 125 GeV");
    ////ll.DrawLatex(0.73,0.82,"#sqrt{s} = 8 TeV, L = 12.1 fb^{-1}");
    ////ll.DrawLatex(0.73,0.78,"m_{H} = 125 GeV");

    TLatex l;
    l.SetNDC();
    l.SetTextAlign(12);
    l.SetTextFont(42);
    l.SetTextSize(0.03);
    //    l.DrawLatex(0.35,0.97,"#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
    //l.DrawLatex(0.66,0.97,"#sqrt{s} = 8 TeV, L = 19.0 fb^{-1}");
    //l.DrawLatex(0.66,0.97,"#sqrt{s} = 13 TeV, L = 35.9 fb^{-1}");
l.DrawLatex(0.74,0.97,"35.9 fb^{-1} (13 TeV)");
 l.DrawLatex(0.38,0.84,TString::Format("#scale[0.95]{Combined}#scale[1.2]{ #mu = %.1f #pm %.1f }",1.2, 0.4));    
   
    TLatex ll;
    ll.SetNDC();
    ll.SetTextAlign(12);
    ll.SetTextFont(42);
    ll.SetTextSize(0.04);
    ll.DrawLatex(0.38,0.91,"CMS Preliminary");
    ll.SetTextSize(0.03);
    ll.DrawLatex(0.38,0.88,"pp #rightarrow VH; H #rightarrow b#bar{b} ");

    //    ll.DrawLatex(0.7,0.92,"m_{H} = 125 GeV");




    c1->SetFillStyle(4000);
	  c1->SetFrameFillStyle(1000);
	  c1->SetFrameFillColor(0);



  c1->Print(filename);
  c1->Print("ccc.C");
}

