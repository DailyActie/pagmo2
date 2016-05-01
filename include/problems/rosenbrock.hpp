#ifndef PAGMO_PROBLEM_ROSENBROCK
#define PAGMO_PROBLEM_ROSENBROCK

#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../io.hpp"
#include "../problem.hpp"
#include "../types.hpp"

namespace pagmo
{

/// The Rosenbrock problem.
/**
 * \image html rosenbrock.png "Two-dimensional Rosenbrock function."
 *
 * This is a box-constrained continuous single-objecive problem.
 * The objective function is the generalised n-dimensional Rosenbrock function:
 * \f[
 *  F\left(x_1,\ldots,x_n\right) =
 *  \sum_{i=1}^{n-1}\left[ 100\left(x_i^2-x_{i+1}\right)^2+\left(x_i-1\right)^2\right], \quad x_i \in \left[ -5,10 \right].
 * \f]
 * The global minimum is in \f$x_i=1\f$, where \f$ F\left( 1,\ldots,1 \right) = 0 \f$.
 *
 * @author Dario Izzo (dario.izzo@esa.int)
 */
struct rosenbrock
{
    /// Constructor from dimension
    rosenbrock(unsigned int dim = 2u) : m_dim(dim) 
    {
        if (dim < 2) {
            pagmo_throw(std::invalid_argument, "Rosenbrock Function must have minimum 2 dimensions, " + std::to_string(dim) + " requested");
        }
    };
    /// Fitness
    vector_double fitness(const vector_double &x) const
    {
        vector_double f(1.,0.);
        for (decltype(m_dim) i=0u; i < m_dim-1u; ++i){
                f[0] += 100. * (x[i]*x[i] -x[i+1])*(x[i]*x[i] -x[i+1]) + (x[i]-1)*(x[i]-1);
        }
        return f;
    }
    /// Number of objectives
    vector_double::size_type get_nobj() const
    {
        return 1u;
    }

    /// Problem bounds
    std::pair<vector_double, vector_double> get_bounds() const
    {
        vector_double lb(m_dim,-5.);
        vector_double ub(m_dim, 1.);
        return {lb,ub};
    }
    /// Problem name
    std::string get_name() const
    {   
        return "Multidimensional Rosenbrock Function";
    }
    /// Optimal solution 
    vector_double best_known() const
    {
        return vector_double(m_dim,1.);
    }
    /// Serialization
    template <typename Archive>
    void serialize(Archive &ar)
    {
        ar(m_dim);
    }

    unsigned int m_dim;
};

}

PAGMO_REGISTER_PROBLEM(pagmo::rosenbrock)

#endif