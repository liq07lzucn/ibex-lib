//============================================================================
//                                  I B E X                                   
// File        : ibex_Expr2Polynom.cpp
// Author      : Gilles Chabert
// Copyright   : IMT Atlantique (France)
// License     : See the LICENSE file
// Created     : Mar 27, 2020
// Last update : May 12, 2020
//============================================================================

#include "ibex_Expr2Polynom.h"
#include "ibex_ExprSubNodes.h"
#include "ibex_Expr.h"
#include "ibex_Map.h"

#include <iostream>
#include <typeinfo>
#include <algorithm>

using namespace std;

namespace ibex {

Expr2Polynom::Expr2Polynom(bool develop) : develop(develop) {

}

Expr2Polynom::~Expr2Polynom() {
	for (IBEX_NODE_MAP(const ExprPolynomial*)::iterator it=cache.begin(); it!=cache.end(); ++it)
		delete it->second;
}

const ExprPolynomial* Expr2Polynom::get(const ExprNode& e) {
	return visit(e);
}

void Expr2Polynom::cleanup(const ExprNode& e) {
	delete cache.find(e)->second;
	cache.erase(e);
}

const ExprPolynomial* Expr2Polynom::visit(const ExprNode& e) {
	return ExprVisitor<const ExprPolynomial*>::visit(e);
}

const ExprPolynomial* Expr2Polynom::visit(const ExprSymbol& e) {
	return new ExprPolynomial(e);
}

const ExprPolynomial* Expr2Polynom::visit(const ExprConstant& e) {
	switch (e.dim.type()) {
	case Dim::SCALAR:
		return new ExprPolynomial(e.get_value());
		break;
	case Dim::ROW_VECTOR:
	{
		IntervalMatrix M(1,e.dim.nb_cols());
		M.row(0)=e.get_vector_value();
		return new ExprPolynomial(M);
	}
	break;
	case Dim::COL_VECTOR:
	{
		IntervalMatrix M(e.dim.nb_rows(),1);
		M.set_col(0,e.get_vector_value());
		return new ExprPolynomial(M);
	}
	break;
	default:
		assert(e.dim.is_matrix());
		return new ExprPolynomial(e.get_matrix_value());
		break;
	}
}

const ExprPolynomial* Expr2Polynom::unary(const ExprUnaryOp& e,
		std::function<const ExprUnaryOp&(const ExprNode&)> f) {

	const ExprPolynomial& pe = *visit(e.expr);
	return new ExprPolynomial(f(pe.to_expr()));
}

const ExprPolynomial* Expr2Polynom::binary(const ExprBinaryOp& e,
		std::function<const ExprBinaryOp&(const ExprNode&, const ExprNode&)> f) {
	const ExprPolynomial* pl = visit(e.left);
	const ExprPolynomial* pr = visit(e.right);
	return new ExprPolynomial(f(pl->to_expr(),pr->to_expr()));
}

const ExprPolynomial* Expr2Polynom::nary(const ExprNAryOp& e,
		std::function<const ExprNAryOp&(const Array<const ExprNode>&)> f) {

	Array<const ExprNode> new_args(e.nb_args);

	for (int i=0; i<e.nb_args; i++) {
		new_args.set_ref(i,visit(e.arg(i))->to_expr());
	}

	return new ExprPolynomial(f(new_args));
}

const ExprPolynomial* Expr2Polynom::visit(const ExprVector& e) {
	return nary(e, [&e](const Array<const ExprNode>& args) { return ExprVector::new_(args,e.orient); });
}

const ExprPolynomial* Expr2Polynom::visit(const ExprApply& e) {
	return nary(e, [&e](const Array<const ExprNode>& args) { return ExprApply::new_(*e.f,args); });
}

const ExprPolynomial* Expr2Polynom::visit(const ExprChi& e) {
	return nary(e, [](const Array<const ExprNode>& args)->const ExprChi& { return ExprChi::new_(args); });
}

const ExprPolynomial* Expr2Polynom::visit(const ExprMul& e) {
	const ExprPolynomial* l = visit(e.left);
	const ExprPolynomial* r = visit(e.right);
	if (develop || l->is_constant() || r->is_constant() || (l->one_monomial() && r->one_monomial()))
		return l->mul(r);
	else
		return new ExprPolynomial(l->to_expr()*r->to_expr());
}

const ExprPolynomial* Expr2Polynom::visit(const ExprGenericBinaryOp& e) {
	return binary( e,
			[&e](const ExprNode& x,const ExprNode& y)->const ExprBinaryOp& { return ExprGenericBinaryOp::new_(e.name,x,y);});
}

const ExprPolynomial* Expr2Polynom::visit(const ExprAdd& e)   {
	return visit(e.left)->add(visit(e.right));
}

const ExprPolynomial* Expr2Polynom::visit(const ExprSub& e)   {
	return visit(e.left)->sub(visit(e.right));
}

const ExprPolynomial* Expr2Polynom::visit(const ExprDiv& e)   {
	const ExprPolynomial* l = visit(e.left);
	const ExprPolynomial* r = visit(e.right);
	if (r->is_constant() && !r->mono.empty()) { // !r.mono.empty() -> we don't want to handle division by zero here
		Interval inv_r = Interval::one() / r->mono.front().coeff;
		return l->mul(inv_r);
	} else if (l->mono.empty())
		return new ExprPolynomial(Dim::scalar());
	else
		return new ExprPolynomial(l->to_expr() / r->to_expr());
}

const ExprPolynomial* Expr2Polynom::visit(const ExprMax& e)   { return binary(e, ExprMax::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprMin& e)   { return binary(e, ExprMin::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAtan2& e) { return binary(e, ExprAtan2::new_); }

const ExprPolynomial* Expr2Polynom::visit(const ExprMinus& e) {
	return visit(e.expr)->minus();
}

const ExprPolynomial* Expr2Polynom::visit(const ExprPower& e) {
	// note: no development with higher powers ?
	return new ExprPolynomial(ExprPower::new_(visit(e.expr)->to_expr(), e.expon));
}

const ExprPolynomial* Expr2Polynom::visit(const ExprGenericUnaryOp& e) {
	return unary(e, [&e](const ExprNode& x)->const ExprUnaryOp& { return ExprGenericUnaryOp::new_(e.name,x);});
}

const ExprPolynomial* Expr2Polynom::visit(const ExprIndex& e) {
	return new ExprPolynomial(ExprIndex::new_(visit(e.expr)->to_expr(), e.index));
}

const ExprPolynomial* Expr2Polynom::visit(const ExprSqr& e)   {
	if (develop)
		return visit(e.expr)->square_();
	else
		return unary(e, ExprSqr::new_);
}

const ExprPolynomial* Expr2Polynom::visit(const ExprTrans& e) { return unary(e, ExprTrans::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprSign& e)  { return unary(e, ExprSign::new_);  }
const ExprPolynomial* Expr2Polynom::visit(const ExprAbs& e)   { return unary(e, ExprAbs::new_);  }
const ExprPolynomial* Expr2Polynom::visit(const ExprSqrt& e)  { return unary(e, ExprSqrt::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprExp& e)   { return unary(e, ExprExp::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprLog& e)   { return unary(e, ExprLog::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprCos& e)   { return unary(e, ExprCos::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprSin& e)   { return unary(e, ExprSin::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprTan& e)   { return unary(e, ExprTan::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprCosh& e)  { return unary(e, ExprCosh::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprSinh& e)  { return unary(e, ExprSinh::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprTanh& e)  { return unary(e, ExprTanh::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAcos& e)  { return unary(e, ExprAcos::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAsin& e)  { return unary(e, ExprAsin::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAtan& e)  { return unary(e, ExprAtan::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAcosh& e) { return unary(e, ExprAcosh::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAsinh& e) { return unary(e, ExprAsinh::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprAtanh& e) { return unary(e, ExprAtanh::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprFloor& e) { return unary(e, ExprFloor::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprCeil& e)  { return unary(e, ExprCeil::new_); }
const ExprPolynomial* Expr2Polynom::visit(const ExprSaw& e)   { return unary(e, ExprSaw::new_);  }

} // namespace ibex