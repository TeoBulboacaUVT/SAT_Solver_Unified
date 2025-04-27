#include "SATSolver.h"

class ResolutionSolver : public SATSolver {
public:
    ResolutionSolver(const string& filename) : SATSolver(filename) {}
    bool solve();
};