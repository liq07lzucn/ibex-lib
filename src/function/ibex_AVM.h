/* ============================================================================
 * I B E X - Interface for Auxiliary Variable Method algorithms
 * ============================================================================
 * Copyright   : Ecole des Mines de Nantes (FRANCE)
 * License     : This program can be distributed under the terms of the GNU LGPL.
 *               See the file COPYING.LESSER.
 *
 * Author(s)   : Antoine Marendet
 * ---------------------------------------------------------------------------- */


#ifndef __IBEX_AVM_H__
#define __IBEX_AVM_H__

#include "ibex_FwdAlgorithm.h"
#include "ibex_Function.h"
#include "ibex_ExprDomain.h"
#include "ibex_ExprDataAVM.h"
#include "ibex_LPSolver.h"
#include "ibex_Eval.h"
#include "ibex_SparseVector.h"
#include "ibex_ConvexEnvelope.h"

namespace ibex {

/**
 * \ingroup symbolic
 * \brief This class implements an Auxiliary Variable Method.
 *
 * Each node in the expression is linearized.
 * Users of this class must implement the methods emit(), setup_node() and finish_node().
 */
class AVM : public FwdAlgorithm {
public:
    AVM(Eval& eval);
    ~AVM();

    /**
     * \brief Linearize the expression in a box.
     */
    void linearize(const IntervalVector& box);

    /**
     * \brief This function is called every time a ConvexEnvelope object is created.
     * It can be called multiple times in a node.
     * The ConvexEnvelope contains the linearization.
     */
    virtual void emit(const ConvexEnvelope& ce) = 0;

    inline void vector_fwd (int* x, int y);
	inline void apply_fwd  (int* x, int y);
	inline void idx_fwd    (int x, int y);
	inline void idx_cp_fwd (int x, int y);
	inline void symbol_fwd (int y);
	inline void cst_fwd    (int y);
	inline void chi_fwd    (int x1, int x2, int x3, int y);
	inline void gen2_fwd   (int x1, int x2, int y);
	inline void add_fwd    (int x1, int x2, int y);
	inline void mul_fwd    (int x1, int x2, int y);
	inline void sub_fwd    (int x1, int x2, int y);
	inline void div_fwd    (int x1, int x2, int y);
	inline void max_fwd    (int x1, int x2, int y);
	inline void min_fwd    (int x1, int x2, int y);
	inline void atan2_fwd  (int x1, int x2, int y);
	inline void gen1_fwd   (int x, int y);
	inline void minus_fwd  (int x, int y);
	inline void minus_V_fwd(int x, int y);
	inline void minus_M_fwd(int x, int y);
	inline void trans_V_fwd(int x, int y);
	inline void trans_M_fwd(int x, int y);
	inline void sign_fwd   (int x, int y);
	inline void abs_fwd    (int x, int y);
	inline void power_fwd  (int x, int y, int p);
	inline void sqr_fwd    (int x, int y);
	inline void sqrt_fwd   (int x, int y);
	inline void exp_fwd    (int x, int y);
	inline void log_fwd    (int x, int y);
	inline void cos_fwd    (int x, int y);
	inline void sin_fwd    (int x, int y);
	inline void tan_fwd    (int x, int y);
	inline void cosh_fwd   (int x, int y);
	inline void sinh_fwd   (int x, int y);
	inline void tanh_fwd   (int x, int y);
	inline void acos_fwd   (int x, int y);
	inline void asin_fwd   (int x, int y);
	inline void atan_fwd   (int x, int y);
	inline void acosh_fwd  (int x, int y);
	inline void asinh_fwd  (int x, int y);
	inline void atanh_fwd  (int x, int y);
	inline void floor_fwd  (int x, int y);
	inline void ceil_fwd   (int x, int y);
	inline void saw_fwd    (int x, int y);
	inline void add_V_fwd  (int x1, int x2, int y);
	inline void add_M_fwd  (int x1, int x2, int y);
	inline void mul_SV_fwd (int x1, int x2, int y);
	inline void mul_SM_fwd (int x1, int x2, int y);
	inline void mul_VV_fwd (int x1, int x2, int y);
	inline void mul_MV_fwd (int x1, int x2, int y);
	inline void mul_VM_fwd (int x1, int x2, int y);
	inline void mul_MM_fwd (int x1, int x2, int y);
	inline void sub_V_fwd  (int x1, int x2, int y);
	inline void sub_M_fwd  (int x1, int x2, int y);

protected:
    Eval& eval_;
    Function& f_;
    const ExprDomain& d_; // = eval_.d
    ExprDataAVM avm_d_;

private:
    /**
     * \brief Setup node functions are called when entering a node.
     */
    virtual void setup_node(int y) = 0;
    virtual void setup_node(int x, int y) = 0;
    virtual void setup_node(int x1, int x2, int y) = 0;
    virtual void setup_node(int* x, int y) = 0;

    /**
     * \brief Finish node functions are called when exiting a node.
     */
    virtual void finish_node(int y) = 0;
    virtual void finish_node(int x, int y) = 0;
    virtual void finish_node(int x1, int x2, int y) = 0;
    virtual void finish_node(int* x, int y) = 0;



};

inline void AVM::vector_fwd(int* x, int y) {
    /* nothing to do */
    setup_node(x, y);
    finish_node(x, y);
}

inline void AVM::apply_fwd(int* x, int y) {
    /* nothing to do */
    not_implemented("Apply not implemented for AVM");
}

inline void AVM::idx_fwd(int x, int y) {
    /* nothing to do */
}

inline void AVM::idx_cp_fwd(int x, int y) {
    /* nothing to do */
}

inline void AVM::symbol_fwd(int y) {
    setup_node(y);
    finish_node(y);
}

inline void AVM::cst_fwd(int y) {
    setup_node(y);
    finish_node(y);
}

inline void AVM::chi_fwd(int x1, int x2, int x3, int y) {
    // d[y].i() = chi(d[x1].i(),d[x2].i(),d[x3].i());
    not_implemented("Chi not implemented for AVM");
}

inline void AVM::gen2_fwd(int x1, int x2, int y) {
    // d[y].i() = chi(d[x1].i(),d[x2].i(),d[x3].i());
    not_implemented("Gen2 not implemented for AVM");
}

inline void AVM::add_fwd(int x1, int x2, int y)   {
    // - y + x1 + x2 = 0
    setup_node(x1, x2, y);
    if(x1 == x2) {
        ConvexEnvelope ce = convex_envelope::int_mul(2, d_[x1].i());
        emit(ce);
    } else {
        ConvexEnvelope ce = convex_envelope::add(d_[x1].i(), d_[x2].i());
        emit(ce);
    }
    finish_node(x1, x2, y);

}

inline void AVM::mul_fwd(int x1, int x2, int y)   {
    if(x1 == x2) {
        sqr_fwd(x1, y);
        return;
    }
    setup_node(x1, x2, y);
    ConvexEnvelope ce = convex_envelope::mul(d_[x1].i(), d_[x2].i());
    emit(ce);
    finish_node(x1, x2, y);
}
inline void AVM::sub_fwd(int x1, int x2, int y)   {
    // - y + x1 - x2 <= 0
    setup_node(x1, x2, y);
    if(x1 == x2) {
        ConvexEnvelope ce = convex_envelope::int_mul(0, d_[x1].i());
        emit(ce);
    } else {
        ConvexEnvelope ce = convex_envelope::sub(d_[x1].i(), d_[x2].i());
        emit(ce);
    }
    finish_node(x1, x2, y);
}
inline void AVM::div_fwd(int x1, int x2, int y)   {
    setup_node(x1, x2, y);
    ConvexEnvelope ce = convex_envelope::div_from_mul(d_[x1].i(), d_[x2].i(), d_[y].i());
    emit(ce);
    finish_node(x1, x2, y);
}
inline void AVM::max_fwd(int x1, int x2, int y)   {
    setup_node(x1, x2, y);
    ConvexEnvelope ce = convex_envelope::max(d_[x1].i(), d_[x2].i());
    emit(ce);
    finish_node(x1, x2, y);
}
inline void AVM::min_fwd(int x1, int x2, int y)   {
    setup_node(x1, x2, y);
    ConvexEnvelope ce = convex_envelope::max(d_[x1].i(), d_[x2].i());
    emit(ce);
    finish_node(x1, x2, y);
}
inline void AVM::atan2_fwd(int x1, int x2, int y) {
    // d[y].i()=atan2(d[x1].i(),d[x2].i());
    not_implemented("Atan2 not implemented for AVM");
}

inline void AVM::gen1_fwd(int x, int y) {
    not_implemented("Gen1 not implemented for AVM");
}

inline void AVM::minus_fwd(int x, int y)          {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::int_mul(-1, d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::minus_V_fwd(int x, int y)        {
    // d[y].v()=-d[x].v();
    const int dim = d_[y].dim.size();
    setup_node(x, y);
    for(int i = 0; i < dim; ++i) {
        ConvexEnvelope ce = convex_envelope::int_mul(-1, d_[x].v()[i]);
        emit(ce);
    }
    finish_node(x, y);
}
inline void AVM::minus_M_fwd(int x, int y)        {
    // d[y].m()=-d[x].m();
    not_implemented("Minus_M not implemented for AVM");
}
inline void AVM::sign_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::sign(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::abs_fwd(int x, int y)            {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::abs(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::power_fwd(int x, int y, int p)   {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::power(d_[x].i(), p);
    emit(ce);
    finish_node(x, y);
}

inline void AVM::sqr_fwd(int x, int y)            {
    // 0 >= x^2 = y >= lin
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::sqr(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::sqrt_fwd(int x, int y)           {
    // if ((d[y].i()=sqrt(d[x].i())).is_empty()) throw EmptyBoxException();
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::sqrt(d_[x].i());
    emit(ce);
    finish_node(x, y);
}

inline void AVM::exp_fwd(int x, int y)            {
    // d[y].i()=exp(d[x].i());
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::exp(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::log_fwd(int x, int y)            {
    // if ((d[y].i()=log(d[x].i())).is_empty()) throw EmptyBoxException();
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::log(d_[x].i());
    emit(ce);
    finish_node(x, y);
}

inline void AVM::cos_fwd(int x, int y)            {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::cos(d_[x].i());
    emit(ce);
    finish_node(x, y);
}

inline void AVM::sin_fwd(int x, int y)            {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::sin(d_[x].i());
    emit(ce);
    finish_node(x, y);
}

inline void AVM::tan_fwd(int x, int y)            {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::tan(d_[x].i());
    emit(ce);
    finish_node(x, y);
}

inline void AVM::cosh_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::cosh(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::sinh_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::sinh(d_[x].i());
    emit(ce);
    finish_node(x, y);;
}
inline void AVM::tanh_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::tanh(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::acos_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::acos(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::asin_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::asin(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::atan_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::atan(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::acosh_fwd(int x, int y)          {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::acosh(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::asinh_fwd(int x, int y)          {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::asinh(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::atanh_fwd(int x, int y)          {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::atanh(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::floor_fwd(int x, int y)          {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::floor(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::ceil_fwd(int x, int y)           {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::ceil(d_[x].i());
    emit(ce);
    finish_node(x, y);
}
inline void AVM::saw_fwd(int x, int y)            {
    setup_node(x, y);
    ConvexEnvelope ce = convex_envelope::saw(d_[x].i());
    emit(ce);
    finish_node(x, y);
}

inline void AVM::trans_V_fwd(int x, int y)        {
    // d[y].v()=d[x].v();
    not_implemented("Trans_V not implemented for AVM");
}
inline void AVM::trans_M_fwd(int x, int y)        {
    // d[y].m()=d[x].m().transpose();
    not_implemented("Trans_M not implemented for AVM");
}
inline void AVM::add_V_fwd(int x1, int x2, int y) {
    // d[y].v()=d[x1].v()+d[x2].v();
    const int dim = d_[y].dim.size();
    setup_node(x1, x2, y);
    if(x1 == x2) {
        for(int i = 0; i < dim; ++i) {
            ConvexEnvelope ce = convex_envelope::int_mul(2, d_[x1].v()[i]);
            emit(ce);
        }
    } else {
        for(int i = 0; i < dim; ++i) {
            ConvexEnvelope ce = convex_envelope::add(d_[x1].v()[i], d_[x2].v()[i]);
            emit(ce);
        }
    }
    finish_node(x1, x2, y);
}
inline void AVM::add_M_fwd(int x1, int x2, int y) {
    // d[y].m()=d[x1].m()+d[x2].m();
    not_implemented("Add_M not implemented for AVM");
}
inline void AVM::mul_SV_fwd(int x1, int x2, int y){
    // d[y].v()=d[x1].i()*d[x2].v();
    not_implemented("Mul_SV not implemented for AVM");
}
inline void AVM::mul_SM_fwd(int x1, int x2, int y){
    // d[y].m()=d[x1].i()*d[x2].m();
    not_implemented("Mul_SM not implemented for AVM");
}
inline void AVM::mul_VV_fwd(int x1, int x2, int y){
    // d[y].i()=d[x1].v()*d[x2].v();
    not_implemented("Mul_VV not implemented for AVM");
}
inline void AVM::mul_MV_fwd(int x1, int x2, int y){
    // d[y].v()=d[x1].m()*d[x2].v();
    not_implemented("Mul_MV not implemented for AVM");
}
inline void AVM::mul_VM_fwd(int x1, int x2, int y){
    // d[y].v()=d[x1].v()*d[x2].m();
    not_implemented("Mul_VM not implemented for AVM");
}
inline void AVM::mul_MM_fwd(int x1, int x2, int y){
    // d[y].m()=d[x1].m()*d[x2].m();
    not_implemented("Mul_MM not implemented for AVM");
}
inline void AVM::sub_V_fwd(int x1, int x2, int y) {
    // d[y].v()=d[x1].v()-d[x2].v();
    not_implemented("Sub_V not implemented for AVM");
}
inline void AVM::sub_M_fwd(int x1, int x2, int y) {
    // d[y].m()=d[x1].m()-d[x2].m();
    not_implemented("Sub_M not implemented for AVM");
}


} // namespace ibex

#endif  // __IBEX_AVM_H__