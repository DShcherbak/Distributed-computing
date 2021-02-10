#include "SQRT.h"


std::pair<std::vector<std::vector<double>>,std::vector<std::vector<double>>>  find_triangle_sqrt(const std::vector<std::vector<double>> &A){
    int n = A.size();
    std::vector<std::vector<double>> S(n, std::vector<double>(n));
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    for(int i = 0; i < n; i++){
        double sum = A[i][i];
        for(int j = 0; j < i; j++){
            sum -= S[j][i] * S[j][i] * d[j][j];
        }
        d[i][i] = sum > 0 ? 1 : (sum < 0 ? -1 : 0);
        S[i][i] = sqrt(std::abs(sum));
        for(int j = i + 1; j < n; j++){
            sum = A[i][j];
            for(int p = 0; p < i; p++){
                sum -= S[p][i] * d[p][p] * S[p][j];
            }
            S[i][j] = sum / (S[i][i] * d[i][i]);
        }
    }
    std::vector<std::vector<double>> StD(n, std::vector<double>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            StD[i][j] = S[j][i] * d[j][j];
        }
    }
    return {S, StD};
}

std::vector<double> last_col(const std::vector<std::vector<double>> & A){
    int n = A.size();
    std::vector<double> result(n);
    for(int i = 0; i < n; i++){
        result[i] = A[i][n];
    }
    return result;
}

std::vector<double> solve_upper_triangle(const std::vector<std::vector<double>> & A, const std::vector<double> & b){
    int n = A.size();
    if(n == 0)
        return {};
    std::vector<double> rev_x;
    for(int i = n - 1; i >= 0; i--){
        double sum = b[i];
        for(int j = n - 1; j > i; j--){
            sum -= A[i][j] * rev_x[(n-1) - j];
        }
        rev_x.push_back(sum / A[i][i]);
    }
    std::vector<double> x(n);
    for(int i = 0; i < n; i++){
        x[i] = rev_x[n-1-i];
    }
    return x;
}


std::vector<double> solve_lower_triangle(const std::vector<std::vector<double>> & A, const std::vector<double> & b){
    int n = A.size();
    if(n == 0)
        return {};
    std::vector<double> x;
    for(int i = 0; i < n; i++){
        double sum = b[i];
        for(int j = 0; j < i; j++){
            sum -= A[i][j] * x[j];
        }
        x.push_back(sum / A[i][i]);
    }
    return x;
}


std::vector<double> solve_SQRT_main(const std::vector<std::vector<double>> &A){
    auto p = find_triangle_sqrt(A);
    auto S = p.first;
    auto StD = p.second;
    std::vector<double> y = solve_lower_triangle(StD, last_col(A));
    std::vector<double> x = solve_upper_triangle(S, y);
    return x;
}
