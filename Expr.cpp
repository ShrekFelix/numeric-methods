#include "Expr.h"


map<string, Fun> fmap;

string Expr_Num::toString()const{
  stringstream ss;
  ss<< num;
  return ss.str();
}

void freeArgs(vector<Expr*> args){
  for(size_t i=0;i<args.size();i++){
    delete args[i];
  }
}

string Expr_Op::toString()const{
  stringstream ss;
  ss<<"("<< name;
  for(size_t i=0;i<args.size();i++){
    ss<<" "<< args[i]->toString();
  }
  ss<<")";
  return ss.str();
}

double Expr_Op_Fun::eval()const{
  // first compute numeric value for each arg
  vector<double> val;
  for(size_t i=0; i<args.size(); i++){
    val.push_back( args[i]->eval() );    
  }
  Fun & fun=fmap[name];
  // then pass the value to their desinated position
  for(size_t i=0; i<fun.second.size(); i++){
    for(size_t j=0; j<fun.second[i].size(); j++){
      fun.second[i][j]->num=val[i];
    }
  }
  return fun.first->eval();
}
