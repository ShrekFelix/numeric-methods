  /* fin >> word;
  if( *word.begin() != '(' ){
    cerr<<"invalid definition\n";
    return;
  }
  else if( word.size()>1 ) 
  else{
    
  }
  
  while(fin >> word && word != "="){
    if( *word.begin() == '(' ){
      if(lCur == false){
	cerr<<"invalid definition\n";
      }
      lCur=false;
      if( word.size() == 1 ) break; //read '(' -> ignore it
      else word.erase( begin() ); //read '(id' -> remove the '('
    }
    if( *word.end() == ')' ){
      if(rCur == false){
	cerr<<"invalid definition"
      }
      if( word.size() == 1 ) break;
      else word.erase( end()-1 );
    }
    ids.push_back( word );
    if(*word.begin() == '('  &&  word.size()>1){
      ids.push_back( word.substr(1) );
    }
    else if(*word.begin() == '('  &&  word.size() == 1){
      break;
    }
    else if(*word.end() == ')' && word.size()>1){
      
    }
    else ids.push_back( word );
  }
  ids[ids.size()-1].erase( ids[ids.size()-1].end()-1 );
    */
#include <iostream>  
#include <string>  
#include <fstream>
#include <vector>
#include <ctype.h>

using namespace std;

void parseExpr(fstream & fin){
  string word;
  while(fin >> word){
    if(word.front() == '(')
  }
}

void eval(fstream & fin){
  string word;
  cout <<"evaluate: ";
  while(fin >> word){
    cout<<word<<"\n";
  }
}

void def(fstream & fin){
  string word;
  vector<string> ids;
  cout <<"defined  ";
  while(fin >> word && word != "="){ // read until '='
    ids.push_back(word);
  }

  if(ids.front().front() != '(' || // must start with '('
     ids.back().back() != ')' //must end with ')'
     ){
    cerr<<"invalid def format\n";
    return;
  }
  else{
    if( ids.front().size()>1 ) // (id
      ids.front().erase( ids.front().begin() );
    else // a single '('
      ids.erase( ids.begin() ); // erase it
    if( ids.back().size()>1 ) // id)
      ids.back().erase( ids.back().end()-1 );
    else // a single ')'
      ids.erase( ids.end() );
  }
  // check ids for containing no non-alphabetic chars
  for(size_t i=0;i<ids.size()-1;i++){
    for(size_t j=0;j<ids[i].size();j++){
      if(!isalpha(ids[i][j])){
	cerr<<"invalid id in lhs of definition\n";
	return;
      }
    }
  }

  parseExpr(fin);

  // output
  cout<<"(";
  for(size_t i=0;i<ids.size()-1;i++){
    cout<<ids[i]<<" ";
  }
  cout<<ids[ids.size()-1]<<")";
  cout<<"\n";
}

int main(int argc,char ** argv){
  if(argc != 2){
    cerr<<"usage: numeric input\n";
    return EXIT_FAILURE;
  }
  
  fstream fin(argv[1]);
  string word;
  while(fin >> word){
    if(word == "define"){
      def(fin);
    }
    if(word == "evaluate"){
      eval(fin);
    }
  }
  return EXIT_SUCCESS;
}
