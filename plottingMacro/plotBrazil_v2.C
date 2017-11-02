#include "TStyle.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"
#include "TLine.h"
#include "TLatex.h"
#include "TBox.h"
#include "TStyle.h"
#include "TROOT.h"


void plotBrazil_v2()

{


  gROOT->LoadMacro("tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");


      



   int n_points=4;
   //   string y_vals[n_points]={"Z(ll) H(bb)", "W(l#nu) H(bb)", "Z(#nu#nu) H(bb)", "VH(bb)combined" };



// double y_vals_ep[n_points]={112.5, 117.5, 122.5, 127.5 };
   //  double y_vals[n_points]={115,120,125,130, 135};
   
  TCanvas * c1 = new TCanvas;



// VHbb 7+8TeV for lHCP

//   string y_labs[n_points]={"VH(bb) comb.","2 lept.", "1 lept.", "0 lept." };

  double x_injected[4]=     {  2.1006 ,   0.9668 ,   1.3915  , 1.7551   };
  double x_observed[4]=     { 1.87  ,   3.13 ,   3.38  , 1.22  };
  double x_dow42[4]= { 0.3203  ,   0.4958 ,   0.6861  , 0.5644  };
  double x_dow41[4]= { 0.4313  ,   0.6765 ,   0.9147  , 0.7615  };
  double x_vals[4]=         { 0.704  ,   1.19 ,   1.34  , 1.31  };
  double x_up_points1[4]=   { 0.8665  ,   1.6263 ,   1.7916  , 1.5409  };
  double x_up_points2[4]=   { 1.1921  ,   2.5305 ,   2.4374  , 2.1274    };



 double y_vals[4]={1, 2 , 3, 4 };
double y_vals_e[4]={0.4, 0.4, 0.4, 0.4 };
double y_vals_em[4]={0.4, 0.4, 0.4, 0.4 };
double y_vals_ep[4]={0.4, 0.4, 0.4, 0.4 };



    // Prepare errorbars
    double* x_down_bars2 = new double[4];
    double* x_down_bars1 = new double[4];
    double* x_up_bars1 = new double[4];
    double* x_up_bars2 = new double[4];

    for (int i=0;i<4;++i){
        x_down_bars2[i]=x_vals[i]-x_dow42[i];
        x_down_bars1[i]=x_vals[i]-x_dow41[i];   
        x_up_bars2[i]=x_up_points2[i]-x_vals[i];
        x_up_bars1[i]=x_up_points1[i]-x_vals[i];
        }

    // bline
    //    m_y_line_graph = new TGraph(4, y_vals, x_vals);
    m_y_line_graph = new TGraphErrors(4, x_vals, y_vals, 0 , y_vals_e);
    m_y_line_graph->SetLineWidth(2);
    m_y_line_graph->SetLineStyle(2);
    m_y_line_graph->SetFillColor(kWhite);
    //    m_y_line_graph->GetXaxis()->SetRangeUser(107.5, 127.5); 



    m_y_lineObs_graph = new TGraphErrors(4, x_vals, x_observed , 0, y_vals_e );
    m_y_lineObs_graph->SetLineWidth(2);
    m_y_lineObs_graph->SetFillColor(kWhite);


    m_y_lineSI_graph = new TGraph(4, x_vals, x_injected);
    m_y_lineSI_graph->SetLineWidth(2);
    m_y_lineSI_graph->SetLineColor(kRed);
    m_y_lineSI_graph->SetLineStyle(2);
    m_y_lineSI_graph->SetFillColor(kWhite);


    // y band 1 sigma
    m_x_band_graph_1sigma = new TGraphAsymmErrors( 4,
                                                  x_vals,
                                                  y_vals,
                                                  x_down_bars1,
                                                  x_up_bars1,
						  y_vals_em,
                                                  y_vals_ep);
    m_x_band_graph_1sigma->SetFillColor(kGreen);
    m_x_band_graph_1sigma->SetLineColor(kGreen);
    m_x_band_graph_1sigma->SetMarkerColor(kGreen);

    // y band 2 sigma
    m_x_band_graph_2sigma = new TGraphAsymmErrors( 4,
                                                  x_vals,
                                                  y_vals,
						  x_down_bars2,
                                                  x_up_bars2,
						  y_vals_em,
                                                  y_vals_ep);
    m_x_band_graph_2sigma->SetFillColor(kYellow);
    m_x_band_graph_2sigma->SetFillColor(kYellow);
    m_x_band_graph_2sigma->SetLineColor(kYellow);
    m_x_band_graph_2sigma->SetMarkerColor(kYellow);
    //    m_x_band_graph_2sigma->GetYaxis()->SetTitle("");
    //    m_x_band_graph_2sigma->GetYaxis()->SetTitleOffset(1.2);
    // m_x_band_graph_2sigma->GetYaxis()->SetTitleSize(0.05);
    //m_x_band_graph_2sigma->GetYaxis()->SetTitle("r=#sigma_{95%CL}/#sigma_{SM}");
    m_x_band_graph_2sigma->GetXaxis()->SetTitle("95% Asymptotic CL Limit on #sigma/#sigma_{SM}");
         m_x_band_graph_2sigma->GetXaxis()->SetTitleOffset(1.2);
    m_x_band_graph_2sigma->GetXaxis()->SetTitleSize(0.05);


    m_legend = new TLegend(0.65,0.70,0.95,0.90);
    m_legend->SetName("SM exclusion");
    // uncomment for ob as well     
    m_legend->AddEntry(m_y_lineObs_graph,"CL_{S} Observed");
      //          m_legend->AddEntry(m_y_lineSI_graph,"CL_{S} H125 injected");
    m_legend->AddEntry(m_y_line_graph,"CL_{S} Expected");
    m_legend->AddEntry(m_x_band_graph_1sigma,"CL_{S} Expected #pm 1 #sigma");
    m_legend->AddEntry(m_x_band_graph_2sigma,"CL_{S} Expected #pm 2 #sigma");
    //    m_legend->SetLineColor(kBlack);
    //m_legend->SetBorderSize(1);

    m_legend->SetFillColor(0);

    delete[] x_down_bars2;
    delete[] x_down_bars1;
    delete[] x_up_bars2;
    delete[] x_up_bars1;

    //      TCanvas * c1 = new TCanvas;
    //    TCanvas *c1 = new TCanvas("c1","c1", 300,300,700,500);
     c1->cd();

     //     c1->SetGridx();
     //c1->SetGridy();

     int opt=4;


     TAxis *ax =  m_x_band_graph_2sigma->GetHistogram()->GetYaxis();

   Double_t nb = ax->GetNbins();
   std::cout << ";n of bins is " << nb << std::endl;

   Double_t x1 = ax->GetBinLowEdge(1);
   std::cout << ";low edge is " << x1 << std::endl;

   Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
   std::cout << ";up edge is " << x2 << std::endl;
   //   m_x_band_graph_2sigma->GetHistogram()->GetXaxis()->Set(4,107.5,127.5);



    // hlab->Draw();




    //      m_y_line_graph->GetXaxis()->SetRangeUser(107.5, 127.5); 
    //  m_x_band_graph_2sigma->GetXaxis()->SetRangeUser(107.5, 127.5); 
    //  m_x_band_graph_1sigma->GetXaxis()->SetRangeUser(107.5, 127.5); 




     // Bands
     if (opt==4){

         m_x_band_graph_2sigma->Draw("AP2");
         m_x_band_graph_1sigma->Draw("P2");
	 m_x_band_graph_1sigma->SetMaximum(7);
         }
     else{
         m_x_band_graph_2sigma->Draw("4");
         m_x_band_graph_1sigma->Draw("4");
         }


     // Lines
     if (opt==4){
	 m_y_line_graph->SetMaximum(7);
         m_y_line_graph->Draw("P");
     }
     else{
         m_y_line_graph->Draw("C");
     }



    
   m_y_lineObs_graph->SetMarkerStyle(15);
   m_y_lineObs_graph->SetMarkerSize(1.1);

   // uncommnet for obs as well
        m_y_lineObs_graph->Draw("P");
          m_y_lineObs_graph->SetTitle(" ");


	  //	  	    m_y_lineSI_graph->Draw("same");
	            m_y_lineSI_graph->SetTitle(" ");
     
		    m_one_line = new TLine(0,1.5 , 6 ,1.5);

		        m_one_line->SetLineColor(2);
			//  m_one_line->Draw("Same");
		    //m_three_line->SetLineStyle(kDashed);
		    //m_three_line->Draw("Same");

     // Legen
     m_x_band_graph_2sigma->SetMaximum(7);
     m_legend->Draw("Same");


     //      m_y_line_graph->GetXaxis()->SetRangeUser(107.5, 127.5); 
     //m_x_band_graph_2sigma->GetXaxis()->SetRangeUser(107.5, 127.5); 
     // m_x_band_graph_1sigma->GetXaxis()->SetRangeUser(107.5, 127.5); 



TLatex l;
l.SetNDC();

l.SetTextAlign(31); // align right
  l.SetTextSize(0.04);
  // l.SetTextSizePixels(24);
  //l.SetTextFont(42);

  l.SetTextAlign(11); // align left

  //  l.DrawLatex(0.15,0.90,"CMS Preliminary");


//l.DrawLatex(0.17,0.83,"CMS, BDT analysis");
l.DrawLatex(0.20,0.90,"CMS Preliminary");
//l.DrawLatex(0.17,0.85,"CMS Preliminary, M_{JJ} analysis");
//
//l.DrawLatex(0.20,0.85,"#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
//l.DrawLatex(0.20,0.80,"#sqrt{s} = 8 TeV, L = 19.0 fb^{-1}");
l.DrawLatex(0.20,0.80,"#sqrt{s} = 13 TeV, L = 35.9 fb^{-1}");

//  l.DrawLatex(0.15,0.96,"CMS Preliminary #sqrt{s} = 8 TeV, L = 5.0 fb^{-1} #sqrt{s} = 8 TeV, L = 12.1 fb^{-1}");

  //l.DrawLatex(0.20,0.85,"#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
  //l.DrawLatex(0.20,0.80,"#sqrt{s} = 8 TeV, L = 12.1 fb^{-1}");
//l.DrawLatex(0.20,0.85,"#sqrt{s} = 8 TeV, L = 5  fb^{-1}");
//l.DrawLatex(0.17,0.74,"Z#mu#muH(bb)");
//l.DrawLatex(0.17,0.74,"ZeeH(bb)");
//l.DrawLatex(0.17,0.74,"We#nuH(bb)");
//l.DrawLatex(0.17,0.74,"W#mu#nuH(bb)");
//l.DrawLatex(0.20,0.80,"Z #rightarrow #nu#nu H ");
//l.DrawLatex(0.20,0.80,"VH(bb), MJJ combined");
l.SetTextSize(0.03);
l.DrawLatex(0.20,0.75,"VH(bb) combined, m_{H}=125 GeV");
// m_y_line_graph->GetXaxis()->SetRangeUser(107.7, 127.5); 
 //l.SetShadowColor(0);



   string y_labs[4]={"VH(bb) comb.","2 lept.", "1 lept.", "0 lept." };

    //    TH1F * hlab = m_y_line_graph->GetHistogram();
      TLatex t;
           t.SetTextAngle(30);
       t.SetTextSize(0.025);
           t.SetTextAlign(33);
      double x = gPad->GetUxmin() - 0.1*m_x_band_graph_1sigma->GetXaxis()->GetBinWidth(1);

      //      m_x_band_graph_2sigma->GetHistogram()->GetYaxis()->SetNbins(4);

          for(int i=0; i<4; i++){

	    // y = m_y_line_graph->GetHistogram()->GetYaxis()->GetBinCenter(i+1);
	    t.DrawText(x , 1+i ,y_labs[i].c_str());
            


      }
                 m_y_line_graph->GetHistogram()->GetYaxis()->SetLabelSize(0);
		 m_x_band_graph_2sigma->GetHistogram()->GetYaxis()->SetLabelSize(0) ;
              m_x_band_graph_1sigma->GetHistogram()->GetYaxis()->SetLabelSize(0) ;

                 m_y_line_graph->GetHistogram()->GetYaxis()->SetNdivisions(0);
                 m_y_line_graph->GetHistogram()->GetYaxis()->SetNdivisions(0);
		 m_x_band_graph_2sigma->GetHistogram()->GetYaxis()->SetNdivisions(0) ;


    //   hlab->SetMaximum(5);



 c1->RedrawAxis();
    c1->Modified();
    c1->Update();

    c1->SaveAs("limits2016_v2.pdf");
    } 
