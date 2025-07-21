#include<iostream>
#include<sstream>
#include<vector>
#include<unordered_map>
using namespace std;


struct Variable {
  string type=" ";
  string strval=" ";
  int numval=0;

};
unordered_map<string, Variable> memory;

vector<string> parser(const string& input) {
  vector<string> args;
  stringstream iss(input);
  string token;
  while (iss>>token) {
    args.push_back(token);
  }
  return args;
}

bool inMemory(const string& var) {
  return memory.count(var);
}
bool isValidName(const string& var) {
  return !var.empty() && !isdigit(var[0]);
}

bool isNumber(const string& var) {
  return inMemory(var) && memory[var].type=="number";
}
bool isString(const string& var) {
  return inMemory(var) && memory[var].type=="string";
}
bool isValidNumber(const string& a,const string& b) {
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
bool isValidString(const string& a,const string& b) {
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
void definefunc(const vector<string> &tokens) {
  if (tokens.size()<5 || tokens[2]!="is") {
    cout<<"Syntax Error: say <var> is <type> <value>"<<endl;
    return;
  }
  const string& var=tokens[1];
  const string& type=tokens[3];

  if (!isValidName(var)) {
    cout<<"Invalid variable name"<<endl;
    return;
  }
  if (inMemory(var)) {
    cout<<"Variable already defined"<<endl;
    return;
  }

  Variable v;
  v.type=type;
  if (type=="number") {
    const string& value=tokens[4];
    v.numval=stoi(value);
  }
  else if (type=="string") {
    string value=" ";
    for (int i=4;i<tokens.size();i++) {
      value+=tokens[i];
      if (i!=tokens.size()-1)value+=" ";
    }
          v.strval=value;
  }
  else {
          cout<<"Expected keyword: type identifier :: hint:number ? string ?"<<endl;
        }
  memory[var]=v;
}
void printfunc(const vector<string> &tokens) {
  if (tokens.size()<2 ) {
    cout<<"Syntax Error: print <var>"<<endl;
    return;
  }
  const string& var=tokens[1];
  if (!inMemory(var)) {
    cout<<"Variable might not have been initialized"<<endl;
    return;
  }
  if (isNumber(var)) {
    cout<<memory[var].numval<<endl;
  }
  else if (isString(var)) {
    cout<<memory[var].strval<<endl;
  }
}
void sumfunc(const vector<string> &tokens) {
  if (tokens.size()<3) {
    cout<<"Syntax Error: sum <var1> <var2>"<<endl;
    return;
  }

  const string& a=tokens[1];
  const string& b=tokens[2];
  if (!isValidNumber(a,b)) return;
  cout<<memory[a].numval+memory[b].numval<<endl;
}
void subfunc(const vector<string> &tokens) {
  if (tokens.size()<3) {
    cout<<"Syntax Error: sub <var1> <var2>"<<endl;
    return;
  }
  const string& a=tokens[1];
  const string& b=tokens[2];
  if (!isValidNumber(a,b)) return;
  cout<<memory[b].numval-memory[a].numval<<endl;
}
void concatfunc(const vector<string> &tokens){
  if (tokens.size()<3) {
    cout<<"Syntax Error: concat <var1> <var2>"<<endl;
    return;
  }
  const string& a=tokens[1];
  const string& b=tokens[2];
  if (!isValidString(a,b)) return;
  cout<<memory[a].strval+memory[b].strval<<endl;
}
void assignFunc(const vector<string> &tokens){
    if(tokens.size()<3){
        cout<<"Syntax Error: assign <var1> <var2>"<<endl;
        return;
    }
    const string& source=tokens[1];
    const string& target=tokens[2];
    if(!inMemory(source)) {
        cout<<"Variable "<<source<<" not defined"<<endl;
        return;
    }
    if(!isValidName(target)){
         cout<<"Invalid variable name"<<endl;
        return;
    }
      Variable v=memory[source];
      memory[target]=v;
    }
void erasefunc(const vector<string>& tokens) {
  if (tokens.size()<2) {
    cout<<"Syntax Error: erase <var>"<<endl;
  }
  if (inMemory(tokens[1])) {
    const string& var=tokens[1];
    memory.erase(var);
    cout<<"Variable "<<var<<" Deleted"<<endl;
  }
  else {
    const string& var=tokens[1];
    cout<<"Variable "<<var<<" does not exist"<<endl;
  }
}
int main() {
  cout<<"Write a line of code"<<endl;
  while (true){
    string input;
    getline(cin,input);
    if (input=="exit") return 0;

    vector<string> tokens=parser(input);

    if(tokens.empty()) continue;

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
    else if (tokens[0]=="assign"){
        assignFunc(tokens);
    }
    else if (tokens[0]=="erase") {
        erasefunc(tokens);
    }
  }
}
