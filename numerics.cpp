#include "numerics.h"


vector<vector<Expr_Num*> > vars;
vector<string> ids;

Expr* makeExpr(const string & s, vector<Expr*> & args){
  
  if(s == "+"){
    if(args.size() != 2){
      cerr<<"\"+\" takes exactly 2 arguments\n";
      freeArgs(args);
      return NULL;
    }
    else
      return new Expr_Op_Plus(args);
  }
  else if(s == "-"){
    if(args.size() != 2){
      cerr<<"\"-\" takes exactly 2 arguments\n";
      freeArgs(args);
      return NULL;
    }
    else
      return new Expr_Op_Minus(args);
  }
  else if(s == "*"){
    if(args.size() != 2){
      cerr<<"\"*\" takes exactly 2 arguments\n";
      freeArgs(args);
      return NULL;
    }
    else
      return new Expr_Op_Times(args);
  }
  else if(s == "/"){
    if(args.size() != 2){
      cerr<<"\"/\" takes exactly 2 arguments\n";
      freeArgs(args);
      return NULL;
    }
    else
      return new Expr_Op_Div(args);
  }
  else if(s == "%"){
    if(args.size() != 2){
      cerr<<"\"%\" takes exactly 2 arguments\n";
      freeArgs(args);
      return NULL;
    }
    else
      return new Expr_Op_Mod(args);
  }
  else if(s == "sin"){
    if(args.size() != 1){
      cerr<<"\"sin\" takes exactly 1 argument\n";
      freeArgs(args);
      return NULL;
    }
    else
      return new Expr_Op_Sin(args);
  }
  else if(s == "cos"){
    if(args.size() != 1){
      cerr<<"\"cos\" takes exactly 1 argument\n";
      freeArgs(args);
      return NULL;
    }
    else return new Expr_Op_Cos(args);
  }
  else if(s == "sqrt"){
    if(args.size() != 1){
      cerr<<"\"sqrt\" takes exactly 1 argument\n";
      freeArgs(args);
      return NULL;
    }
    else return new Expr_Op_Sqrt(args);
  }
  else if(s == "log"){
    if(args.size() != 1){
      cerr<<"\"log\" takes exactly 1 argument\n";
      freeArgs(args);
      return NULL;
    }
    else return new Expr_Op_Log(args);
  }
  else if(s == "pow"){
    if(args.size() != 2){
      cerr<<"\"pow\" takes exactly 2 arguments\n";
      freeArgs(args);
      return NULL;
    }
    else return new Expr_Op_Pow(args);
  }
  else{ // a pre-defined function
    size_t num_args=fmap[s].second.size();
    if( num_args != args.size() ){
      cerr<<"\""<< s <<"\" takes exactly "<< num_args <<" arguments\n";
      freeArgs(args);
      return NULL;
    }
    else return new Expr_Op_Fun(s, args);
  }
}

Expr* parseFun(stringstream & ss){
  vector<Expr*> args;
  string s;
  ss >> s;
  if( !EXIST_FUN(s) ){
    cerr<<"\""<< s <<"\" is not defined\n";
    return NULL;
  }
  // prepare args for the new expr
  Expr* newExpr;
  while( ( newExpr=parseExpr(ss) ) != NULL ){
    args.push_back( newExpr );
  }
  return makeExpr(s,args);
}

Expr* parseExpr(stringstream & ss){
  string s;
  ss >> s;
  if( s == "(" ){ // (fname expr expr ...)
    return parseFun(ss);
  }
  else if( s == ")"){ // end of expr
    return NULL;
  }
  else if(isalpha(s[0])){ // variable
    for(size_t i=1;i<ids.size();i++){
      if( ids[i] == s ){
	vars[i-1].push_back(new Expr_Num(0));
	return vars[i-1].back();
      }
    }
    cerr<<"invalid variable "<< s <<"\n";
    return NULL;
  }
  else{ // number
    size_t sz;
    double num=stod(s,&sz);
    if(sz != 0){
      return new Expr_Num(num);
    }
    else{
      cerr<<"expected a number, but found "<< s <<"\n";
      return NULL;
    }
  }
}

void define(stringstream & ss){
  string s;
  vars.clear();
  ids.clear();  
  ss >> s;
  if(s != "("){
    cerr<< "definition format: (fname arg arg ...) = expr\n\n";
    return;
  }
  // read ids til ")"
  while(ss >> s && s != ")"){
    ids.push_back(s);
  }
  // check ids
  if(ids.size() == 0){
    cerr<<"no identifier found in definition lhs\n\n";
    return;
  }
  if( EXIST_FUN(ids[0]) ){
    cerr<<"\""<< ids[0] <<"\" is already defined\n\n";
    return;
  }
  for(size_t i=0;i<ids.size();i++){
    for(size_t k=i+1;k<ids.size();k++){
      if(ids[i] == ids[k]){
	cerr<<"identical ids in definition lhs\n\n";
	return;
      }
    }
    for(size_t j=0;j<ids[i].size();j++){
      if(!isalpha(ids[i][j])){
	cerr<<"definition lhs contains non-alphabetic id\n\n";
	return;
      }
    }
  }
  // must read a '=' to start parsing the rhs of definition
  ss >> s;
  if( s != "=" ){
    cerr<<"expected \"=\" between lhs and rhs of definition\n\n";
    return;
  }
  else{ // ss is now at the rhs of definition
    vector< Expr_Num * > tmp;
    vars.assign(ids.size()-1,tmp);
    Expr* newDef = parseExpr(ss);
    // build map
    if( newDef != NULL){
      Fun fun(newDef,vars);
      fmap[ids[0]] = fun;
    }
    else{
      cerr<<"cannot parse definition expression\n\n";
      return;
    }
  }
  // output
  cout <<"defined  (";
  for(size_t i=0;i<ids.size()-1;i++){
    cout<<ids[i]<<" ";
  }
  cout<<ids[ids.size()-1]<<")\n\n";
}

void evaluate(stringstream & ss){
  vars.clear();
  ids.clear();
  Expr* newEval = parseExpr(ss);
  if(newEval == NULL){
    cerr<<"cannot parse evaluation expression\n\n";
    return;
  }
  else{
    cout<< newEval->toString() <<" = ";
    cout<< newEval->eval() <<"\n\n";
    delete newEval;
  }
}

int main(int argc,char ** argv){
  if(argc != 2){
    cerr<<"usage: numeric input\n";
    return EXIT_FAILURE;
  }
  fstream fin(argv[1]);
  // format the input by adding spaces
  stringstream ss;
  char c;
  while( fin.get(c) ){
    if(c == '('){
      ss << " ( ";
    }
    else if(c == ')'){
      ss << " ) ";
    }
    else if(c == '='){
      ss << " = ";
    }
    else{
      ss << c;
    }
  }
  string s;
  while(ss >> s){
    if(s == "define"){
      define(ss);
    }
    else if(s == "evaluate"){
      evaluate(ss);
    }
    else if(s == "numint"){
      numint(ss);
    }
    else if(s == "mcint"){
      mcint(ss);
    }
    else if(s == "max"){
      extremum(ss,1);
    }
    else if(s == "min"){
      extremum(ss,-1);
    }
  }
  // free memory in fmap
  for(map<string, Fun> :: iterator it=fmap.begin();
      it != fmap.end();
      ++it){
    delete it->second.first;
  }
  return EXIT_SUCCESS;
}
