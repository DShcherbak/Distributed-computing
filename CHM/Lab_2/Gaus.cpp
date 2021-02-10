#include "Gaus.h"


#include <iostream>
#include <vector>

std::pair<int, int> find_maximum(std::vector<std::vector<double>> M){
    int n = M.size();
    if(n <= 0)
        return {0,0};
    std::pair<int, int> ij = {0,0};
    int m = M[0].size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m - 1; j++){
            if(M[i][j] > M[ij.first][ij.second])
                ij = {i,j};
        }
    }
    return ij;
}

std::pair<std::vector<double>, std::vector<std::vector<double>>> extract_row(std::vector<std::vector<double>> M, std::pair<int, int> ij){
    int n = M.size();
    if(n <= 0)
        return {{}, {}};
    int m = M[0].size();
    int I = ij.first, J = ij.second;
    for(int i = 0; i < n; i++){
        if(i == I)
            continue;
        double p = M[i][J]/M[I][J];
        for(int j = 0; j < m; j++){
            M[i][j] -= M[I][j] * p;
        }
    }
    int id = -1;
    std::vector<std::vector<double>> M_next;
    for(int i = 0; i < n; i++){
        if(i == I)
            continue;
        M_next.emplace_back();
        id++;
        for(int j = 0; j < m; j++){
            if(j == J)
                continue;
            M_next[id].push_back(M[i][j]);
        }
    }
    return {M[I], M_next};
}

std::vector<double> find_new_x(std::vector<double> row, std::vector<double> x, int J){
    std::vector<double> result;
    double sum = 0;
    for(int j = 0; j < J; j++){
        sum -= x[j] * row[j];
        result.push_back(x[j]);
    }
    result.push_back(0);
    for(int j = J + 1; j < row.size() - 1; j++){
        sum -= x[j-1] * row[j];
        result.push_back(x[j-1]);
    }
    sum += row[row.size() - 1];
    result[J] = sum / row[J];
    return result;
}


std::vector<double> solve_Gause_main(std::vector<std::vector<double>> M) {
    if(M.size() == 1)
        return {M[0][1] / M[0][0]};
    std::pair<int,int> ij = find_maximum(M);
    auto p = extract_row(M, ij);
    std::vector<double> row = p.first;
    std::vector<std::vector<double>> M_next = p.second;
    std::vector<double> xs = solve_Gause_main(M_next);
    return find_new_x(row, xs, ij.second);

}