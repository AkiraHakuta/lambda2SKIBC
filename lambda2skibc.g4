grammar lambda2skibc;

toplevel
    : (command ';')+ 
    ;

command
    : term                           # c_term
    | sbid ':=' term                 # c_sbid_ceq_term
    | sbid '::=' term                # c_sbid_cceq_term
    | 'putStr' '(' dqString ')'      # c_dq_string
    | 'NL'                           # c_newline
    ;

term 
    : appterm                        # t_appterm  
    | '\\' var '.' vs                # t_abs_vst 
    | '\\' var '.' sappterm          # t_abs_sapp       
    | '\\' var '.' term              # t_abs_term
    ;

sappterm
    : appterm aterm                  # sapp_app_a
    | '(' sappterm ')'               # sapp_paren
    ;

appterm 
    : aterm                          # app_a
    | appterm aterm                  # app_app_a    
    ;

aterm                                                     
    : vs                             # a_vsterm
    | '(' '(' term ')' ')'           # a_dparen
    | '(' term ')'                   # a_paren           
    ;

vs    
    : var                            # vs_var
    | skibc                          # vs_skibc  
    | sbid                           # vs_sbid
    | '(' vs ')'                     # vs_paren 
    ;


skibc : SKIBC  ;
var : LCID ;
sbid : SBID ;
dqString : StringLiteral;


SKIBC  : [SKIBC] ;
LCID : [a-z] ;
SBID : '[' [a-zA-Z0-9_']+ ']';
StringLiteral : '"' (~["\\\r\n_])* '"';
WS : [ \t\n\r]+                               -> skip;
COMMENT : '/*' .*? '*/'                       -> skip;
SL_COMMENT :  '//' .*? '\n'                   -> skip;
