
//
// Created by Hongxi on 16/12/2020.
//
#include <utility>
#include <fstream>
#include "float.h"
#include "reproducibility.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace std::chrono;
using namespace Eigen;

double
pairwise_distance(vector<MatrixXd> all_strata, string similarity_method,
                  bool print_time = true) {
    transform(similarity_method.begin(), similarity_method.end(),
              similarity_method.begin(), ::tolower);

    high_resolution_clock::time_point t0, t1, t2, t3, t4;
    MatrixXd zscores;

    int n_cells = all_strata[0].rows(), n_bins = all_strata[0].cols();
    int all_size = all_strata.size();
    MatrixXd distance_mat(n_cells, n_cells);
    t0 = high_resolution_clock::now();
    if (similarity_method == "hicrep") {

        int n_strata = all_strata.size();
        int score_col = 0;
        MatrixXd weighted_std = MatrixXd::Zero(n_cells, n_bins);
        int i = 0;
        for (auto stratum : all_strata) {

            MatrixXd mean = stratum.rowwise().mean();
            MatrixXd std = ((stratum.colwise() -
                             stratum.rowwise().mean()).array().square().rowwise().sum() /
                            (stratum
                                    .cols())).sqrt();
            weighted_std.col(i) = (n_bins - i) * std;
            all_strata[i] -= mean.replicate(1, n_bins);
//            cout << all_strata[i] << endl;
            i++;
            score_col += stratum.cols();
        }
        t1 = high_resolution_clock::now();

        MatrixXd scores(n_cells, score_col);
        scores << all_strata[0], all_strata[1], all_strata[2],
                all_strata[3], all_strata[4], all_strata[5],
                all_strata[6], all_strata[7], all_strata[8],
                all_strata[9];

        t2 = high_resolution_clock::now();
        MatrixXd tmp1 = (scores * scores.transpose()), tmp2 = (weighted_std *
                                                               (weighted_std.transpose()));

        for (int i = 0; i < n_cells; i++)
            for (int j = 0; j < n_cells; j++) {
                int tmpdiv = tmp1(i, j) / tmp2(i, j);
                if (tmpdiv > 1) distance_mat(i, j) = 0.0;
                else if (tmpdiv < -1) distance_mat(i, j) = 4.0;
                else distance_mat(i, j) = 2 - 2.0 * tmpdiv;
            }

        t3 = high_resolution_clock::now();

    } else {
        throw "Method {0} not supported. Only \"inner_product\", \"HiCRep\", \"old_hicrep\" and \"Selfish\".";
    }


    std::chrono::duration<double, std::milli> duration1 = (t1 - t0);
    std::chrono::duration<double, std::milli> duration2 = (t2 - t1);
    std::chrono::duration<double, std::milli> duration3 = (t3 - t2);
//    std::chrono::duration<double, std::milli> duration4 = (t4 - t3);
    std::chrono::duration<double, std::milli> duration_total = (t3 - t0);
    double tout = duration_total.count();
    cout << "Time 1:" << duration1.count() << endl
         << "Time 2:" << duration2.count() << endl
         << "Time 3:" << duration3.count() << endl
         //         << "Time 4:" << duration4.count() << endl
         << "total: " << tout << endl;
    cout << distance_mat;
    return tout;
}


