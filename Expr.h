#ifndef __EXPR_H__
#define __EXPR_H__

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <sstream>

using std::vector;
using std::map;
using std::cin;
using std::cout;
using std::stringstream;
using std::string;
using std::pair;

class Expr{
 public:
  virtual string toString()const=0;
  virtual double eval()const=0;
  virtual ~Expr(){}
};

class Expr_Num:public Expr{
 public:
  double num;
 Expr_Num(double _num): num(_num) {}
  virtual string toString()const;
  virtual double eval()const{
    return num;
  }
  virtual ~Expr_Num(){}
};

typedef pair<Expr*, vector<vector<Expr_Num*> > > Fun;
extern map<string, Fun> fmap;

void freeArgs(vector<Expr*> args);

class Expr_Op:public Expr{
 public:
  string name;
  vector<Expr*> args;
 Expr_Op(string _name,vector<Expr*> & _args): name(_name), args(_args){}
  virtual string toString()const;
  virtual ~Expr_Op(){
    freeArgs(args);
  }
};

class Expr_Op_Fun:public Expr_Op{
 public:
 Expr_Op_Fun(string _name,vector<Expr*>& args): Expr_Op(_name,args){}
  virtual double eval()const;
};

class Expr_Op_Plus:public Expr_Op{
 public:
 Expr_Op_Plus(vector<Expr*>& args): Expr_Op("+",args){}
  virtual double eval()const{
    return args[0]->eval() + args[1]->eval();
  }
};

class Expr_Op_Minus:public Expr_Op{
 public:
 Expr_Op_Minus(vector<Expr*>& args): Expr_Op("-",args){}
  virtual double eval()const{
    return args[0]->eval() - args[1]->eval();
  }
};

class Expr_Op_Times:public Expr_Op{
 public:
 Expr_Op_Times(vector<Expr*>& args): Expr_Op("*",args){}
  virtual double eval()const{
    return args[0]->eval() * args[1]->eval();
  }
};

class Expr_Op_Div:public Expr_Op{
 public:
 Expr_Op_Div(vector<Expr*>& args): Expr_Op("/",args){}
  virtual double eval()const{
    return args[0]->eval() / args[1]->eval();
  }
};

class Expr_Op_Mod:public Expr_Op{
 public:
 Expr_Op_Mod(vector<Expr*>& args): Expr_Op("%",args){}
  virtual double eval()const{
    return fmod(args[0]->eval() , args[1]->eval());
  }
};

class Expr_Op_Sin:public Expr_Op{
 public:
 Expr_Op_Sin(vector<Expr*>& args): Expr_Op("sin",args){}
  virtual double eval()const{
    return sin( args[0]->eval() );
  }
};

class Expr_Op_Cos:public Expr_Op{
 public:
 Expr_Op_Cos(vector<Expr*>& args): Expr_Op("cos",args){}
  virtual double eval()const{
    return cos( args[0]->eval() );
  }
};

class Expr_Op_Sqrt:public Expr_Op{
 public:
 Expr_Op_Sqrt(vector<Expr*>& args): Expr_Op("sqrt",args){}
  virtual double eval()const{
    return sqrt( args[0]->eval() );
  }
};

class Expr_Op_Log:public Expr_Op{
 public:
 Expr_Op_Log(vector<Expr*>& args): Expr_Op("log",args){}
  virtual double eval()const{
    return log( args[0]->eval() );
  }
};

class Expr_Op_Pow:public Expr_Op{
 public:
 Expr_Op_Pow(vector<Expr*>& args): Expr_Op("pow",args){}
  virtual double eval()const{
    return pow( args[0]->eval(), args[1]->eval() );
  }
};

#endif
