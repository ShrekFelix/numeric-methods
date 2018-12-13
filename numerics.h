#ifndef __NUMERICS_H__
#define __NUMERICS_H__

#include <string>  
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <utility>
#include <exception>
#include "Expr.h"

#define EXIST_FUN(s) ( (s)=="+"||(s)=="-"||(s)=="*"||(s)=="/"||(s)=="%"||(s)=="sin"||(s)=="cos"||(s)=="sqrt"||(s)=="log"||(s)=="pow"||fmap.find((s))!=fmap.end() )

#define H 0.000000000001

using std::vector;
using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::cerr;
using std::fstream;
using std::invalid_argument;
using std::out_of_range;

extern vector<vector<Expr_Num*> > vars;
extern vector<string> ids;

Expr* makeExpr(const string & s, vector<Expr*> & args);

Expr* parseFun(stringstream & ss);

Expr* parseExpr(stringstream & ss);

void define(stringstream & ss);

void evaluate(stringstream & ss);

bool parseInt(stringstream & ss,
	      double & prec,
	      vector<double> & low, vector<double> & high,
	      Expr_Op_Fun* & expr);

double intDim(double ans, double step,
	      size_t dim,
	      vector<double> & low, vector<double> & cur, vector<double> & high,
	      Expr_Op_Fun * expr);

void numint(stringstream & ss);

void mcint(stringstream & ss);

vector<double> gradf(Expr_Op_Fun * expr, vector<double> & point, double * step);

double dist(const vector<double> & a, const vector<double> & b);

vector<double> gradAD(Expr_Op_Fun* fun, vector<double> & p0, double gamma, double convDist, double step, double sign);

void extremum(stringstream & ss, double ad);

#endif
