#pragma once 

#include <vector>

#include "Structure.h"
#include "IfCode.h"

class ConditionalStruct : public Structure {

public:

    ConditionalStruct(Expression * expr, Block * b, vector <IfCode *> elseIf, Block * bElse) { // unique if condition with list of elseIf conditions
        this->ifCode = new IfCode(expr,b);
        this->listElseIfCode = elseIf;
        this->blockElse = bElse;
    };

    string getIR(BasicBlock **bb) {
        #ifdef DEBUG
        cout << "getIR ConditionalStruct starting" << endl;
        cout << "Current BasicBlock is : " << *bb << " | addressed at: " << bb << endl;
        #endif

        BasicBlock *bbIf = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name()); // création du basic block if 

        BasicBlock *bbAfterConditionalStruct = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name()); // création du basic block AfterConditionalStruct au CFG
        bbIf->setUnconditionalJump(bbAfterConditionalStruct); // après le code du block if on passe à la suite du conditionalStruct

        (*bb)->cfg->add_bb(bbAfterConditionalStruct);  // ajout du bbAfterConditi
        (*bb)->cfg->add_bb(bbIf);             // ajout du bbIf au CFGonalStruct au CFG, dont on lira les codelines dans la suite des visiteurs

        BasicBlock **bbIfPointer = new BasicBlock *;
        (*bbIfPointer) = bbIf;
        
        ifCode->getBlock()->getIR(bbIfPointer);     // lecture des codelines du block if, qui sont mises dans le bbIf
        bbAfterConditionalStruct->setUnconditionalJump((*bb)->getUnconditionalJump()); // donner la sortie du bb courant au prochain bb après le If, pour qu'il ait toujours un bloc suivant
        
        string conditionRegisterIf = ifCode->getCondition()->getIR(bb); // on lit la condition du if
        (*bb)->setCondition(conditionRegisterIf);  // si cette condition est vérifiée
        (*bb)->setConditionalJump(bbIf);           // alors on rentre dans le bb if

        BasicBlock *bbElse = new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name()); // création du basic block else
        BasicBlock **bbPointerElse = new BasicBlock*;
        (*bbPointerElse) = bbElse;

        if (blockElse != nullptr) {
            (*bb)->setUnconditionalJump(bbElse); // sinon c'est le if qui a pour sortie le else
        } else {
            (*bb)->setUnconditionalJump(bbAfterConditionalStruct); // sinon on passe au bb de la suite du code
        }
        
        vector <BasicBlock *> bbConditionElseIf; // liste des conditions des elseIf
        vector <BasicBlock *> bbCodeElseIf; // liste des blocks à executer si la condition des elseIf est vérifiée
        vector <BasicBlock **> bbConditionElseIfPointer; // liste des conditions des elseIf
        vector <BasicBlock **> bbCodeElseIfPointer; // liste des blocks à executer si la condition des elseIf est vérifiée
        
        string conditionRegisterElseIf;

        if (listElseIfCode.size()>0) { // s'il y a des elseIf
            // on crée les bb de chaque elseIf (1 pour la condition et 1 pour le contenu du else if), on les ajoute au CFG et on lit leur codelines
            for(int i=0; i<listElseIfCode.size(); i++) {
                bbConditionElseIf.push_back(new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name())); 
                bbCodeElseIf.push_back(new BasicBlock((*bb)->cfg, (*bb)->cfg->new_BB_name()));
                BasicBlock **bbPointer = new BasicBlock*;
                (*bbPointer) = bbCodeElseIf[i];
                bbCodeElseIfPointer.push_back(bbPointer);
                BasicBlock **bbPointerCond = new BasicBlock*;
                (*bbPointerCond) = bbConditionElseIf[i];
                bbConditionElseIfPointer.push_back(bbPointerCond);
                
                (*bb)->cfg->add_bb(bbConditionElseIf[i]);
                (*bb)->cfg->add_bb(bbCodeElseIf[i]);

                (*(bbCodeElseIfPointer[i]))->setUnconditionalJump(bbAfterConditionalStruct); // chaque block de code elseIf a pour sortie le bb de la suite du code
                listElseIfCode[i]->getBlock()->getIR(bbCodeElseIfPointer[i]);
            }

            (*bb)->setUnconditionalJump(bbConditionElseIf[0]); // si la condition du if est fausse on passe au 1er else if
            
            // on établit les liens entre chaque bb condition elseIf dans le CFG, sauf pour le dernier
            int i = 0;
            while(i<bbConditionElseIf.size()-1) {
                conditionRegisterElseIf = listElseIfCode[i]->getCondition()->getIR(bbConditionElseIfPointer[i]); // on lit la condition du else if
                bbConditionElseIf[i]->setConditionalJump(bbCodeElseIf[i]);              // alors on rentre dans le bb de ce else if
                bbConditionElseIf[i]->setUnconditionalJump(bbConditionElseIf[i+1]);     // sinon on passe au prochain bb else if
                bbConditionElseIf[i]->setCondition(conditionRegisterElseIf);            // si elle est vérifiée
                i++;
            }
            // pour le dernier elseIf
            conditionRegisterElseIf = listElseIfCode[i]->getCondition()->getIR((bbConditionElseIfPointer[i])); // on lit la condition du else if
            bbConditionElseIf[i]->setCondition(conditionRegisterElseIf); // si elle est vérifiée
            if (blockElse != nullptr) { // s'il y a un else 
                bbConditionElseIf[i]->setUnconditionalJump(bbElse); // le dernier elseIf a pour sortie le else
            } else {
                bbConditionElseIf[i]->setUnconditionalJump(bbAfterConditionalStruct); // sinon il a pour sortie la suite du code
            }
            bbConditionElseIf[i]->setConditionalJump(bbCodeElseIf[i]); // si la confition du else if est vrai alors on rentre dans le bb de ce else if
        } 

        if (blockElse != nullptr) { // s'il y a un else
            (*bb)->cfg->add_bb(bbElse);           // ajout du bbElse au CFG
            (*bbPointerElse)->setUnconditionalJump(bbAfterConditionalStruct); // le else a pour sortie la suite après conditionalStruct
            blockElse->getIR(bbPointerElse);            // lecture des codelines du block else, qui sont mises dans le bbElse
        }

        *bb = bbAfterConditionalStruct; // à la sortie de la structure conditionnelle (if, else if ou else) le bloc courant est le bbAfterConditionalStruct, qu'on va lire par la suite
        return "";
    }

    ~ConditionalStruct() {
        for(int i=0; i<listElseIfCode.size(); i++) {
            delete listElseIfCode[i];
        }
        delete ifCode;
        delete blockElse;
    };

    vector<IfCode *> getListElseIf() {
        return listElseIfCode;
    }

private:
    IfCode* ifCode;
    vector<IfCode*> listElseIfCode;
    Block* blockElse;
};