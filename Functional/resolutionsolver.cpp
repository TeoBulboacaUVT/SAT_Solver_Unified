#include "SATSolver.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class ResolutionSolver : public SATSolver {
public:
    ResolutionSolver(const string& filename) : SATSolver(filename) {}

    bool solve(){
        cout << "Solving using Resolution..." << endl;

        // Convert clauses to sets for easier resolution
        vector<set<int>> clauseSets;
        for (const auto& clause : clauses) {
            clauseSets.push_back(set<int>(clause.begin(), clause.end()));
        }

        while (true) {
            vector<set<int>> newClauses;

            // Generate all resolvents
            for (size_t i = 0; i < clauseSets.size(); i++) {
                for (size_t j = i + 1; j < clauseSets.size(); j++) {
                    set<int> resolvent;
                    if (resolve(clauseSets[i], clauseSets[j], resolvent)) {
                        // If the resolvent is empty, UNSAT is detected
                        if (resolvent.empty()) {
                            cout << "UNSATISFIABLE" << endl;
                            return false;
                        }
                        newClauses.push_back(resolvent);
                    }
                }
            }

            // Check if new clauses are already in the set of clauses
            bool addedNewClause = false;
            for (const auto& clause : newClauses) {
                if (find(clauseSets.begin(), clauseSets.end(), clause) == clauseSets.end()) {
                    clauseSets.push_back(clause);
                    addedNewClause = true;
                }
            }

            // If no new clauses were added, SAT is detected
            if (!addedNewClause) {
                cout << "SATISFIABLE" << endl;
                return true;
            }
        }
    }

private:
    // Helper function to resolve two clauses
    bool resolve(const set<int>& clause1, const set<int>& clause2, set<int>& resolvent) {
        for (int literal : clause1) {
            if (clause2.count(-literal)) {
                // Found a complementary pair
                resolvent = clause1;
                resolvent.insert(clause2.begin(), clause2.end());
                resolvent.erase(literal);
                resolvent.erase(-literal);
                return true;
            }
        }
        return false;
    }
};