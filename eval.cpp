#include "lambda2skibc.h"
#include <array>

any EVAL::visitToplevel(lambda2skibcParser::ToplevelContext *ctx) {
    if (top)    
        for (int i = 0; i < ctx->command().size(); i++)
            comm.push_back(any_cast<string>(visit(ctx->command(i))));      
    return 1;
}


any EVAL::visitC_term(lambda2skibcParser::C_termContext *ctx){ 
    string result_str = "";
    if (top)
        result_str = ctx->term()->getText();
    else
        result_str = any_cast<string>(visit(ctx->term())) + ";";
    return result_str;
}


any EVAL::visitC_sbid_ceq_term(lambda2skibcParser::C_sbid_ceq_termContext *ctx){
    string result_str;
    string sb = ctx->sbid()->getText();
    string t;
    if (top){
        result_str = ctx->getText();
    }
     else {
        result_str = any_cast<string>(visit(ctx->term()));
        sbid_term[sb] = result_str;
        result_str = sb + " := " + result_str + ";";
    }        
    return result_str;
}


any EVAL::visitC_sbid_cceq_term(lambda2skibcParser::C_sbid_cceq_termContext *ctx){
    string result_str;
    string sb = ctx->sbid()->getText();
    string t;
    if (top){
        result_str = ctx->getText();
    }
     else {
        result_str = any_cast<string>(visit(ctx->term()));
        sbid_term[sb] = result_str;
        result_str = sb + " ::= " + result_str + ";";
    }        
    return result_str;
}


any EVAL::visitC_dq_string(lambda2skibcParser::C_dq_stringContext *ctx){
    string result_str;
    if (top)
        result_str = ctx->getText();
    else
        result_str = any_cast<string>(visit(ctx->dqString()));
    return result_str;    
}


any EVAL::visitC_newline(lambda2skibcParser::C_newlineContext *ctx){
    string result_str;
    if (top)
        result_str = "NL";
    else
        result_str = "";
    return result_str;    
}


any EVAL::visitT_appterm(lambda2skibcParser::T_apptermContext *ctx) {
   return any_cast<string>(visit(ctx->appterm()));
}


any EVAL::visitT_abs_vst(lambda2skibcParser::T_abs_vstContext *ctx) {
    *changed_ptr = true;
    string vs_str = any_cast<string>(visit(ctx->vs()));
    string var_str = ctx->var()->getText();
    string result_str;
    if (var_str == vs_str)
        result_str = "I"; // conversion rule (1)
    else
        result_str = "(K" + vs_str + ")"; // conversion rule (2)
    return result_str;
}


any EVAL::visitT_abs_sapp(lambda2skibcParser::T_abs_sappContext *ctx) {    
    string result_str;
    *changed_ptr = true;
    string var_str = ctx->var()->getText();
    pair<string, string> p = any_cast<pair<string, string>>(visit(ctx->sappterm()));
    bool var_is_not_free_in_left = ((p.first).find(var_str) == string::npos);
    bool var_is_not_free_in_right = ((p.second).find(var_str) == string::npos);
    if (var_is_not_free_in_left)
        if (var_is_not_free_in_right)
            result_str = "(K(" + p.first + p.second + "))"; // conversion rule (2)
        else{
            if (var_str == p.second){
                if (p.first.length() == 1)
                    result_str = p.first;
                else
                    result_str = "(" + p.first + ")"; // conversion rule (6)
            }                
                
            else // conversion rule (4)
                result_str = "(B(" + p.first + ")(\\" + var_str + "." + p.second +"))";
        }            
    else
        if (var_is_not_free_in_right) // conversion rule (3)
            result_str = "(C(\\" + var_str + "." + p.first +")(" + p.second + "))";
        else // conversion rule (7)
            if (p.first == p.second && p.first.length() != 1)
                result_str = "(B(SII)(\\" +  var_str + "." + p.first +"))";
            else // conversion rule (5)
                result_str = "(S(\\" + var_str + "." + p.first +")(\\" + var_str + "." + p.second +"))";
    return result_str;
}


any EVAL::visitT_abs_term(lambda2skibcParser::T_abs_termContext *ctx) {
    string var_str = ctx->var()->getText();
    string term_str = any_cast<string>(visit(ctx->term()));
    string result_str = "(\\" + var_str + "." + term_str + ")";
    return result_str; 
}


any EVAL::visitSapp_app_a(lambda2skibcParser::Sapp_app_aContext *ctx) {
    pair<string, string> p;
    p.first = any_cast<string>(visit(ctx->appterm()));
    p.second = any_cast<string>(visit(ctx->aterm()));
    return p;
}


any EVAL::visitSapp_paren(lambda2skibcParser::Sapp_parenContext *ctx) {
    return visit(ctx->sappterm());
}


any EVAL::visitApp_a(lambda2skibcParser::App_aContext *ctx) {
    return any_cast<string>(visit(ctx->aterm()));
}


any EVAL::visitApp_app_a(lambda2skibcParser::App_app_aContext *ctx) {
    return any_cast<string>(visit(ctx->appterm())) + any_cast<string>(visit(ctx->aterm()));
}


any EVAL::visitA_dparen(lambda2skibcParser::A_dparenContext *ctx) {
    string result_str = any_cast<string>(visit(ctx->term()));
    if (result_str.length() != 1)
        result_str = "(" + result_str + ")";
    return result_str; 
}


any EVAL::visitA_paren(lambda2skibcParser::A_parenContext *ctx) {
    string result_str = any_cast<string>(visit(ctx->term()));
    if (result_str.length() != 1)
        result_str = "(" + result_str + ")";
    return result_str; 
}


any EVAL::visitA_vsterm(lambda2skibcParser::A_vstermContext *ctx) {
    return visit(ctx->vs());
}


any EVAL::visitVs_var(lambda2skibcParser::Vs_varContext *ctx) {
    return visit(ctx->var());
}


any EVAL::visitVs_skibc(lambda2skibcParser::Vs_skibcContext *ctx) {
    return visit(ctx->skibc());
}


any EVAL::visitVs_sbid(lambda2skibcParser::Vs_sbidContext *ctx) {
    return visit(ctx->sbid());
}


any EVAL::visitVs_paren(lambda2skibcParser::Vs_parenContext *ctx) {
    return visit(ctx->vs());
}


any EVAL::visitSkibc(lambda2skibcParser::SkibcContext *ctx) {
    return ctx->getText();
}


any EVAL::visitVar(lambda2skibcParser::VarContext *ctx) {
    return ctx->getText();
}
  

any EVAL::visitSbid(lambda2skibcParser::SbidContext *ctx) {
    return ctx->getText();
}
  

any EVAL::visitDqString(lambda2skibcParser::DqStringContext *ctx) {
    string result_str = ctx->getText();
    (result_str.erase(0, 1)).pop_back();
    return result_str;
}
