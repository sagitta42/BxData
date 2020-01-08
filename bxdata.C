#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "/storage/gpfs_data/borexino/users/mredchuk/offline_RefVersions/offline_c19/Echidna/event/BxEvent.hh"

using namespace std;

class BxData{
    public:
        BxData(string name);

        void Loop();
        void SaveHistos(string fname);


    private:
        TFile* f; // the root file
        TTree* t; // the bxtree
        int tentries;
        BxEvent* ev; // event pointer for the loop

        TH1D* h[10]; // histograms of interest
        int nhistos;
};

BxData::BxData(string name){
    // read bxtree
    cout << "Analysing file: " << name << endl;
    cout << "------------------------" << endl;
    f = TFile::Open(name.c_str());
    f->GetObject("bxtree", t);
    ev = new BxEvent();
    t->SetBranchAddress("events", &ev);
    tentries = t->GetEntries();

    // initialize histograms
    nhistos = 2;
    h[0] = new TH1D("npmts", "npmts", 2000, 0, 2000);
    h[1] = new TH1D("npmts_norm", "npmts_norm", 2000, 0, 2000);
}

void BxData::Loop(){
    /* loop over root file and analyse events */

    for(int i = 0; i < tentries; i++){
        t->GetEntry(i);

        // ------------- insert your conditions and histo fillings here

        if(ev->GetLaben().GetNClusters() != 1) continue;

        h[0]->Fill(ev->GetLaben().GetCluster(0).GetNPmts());
        h[1]->Fill(ev->GetLaben().NormalizePmts(ev->GetLaben().GetCluster(0).GetNPmts()));

        // ------------- insert your conditions and histo fillings here

        if(i % 10000 == 0) cout << i << "/" << tentries << endl; // occasional printout
    }
}

void BxData::SaveHistos(string fname){
    /* save histograms to file called fname */
    cout << "------------------------" << endl;
    cout << "Saving histos to file: " << fname << endl;
    TFile* out = TFile::Open(fname.c_str(), "recreate");

    for(int i = 0; i < nhistos; i++){
        h[i]->Write();
        cout << "..." << h[i]->GetName() << endl;
    }

    out->Close();
    cout << "------------------------" << endl;
}







