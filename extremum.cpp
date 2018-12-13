#include "numerics.h"

// overload operator +, * for vector
vector<double> operator+(const vector<double> & a, const vector<double> & b){
  vector<double> ans;
  for(size_t i=0; i<a.size(); i++){
    ans.push_back( a[i]+b[i] );
  }
  return ans;
}
vector<double> operator*(const double s, const vector<double> & v){
  vector<double> ans;
  for(size_t i=0; i<v.size(); i++){
    ans.push_back( s*v[i] );
  }
  return ans;
}

// compute gradient at one point
vector<double> gradf(Expr_Op_Fun * expr, vector<double> & point, double * step){
  vector<double> ans;
  for(size_t i=0; i<point.size(); i++){
    Expr_Num* new_arg =dynamic_cast<Expr_Num*>(expr->args[i]);
    new_arg->num=point[i]+H;
    double f1=expr->eval();
    new_arg->num=point[i];
    double f0=expr->eval();
    double deri=(f1-f0)/H;
    /*
    if(deri==0){ // potential lose of double precision
      *step = 1;
    }
    */
    ans.push_back( deri );
  }
  return ans;
}

// compute distance of two vectors
double dist(const vector<double> & a, const vector<double> & b){
  double ans=0;
  for(size_t i=0; i<a.size(); i++){
    ans += pow( (a[i]-b[i]), 2); // 2-norm
  }
  return sqrt(ans);
}

// using gradient ascent/descent(based on the 'sign') to find extremum
vector<double> gradAD(Expr_Op_Fun* fun, vector<double> & p0, double gamma, double convDist, double step, double sign){
  vector<double> p1(p0);
  do{
    if(step <= 0){
      cerr<<"potential lose in double precision\n";
      cerr<<"cannot converge within given steps\n";
      break;
    }
    p0 = p1;
    p1 = p0 + sign * gamma * gradf(fun, p0, &step);
    step--;
  }
  while( dist(p1, p0)>convDist );  
  return p1;
}

void extremum(stringstream & ss, double ad){
  string s;
  vector<double> arg_in;
  ss >> s;
  if( fmap.find(s) == fmap.end() ){
    cerr<<"\""<< s <<"\" is not defined\n\n";
    return;
  }
  string name=s;
  for(size_t i=0; i<fmap[name].second.size()+3; i++){
    ss >> s;
    try{
      arg_in.push_back( stod(s) );
    }
    catch (const invalid_argument& ia) {
      cerr << "invalid argument\n\n";
      return;
    }
    catch (const out_of_range& oor) {
      cerr << "argument out of range\n\n";
      return;
    }
  }
  vector<double> point;
  vector<Expr *> nums;
  if(arg_in[0] < 0 || arg_in[1]<0 || arg_in.back()<0){
    cerr<<"gamma, converged distance, step number should be positive\n";
    return;
  }
  // make expr, initialize starting point
  for(size_t i=2; i<arg_in.size()-1; i++){
    point.push_back( arg_in[i] );
    nums.push_back( new Expr_Num(arg_in[i]) );
  }
  Expr_Op_Fun* expr=new Expr_Op_Fun(name, nums);
  vector<double> ans=gradAD(expr, point, arg_in[0], arg_in[1], arg_in.back(), ad);
  // output
  if( ad == 1 ){
    cout<<"max ";
  }
  else{
    cout<<"min ";
  }
  cout<<name<<" ";
  for(size_t i=0; i<arg_in.size(); i++){
    cout<< arg_in[i] <<" ";
  }
  cout<<"=";
  for(size_t i=0; i<ans.size(); i++){
    cout<<" "<< ans[i];
  }
  cout<<"\n\n";
  delete expr;
}
