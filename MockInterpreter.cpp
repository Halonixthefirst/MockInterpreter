#include<iostream>
#include<sstream>
#include<vector>
#include<unordered_map>
using namespace std;


struct Variable {
  string type;
  string strval;
  int numval;

};
unordered_map<string, Variable> memory;

vector<string> parser(string input) {
  vector<string> args;
  stringstream iss(input);
  string token;
  while (iss>>token) {
    args.push_back(token);
  }
  return args;
}

bool inMemory(string var) {
  return memory.count(var);
}
bool isValidName(string var) {
  return !(isdigit(var[0]));
}

bool isNumber(string var) {
  return inMemory(var) && memory[var].type=="number";
}
bool isString(string var) {
  return inMemory(var) && memory[var].type=="string";
}
bool isValidNumber(string a,string b) {
  if (!inMemory(a)) {
    cout<<"Variable "<<a<<" Not defined";
    return false;
  }
  if (!inMemory(b)) {
    cout<<"Variable "<<b<<" Not defined";
    return false;
  }
  if (!isNumber(a) || !isNumber(b)) {
    cout<<"Syntax Error: Operands must be numbers"<<endl;
    return false;
  }
  return true;
}
bool isValidString(string a,string b) {
  if (!inMemory(a)) {
    cout<<"Variable "<<a<<" Not defined";
    return false;
  }
  if (!inMemory(b)) {
    cout<<"Variable "<<b<<" Not defined";
    return false;
  }
  if (!isString(a) || !isString(b)) {
    cout<<"Syntax Error: Operands must be strings"<<endl;
    return false;
  }
  return true;
}
void definefunc(vector<string> tokens) {
  if (tokens.size()<5 || tokens[2]!="is") {
    cout<<"Syntax Error: say <var> is <type> <value>"<<endl;
    return;
  }
  string var=tokens[1];
  string type=tokens[3];
  string value=tokens[4];

  if (!isValidName(var)) {
    cout<<"Variable name cannot start with a digit"<<endl;
    return;
  }
  if (inMemory(var)) {
    cout<<"Variable already defined"<<endl;
    return;
  }

  Variable v;
  v.type=type;
  if (type=="number") {
    v.numval=stoi(value);
  }
  else if (type=="string") {
          v.strval=value;
  }
  else {
          cout<<"Expected keyword: type identifier :: hint:number ? string ?"<<endl;
        }
  memory[var]=v;
}
void printfunc(vector<string> tokens) {
  if (tokens.size()<2 ) {
    cout<<"Syntax Error: print <var>"<<endl;
    return;
  }
  string var=tokens[1];
  if (!inMemory(var)) {
    cout<<"Variable might not have been initialized"<<endl;
    return;
  }
  if (isNumber(var)) {
    cout<<memory[var].numval<<endl;
    return;
  }
  else if (isString(var)) {
    cout<<memory[var].strval<<endl;
    return;
  }
}
void sumfunc(vector<string> tokens) {
  if (tokens.size()<3) {
    cout<<"Syntax Error: sum <var1> <var2>"<<endl;
    return;
  }
  string a=tokens[1];
  string b=tokens[2];
  if (!isValidNumber(a,b)) return;
  cout<<memory[a].numval+memory[b].numval<<endl;
  return;
}
void subfunc(vector<string> tokens) {
  if (tokens.size()<3) {
    cout<<"Syntax Error: sub <var1> <var2>"<<endl;
    return;
  }
  string a=tokens[1];
  string b=tokens[2];
  if (!isValidNumber(a,b)) return;
  cout<<memory[b].numval-memory[a].numval<<endl;
  return;
}
void concatfunc(vector<string> tokens){
  if (tokens.size()<3) {
    cout<<"Syntax Error: concat <var1> <var2>"<<endl;
    return;
  }
  string a=tokens[1];
  string b=tokens[2];
  if (!isValidString(a,b)) return;
  cout<<memory[a].strval+memory[b].strval<<endl;
}
int main() {
  cout<<"Write a line of code"<<endl;
  while (true){
    string input;
    getline(cin,input);
    if (input=="exit") return 0;

    vector<string> tokens=parser(input);

    if (tokens[0]=="say") {
      definefunc(tokens);
    }
    else if (tokens[0]=="print") {
      printfunc(tokens);
    }
    else if (tokens[0]=="sum") {
      sumfunc(tokens);
    }
    else if (tokens[0]=="sub") {
      subfunc(tokens);
    }
    else if (tokens[0]=="concat") {
      concatfunc(tokens);
    }
  }
}
