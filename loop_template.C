#include "bxdata.C"

int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "Format: ./loop_template input.root output.root" << endl;
        return 1;
    }

    string fname = argv[1]; // filename to analyse
    string outname  = argv[2]; // output filename
    cout << "Future output file: " << outname << endl;

    // BxData object
    BxData* bxdata = new BxData(fname);

    // loop over events and apply conditions
    bxdata->Loop();

    // save histograms
    bxdata->SaveHistos(outname);
}
