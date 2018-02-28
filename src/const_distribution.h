//
// Created by natasha on 28.02.18.
//
#include <iostream>
#include <random>

#ifndef GG1_SIMULATOR_CONSTDISTRIBUTION_H
#define GG1_SIMULATOR_CONSTDISTRIBUTION_H


template<typename _RealType = double>
class const_distribution
{

public:
/** The type of the range of the distribution. */
typedef _RealType param_type;
///** Parameter type. */
//struct param_type {
//    typedef const_distribution<_RealType> distribution_type;
//
//    explicit param_type(_RealType __lambda = _RealType(1)) : _M_lambda(__lambda) {
//        _GLIBCXX_DEBUG_ASSERT(_M_lambda > _RealType(0));
//    }
//
//    _RealType lambda() const {
//        return _M_lambda;
//    }
//
//    friend bool operator==(const param_type& __p1, const param_type& __p2)
//    { return __p1._M_lambda == __p2._M_lambda; }
//
//private:
//    _RealType _M_lambda;
//};

public:
explicit const_distribution(const param_type& __p) : _M_param(__p) {}

/**
 * @brief Resets the distribution state.
 *
 * Has no effect on exponential distributions.
 */
void reset() { }


/**
 * @brief Sets the parameter set of the distribution.
 * @param __param The new parameter set of the distribution.
 */
void param(const param_type& __param)
{ _M_param = __param; }


/**
 * @brief Generating functions.
 */
template<typename _UniformRandomNumberGenerator>
_RealType operator()(_UniformRandomNumberGenerator& __urng)
{ return _M_param; }


private:

param_type _M_param;
};

#endif //GG1_SIMULATOR_CONSTDISTRIBUTION_H
