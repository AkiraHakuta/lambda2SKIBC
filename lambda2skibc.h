#ifndef LAMBDA2SKIBC_H
#define LAMBDA2SKIBC_H


#include "antlr4-runtime.h"
#include "lambda2skibcLexer.h"
#include "lambda2skibcParser.h"
#include "lambda2skibcVisitor.h"

using namespace antlr4;
using namespace tree;
using namespace std;


class EVAL : public lambda2skibcVisitor{    
    public:
        bool* changed_ptr;
        vector<string> comm;
        map<string, string> sbid_term;
        bool top;

        any visitToplevel(lambda2skibcParser::ToplevelContext *context);

        any visitC_term(lambda2skibcParser::C_termContext *context); 

        any visitC_sbid_ceq_term(lambda2skibcParser::C_sbid_ceq_termContext *context);  

        any visitC_sbid_cceq_term(lambda2skibcParser::C_sbid_cceq_termContext *context);  

        any visitC_dq_string(lambda2skibcParser::C_dq_stringContext *context);  

        any visitC_newline(lambda2skibcParser::C_newlineContext *context);

        any visitT_appterm(lambda2skibcParser::T_apptermContext *context);

        any visitT_abs_vst(lambda2skibcParser::T_abs_vstContext *context);

        any visitT_abs_sapp(lambda2skibcParser::T_abs_sappContext *context);

        any visitT_abs_term(lambda2skibcParser::T_abs_termContext *context);

        any visitSapp_app_a(lambda2skibcParser::Sapp_app_aContext *context);

        any visitSapp_paren(lambda2skibcParser::Sapp_parenContext *context);

        any visitApp_a(lambda2skibcParser::App_aContext *context);

        any visitApp_app_a(lambda2skibcParser::App_app_aContext *context);

        any visitA_paren(lambda2skibcParser::A_parenContext *context);

        any visitA_dparen(lambda2skibcParser::A_dparenContext *context);

        any visitA_vsterm(lambda2skibcParser::A_vstermContext *context);

        any visitVs_var(lambda2skibcParser::Vs_varContext *context);

        any visitVs_skibc(lambda2skibcParser::Vs_skibcContext *context);

        any visitVs_sbid(lambda2skibcParser::Vs_sbidContext *context);

        any visitVs_paren(lambda2skibcParser::Vs_parenContext *context);

        any visitSkibc(lambda2skibcParser::SkibcContext *context);

        any visitVar(lambda2skibcParser::VarContext *context);

        any visitSbid(lambda2skibcParser::SbidContext *context);

        any visitDqString(lambda2skibcParser::DqStringContext *context);
          
};

#endif  // LAMBDA2SKIBC_H