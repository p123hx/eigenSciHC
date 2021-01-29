#include "xtensor/xio.hpp"
#include "../load/ContactMaps.h"
#include "../embedding/reproducibility.h"
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
using namespace std;using namespace Eigen;

double fastHicP(vector<MatrixXd> all_strata) {

    double times
            =
            pairwise_distance(all_strata, "hicrep");

    return times;
}
vector<string> f100() {
    return  vector<string>{"../../Nagano/1CDX_cells/1CDX1.1/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.185/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.281/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.38/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.46/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.117/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.202/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.294/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.377/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.465/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.108/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.182/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.263/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.352/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.68/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.154/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.237/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.312/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.392/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.468/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.101/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.186/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.283/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.381/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.464/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.12/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.203/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.295/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.382/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.466/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.11/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.183/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.264/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.353/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.72/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.155/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.24/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.313/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.393/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.47/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.102/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.187/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.284/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.383/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.466/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.121/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.204/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.296/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.383/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.467/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.111/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.185/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.265/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.354/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.73/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.156/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.241/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.314/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.394/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.472/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.103/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.191/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.285/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.384/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.468/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.122/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.205/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.297/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.384/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.468/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.112/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.186/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.266/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.355/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.74/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.157/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.242/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.315/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.396/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.473/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.104/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.192/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.286/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.385/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX1.47/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.123/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.206/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.3/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.385/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX2.47/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.113/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.187/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.267/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.356/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX3.75/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.158/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.243/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.316/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.397/new_adj",
                                      "../../Nagano/1CDX_cells/1CDX4.474/new_adj"};
}
int main(){
//    vector<string> fileLst{"../test/data/cell_03","../test/data/cell_01","../test/data/cell_02"};
    vector<string> fileLst100 = f100();

    string operation = "convolution";
    scHiCs y = scHiCs(fileLst100, "mm9", 500000, 3, 4000000, true, "except Y",
                      "shortest_score",
                      10, true,
                      operation);
    vector<string> chrs{"chr1", "chr2", "chrX", "chr3", "chr4", "chr5", "chr6", "chr7",
                        "chr8", "chr9", "chr10", "chr11", "chr12", "chr13", "chr14",
                        "chr15", "chr16", "chr17", "chr18", "chr19"}; //since "except Y"
    double tsum = 0.0;

    for(int i=10;i>0;i--){
        for (string s:chrs) {
            cout << "\n" << s << ":\n";
            vector<MatrixXd> chr = y.get_strata()[s];
            tsum += (fastHicP(chr));
        }
    }

    cout << "Total average out of 10 fastHiCrep 100cells " << tsum/10 << " in "
                                                                     "milliseconds\n";
    ofstream fout("100out.txt");
    fout<< "Total average out of 10 fastHiCrep 100cells " << tsum/10 << " in "
                                                                          "milliseconds\n";
    fout.close();
}