#ifndef LAB_2_GAUS_H
#define LAB_2_GAUS_H

#include <iostream>
#include <vector>

std::pair<int, int> find_maximum(std::vector<std::vector<double>> M);

std::pair<std::vector<double>, std::vector<std::vector<double>>> extract_row(std::vector<std::vector<double>> M, std::pair<int, int> ij);

std::vector<double> find_new_x(std::vector<double> row, std::vector<double> x, int J);


std::vector<double> solve_Gause_main(std::vector<std::vector<double>> M);
#endif //LAB_2_GAUS_H
