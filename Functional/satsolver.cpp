#include "SATSolver.h"
#include "DIMACSParser.h"
#include <algorithm> // For std::remove

// Constructor to initialize SATSolver with DIMACSParser
SATSolver::SATSolver(const string& filename) {
    DIMACSParser parser(filename);
    numLiterals = parser.getNumLiterals();
    numClauses = parser.getNumClauses();
    clauses = parser.getClauses(); // No changes needed here
}

void SATSolver::unitPropagation(vector<int>& assignment) {
    bool changed;
    do {
        changed = false;
        
        // Check for direct contradictions in unit clauses
        for (size_t i = 0; i < clauses.size(); i++) {
            if (clauses[i].size() == 1) {
                int unit = clauses[i][0];
                for (size_t j = i + 1; j < clauses.size(); j++) {
                    if (clauses[j].size() == 1 && clauses[j][0] == -unit) {
                        cout << "Direct contradiction in unit clauses: " << unit << " and " << -unit << endl;
                        clauses = {vector<int>()};
                        return;
                    }
                }
            }
        }

        // Process unit clauses
        for (auto it = clauses.begin(); it != clauses.end();) {
            if (it->size() == 1) {
                int unit = (*it)[0];
                cout << "Propagating unit: " << unit << endl;
                assignment.push_back(unit);
                
                // Remove unit clause and simplify remaining clauses
                it = clauses.erase(it);
                vector<vector<int>> newClauses;
                
                for (const auto& clause : clauses) {
                    // Skip if clause is satisfied
                    if (find(clause.begin(), clause.end(), unit) != clause.end()) {
                        continue;
                    }
                    
                    // Remove negated literals
                    vector<int> newClause;
                    for (int lit : clause) {
                        if (lit != -unit) {
                            newClause.push_back(lit);
                        }
                    }
                    
                    if (!newClause.empty()) {
                        newClauses.push_back(newClause);
                    }
                }
                
                clauses = newClauses;
                changed = true;
                break;
            } else {
                ++it;
            }
        }
    } while (changed);
}

// Utility: Eliminate pure literals
void SATSolver::eliminatePureLiterals(vector<int>& assignment) {
    vector<int> literalCounts(numLiterals + 1, 0);

    // Count occurrences of each literal
    for (const auto& clause : clauses) {
        for (int literal : clause) {
            literalCounts[abs(literal)] += (literal > 0) ? 1 : -1;
        }
    }

    // Identify and eliminate pure literals
    for (int i = 1; i <= numLiterals; ++i) {
        if (literalCounts[i] > 0) {
            cout << "Pure literal found: " << i << endl;
            assignment.push_back(i); // Pure positive literal
            clauses.erase(std::remove_if(clauses.begin(), clauses.end(),
                                         [i](const vector<int>& clause) {
                                             return std::find(clause.begin(), clause.end(), i) != clause.end();
                                         }),
                          clauses.end());
        } else if (literalCounts[i] < 0) {
            cout << "Pure literal found: " << -i << endl;
            assignment.push_back(-i); // Pure negative literal
            clauses.erase(std::remove_if(clauses.begin(), clauses.end(),
                                         [i](const vector<int>& clause) {
                                             return std::find(clause.begin(), clause.end(), -i) != clause.end();
                                         }),
                          clauses.end());
        }
    }
}

// Utility: Check if there is an empty clause
bool SATSolver::checkEmptyClause() const {
    if (clauses.empty()) {
        // All clauses are satisfied
        return false;
    }
    for (const auto& clause : clauses) {
        if (clause.empty()) {
            // An empty clause exists
            return true;
        }
    }
    return false;
}

bool SATSolver::checkContradictions() {
    // Check for pairs of complementary literals in binary clauses
    for (size_t i = 0; i < clauses.size(); i++) {
        if (clauses[i].size() == 2) {
            int lit1 = clauses[i][0];
            int lit2 = clauses[i][1];
            
            // Look for complementary pair
            for (size_t j = i + 1; j < clauses.size(); j++) {
                if (clauses[j].size() == 2) {
                    // Check all combinations for contradiction
                    if ((clauses[j][0] == -lit1 && clauses[j][1] == -lit2) ||
                        (clauses[j][0] == -lit2 && clauses[j][1] == -lit1)) {
                        cout << "Found contradiction in binary clauses" << endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void SATSolver::printClauses() const {
    cout << "Clauses:" << endl;
    for (const auto& clause : clauses) {
        for (int literal : clause) {
            cout << literal << " ";
        }
        cout << "0" << endl;
    }
}

vector<vector<int>> SATSolver::getClauses() const {
    return clauses;
}