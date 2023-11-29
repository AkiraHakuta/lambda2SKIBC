#include "lambda2skibc.h"
#include <iomanip>

string indent_sp(int size)
{ 
    string result = "";
    for(int i = 0; i < size; i++)
      result += " ";
    return result;
}


string beautify_lisp_string(string in_string)
{
    int indent_size = 3;
    int curr_indent = 0;
    string out_string = string(1,in_string[0]);
    string indent = "";
    for (int i = 1; i < in_string.size(); i++)
        if (in_string[i] == '(' and  in_string[i+1] != ' '){
           curr_indent += indent_size;
           out_string += '\n' + indent_sp(curr_indent) + '(';
        }
        else if (in_string[i] == ')'){
          out_string += ')';
          if (curr_indent >= indent_size)
            curr_indent -= indent_size;
        }
        else
          out_string += in_string[i];     
    return out_string;
}


EVAL* e = new EVAL;
int step;
bool trace;

string eval1(string data, bool* changed_ptr)
{
    ANTLRInputStream input;
    
    e->changed_ptr = changed_ptr;
    
    input.load(data);
    lambda2skibcLexer lexer(&input);
    CommonTokenStream tokens(&lexer);           
    /*
    cout << "Tokens:" << endl;
    tokens.fill();
    for (Token *token : tokens.getTokens())
    cout << token->toString() << endl;/**/    
    lambda2skibcParser parser(&tokens);
    tree::ParseTree *tree = parser.command();    
    /*
    cout << endl << "Parse tree (Lisp format) :" << endl;
    string lisp_tree_str = tree->toStringTree(&parser);
    cout << beautify_lisp_string(lisp_tree_str) << endl;/**/   
    return any_cast<string>(e->visit(tree));  
}


string eval(string data){ 
    bool changed = false;
    string result_str = eval1(data, &changed);
    if (trace){
        step++;
        cout << setw(4) << step << ": " << result_str << endl;
    }
    if (changed)
        return eval(result_str);        
    else
        return result_str;
}


int main(int argc, const char *args[])
{   
    if (argc == 3 && string(args[2]) == "-t")
        trace = true;
    else
        trace = false;
    ifstream ifs;
    string result_str;
    string filename = args[1];
    ifs.open(filename);
    string data,buf;
    while (!ifs.eof()){
        getline(ifs, buf);
        data += buf + "\n";
    }
    ANTLRInputStream input;
    input.load(data);
    lambda2skibcLexer lexer(&input);
    CommonTokenStream tokens(&lexer);    
    lambda2skibcParser parser(&tokens);
    tree::ParseTree *tree = parser.toplevel();    
    e->visit(tree);     
    e->top = false; 
    for (int i = 0; i < e->comm.size(); i++){
        if (trace){
            step = 0;
            cout << endl; 
            cout << setw(4) << step << ": "<< e->comm[i] << ";" << endl;   
        }
        result_str =  eval(e->comm[i]);
        if (!trace)
            cout << result_str << endl;
    }
    return 0;
}

