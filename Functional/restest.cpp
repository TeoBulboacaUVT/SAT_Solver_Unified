#include "resolutionsolver.cpp"
#include "SATSolver.cpp"
#include "DIMACSParser.cpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Specify the path to a DIMACS CNF file
    string filename = "C:\\Users\\Lenovo\\Desktop\\UVT\\Sem 2\\MPI Project\\New folder\\Functional\\test2.cnf";

    // Create an instance of ResolutionSolver
    ResolutionSolver solver(filename);

    // Test: Solve the SAT problem using resolution
    cout << "Testing Resolution Solver on file: " << filename << endl;
    bool result = solver.solve();

    // Output the result
    if (result) {
        cout << "The formula is SATISFIABLE." << endl;
    } else {
        cout << "The formula is UNSATISFIABLE." << endl;
    }

    return 0;
}