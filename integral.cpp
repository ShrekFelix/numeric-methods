#include "numerics.h"

// input of 'numint' and 'mcint' follows the same pattern
bool parseInt(stringstream & ss,
	      double & prec,
	      vector<double> & low, vector<double> & high,
	      Expr_Op_Fun* & expr){
  // fname
  string s;
  ss >> s;
  if( fmap.find(s) == fmap.end() ){
    cerr<<"\""<< s <<"\" is not defined\n";
    return false;
  } 
  string name=s;
  // initialize precision parameter
  ss >> s;
  try{
    prec = stod(s);
    if( prec <= 0){
      cerr<<"precision parameter must be positive\n";
      return false;
    }
  }
  catch (const invalid_argument& ia) {
    cerr << "invalid argument for numint\n";
    return false;
  }
  catch (const out_of_range& oor) {
    cerr << "argument out of range\n";
    return false;
  }
  // initialize bounds of integration
  size_t sz=fmap[name].second.size();
  for(size_t i=0;i<sz*2;i++){
    ss >> s;
    try{
      if(i%2 == 0){
	low.push_back( stod(s) );
      }
      else{
	high.push_back( stod(s) );
      }
    }
    catch (const invalid_argument& ia) {
      cerr << "invalid argument for integration\n";
      return false;
    }
    catch (const out_of_range& oor) {
      cerr << "argument out of range\n";
      return false;
    }
  }
  // make expr
  vector<Expr*> nums;
  for(size_t i=0;i<low.size();i++){
    nums.push_back( new Expr_Num(low[i]) );
  }
  expr=new Expr_Op_Fun(name,nums);
  return true;
}

// output of 'numint' and 'mcint' follows the same pattern
void printInt(string cmd, string name, double prec, vector<double> & low, vector<double> & high, double ans){
  cout<< cmd <<" "<< name <<" "<< prec;
  for(size_t i=0; i<low.size()*2; i++){
    if(i%2 == 0){
      cout<<" "<< low[i/2];
    }
    else{
      cout<<" "<< high[i/2];
    }
  }
  cout<<" = "<< ans <<"\n\n";
}

// integrate recursively by each dimension
double intDim(double ans, double step,
	      size_t dim,
	      vector<double> & low, vector<double> & cur, vector<double> & high,
	      Expr_Op_Fun * expr){
  if(dim == cur.size()-1){ //base case:compute integral of the last one dimension
    if(low[dim]<high[dim]){
      for(cur[dim] = low[dim]; cur[dim] < high[dim]; cur[dim] += step){
	Expr_Num* new_arg = dynamic_cast<Expr_Num*>(expr->args[dim]);
	new_arg->num = cur[dim];
	ans += expr->eval() ;
      }
      return ans*step;
    }
    else{
      for(cur[dim] = high[dim]; cur[dim] < low[dim]; cur[dim] += step){
	Expr_Num* new_arg = dynamic_cast<Expr_Num*>(expr->args[dim]);
	new_arg->num = cur[dim];
	ans += expr->eval() ;
      }
      return -ans*step; 
    }
  }
  else{ // recursively compute integral of inner dimensions
    if(low[dim]<high[dim]){   
      for(cur[dim] = low[dim]; cur[dim] < high[dim]; cur[dim] += step){
	Expr_Num* new_arg = dynamic_cast<Expr_Num*>(expr->args[dim]);
	new_arg->num = cur[dim];
	ans += intDim(0,step, dim+1, low,cur,high, expr); 
      }
      return ans*step;
    }
    else{
      for(cur[dim] = high[dim]; cur[dim] < low[dim]; cur[dim] += step){
	Expr_Num* new_arg = dynamic_cast<Expr_Num*>(expr->args[dim]);
	new_arg->num = cur[dim];
	ans += intDim(0,step, dim+1, low,cur,high, expr);
      }
      return -ans*step;
    }
  }
}

void numint(stringstream & ss){
  double prec;
  vector<double> low;
  vector<double> high;
  Expr_Op_Fun * expr;
  if( parseInt(ss, prec, low,high, expr) ){ // parse input
    vector<double> cur(low);
    double ans=intDim(0,prec, 0, low,cur,high, expr); // numerical integration
    printInt("numint", expr->name, prec, low,high, ans); // output
    delete expr;
  }
  else{
    cerr<<"numint failed\n\n";
    return;
  }
}

void mcint(stringstream & ss){
  double prec;
  vector<double> low;
  vector<double> high;
  Expr_Op_Fun * expr;
  // parse input
  if( parseInt(ss, prec, low,high, expr) ){
    size_t trial=size_t(prec);
    if(trial == 0){
      cerr<<"trial must be greater than 1\n";
      return;
    }
    // Monte Carlo integration
    double sum=0;
    for(size_t i=0; i<trial; i++){
      for(size_t dim=0; dim<low.size(); dim++){
	Expr_Num* new_arg = dynamic_cast<Expr_Num*>(expr->args[dim]);
	new_arg->num=rand()/double(RAND_MAX)*(high[dim]-low[dim])+low[dim];
      }
      sum += expr->eval();
    }
    sum /= trial;
    for(size_t i=0; i<low.size(); i++){
      sum *= (high[i]-low[i]);
    }
    printInt("mcint", expr->name, trial, low,high, sum); // output
    delete expr;
  }
  else{
    cerr<<"mcint failed\n\n";
    return;
  }
}

