/**
 * \file misc.cpp
 * \brief definition of some member functions of the class AmgXSolver.
 * \author Pi-Yueh Chuang (pychuang@gwu.edu)
 * \date 2016-01-08
 */


// AmgXWrapper
# include "AmgXSolver.hpp"


// definition of AmgXSolver::setMode
PetscErrorCode AmgXSolver::setMode(const std::string &modeStr)
{
    PetscFunctionBeginUser;

    if (modeStr == "hDDI")
        mode = AMGX_mode_hDDI;
    else if (modeStr == "hDFI")
        mode = AMGX_mode_hDFI;
    else if (modeStr == "hFFI")
        mode = AMGX_mode_hFFI;
    else if (modeStr == "dDDI")
        mode = AMGX_mode_dDDI;
    else if (modeStr == "dDFI")
        mode = AMGX_mode_dDFI;
    else if (modeStr == "dFFI")
        mode = AMGX_mode_dFFI;
    else
        SETERRQ1(MPI_COMM_WORLD, PETSC_ERR_ARG_WRONG,
                "%s is not an available mode! Available modes are: "
                "hDDI, hDFI, hFFI, dDDI, dDFI, dFFI.\n", modeStr.c_str());

    PetscFunctionReturn(0);
}


// definition of AmgXSolver::getIters
PetscErrorCode AmgXSolver::getIters(int &iter)
{
    PetscFunctionBeginUser;

    // only processes using AmgX will try to get # of iterations
    if (gpuProc == 0)
        AMGX_solver_get_iterations_number(solver, &iter); 

    PetscFunctionReturn(0);
}


// definition of AmgXSolver::getResidual
PetscErrorCode AmgXSolver::getResidual(const int &iter, double &res)
{
    PetscFunctionBeginUser;

    // only processes using AmgX will try to get residual
    if (gpuProc == 0)
        AMGX_solver_get_iteration_residual(solver, iter, 0, &res);

    PetscFunctionReturn(0);
}
