//
// Created by DELL on 2020/7/16.
//

#ifndef RISC_V_PREDICTION_HPP
#define RISC_V_PREDICTION_HPP

#include<iostream>
#include<cstring>
#include<vector>
class predict{
enum InsType{
        EMPTY,LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,LOCK
};
private:
    //success是总成功次数，total是总预测次数
    double success,total;
    std::vector<int>BEQrec;
    std::vector<int>BNErec;
    std::vector<int>BLTrec;
    std::vector<int>BGErec;
    std::vector<int>BLTUrec;
    std::vector<int>BGEUrec;

public:
    predict(){
        success=0,total=0;
        BEQrec.clear();
        BNErec.clear();
        BLTrec.clear();
        BGErec.clear();
        BLTUrec.clear();
        BGEUrec.clear();
    }

    bool prediction(int type) {
        int count=0;
        switch(type){
            case BEQ:{
                for(int i=0;i<10&&i<(int)BEQrec.size();i++){
                    count+=BEQrec[i];
                }
                if(count<0)return false;
                else return true;
            }
            case BNE:{
                for(int i=0;i<10&&i<(int)BNErec.size();i++){
                    count+=BNErec[i];
                }
                if(count<0)return false;
                else return true;
            }
            case BLT:{
                for(int i=0;i<10&&i<(int)BLTrec.size();i++){
                    count+=BLTrec[i];
                }
                if(count<0)return false;
                else return true;
            }
            case BGE:{
                for(int i=0;i<10&&i<(int)BGErec.size();i++){
                    count+=BGErec[i];
                }
                if(count<0)return false;
                else return true;
            }
            case BLTU:{
                for(int i=0;i<10&&i<(int)BLTUrec.size();i++){
                    count+=BLTUrec[i];
                }
                if(count<0)return false;
                else return true;
            }
            case BGEU:{
                for(int i=0;i<10&&i<(int)BGEUrec.size();i++){
                    count+=BGEUrec[i];
                }
                if(count<0)return false;
                else return true;
            }
             default:return true;
        }
            return true;
    }
    void record(int type,bool result,bool suc){
        switch(type){
            case BEQ:
                if(result){
                    if(BEQrec.size()<10)BEQrec.push_back(1);
                    else{
                        for(int i=1;i<10;i++)
                            BEQrec[i-1]=BEQrec[i];
                        BEQrec[9]=1;
                    }
                }else{
                    if(BEQrec.size()<10)BEQrec.push_back(-1);
                    else{
                        for(int i=1;i<10;i++)
                            BEQrec[i-1]=BEQrec[i];
                        BEQrec[9]=-1;
                    }
                }
                break;
            case BNE:
                if(result){
                    if(BNErec.size()<10)BNErec.push_back(1);
                    else{
                        for(int i=1;i<10;i++)
                            BNErec[i-1]=BNErec[i];
                        BNErec[9]=1;
                    }
                }else{
                    if(BNErec.size()<10)BNErec.push_back(-1);
                    else{
                        for(int i=1;i<10;i++)
                            BNErec[i-1]=BNErec[i];
                        BNErec[9]=-1;
                    }
                }
                break;
            case BLT:
                if(result){
                    if(BLTrec.size()<10)BLTrec.push_back(1);
                    else{
                        for(int i=1;i<10;i++)
                            BLTrec[i-1]=BLTrec[i];
                        BLTrec[9]=1;
                    }
                }else{
                    if(BLTrec.size()<10)BLTrec.push_back(-1);
                    else{
                        for(int i=1;i<10;i++)
                            BLTrec[i-1]=BLTrec[i];
                        BLTrec[9]=-1;
                    }
                }
                break;
            case BGE:
                if(result){
                    if(BGErec.size()<10)BGErec.push_back(1);
                    else{
                        for(int i=1;i<10;i++)
                            BGErec[i-1]=BGErec[i];
                        BGErec[9]=1;
                    }
                }else{
                    if(BGErec.size()<10)BGErec.push_back(-1);
                    else{
                        for(int i=1;i<10;i++)
                            BGErec[i-1]=BGErec[i];
                        BGErec[9]=-1;
                    }
                }
                break;
            case BLTU:
                if(result){
                    if(BLTUrec.size()<10)BLTUrec.push_back(1);
                    else{
                        for(int i=1;i<10;i++)
                            BLTUrec[i-1]=BLTUrec[i];
                        BLTUrec[9]=1;
                    }
                }else{
                    if(BLTUrec.size()<10)BLTUrec.push_back(-1);
                    else{
                        for(int i=1;i<10;i++)
                            BLTUrec[i-1]=BLTUrec[i];
                        BLTUrec[9]=-1;
                    }
                }
                break;
            case BGEU:
                if(result){
                    if(BGEUrec.size()<10)BGEUrec.push_back(1);
                    else{
                        for(int i=1;i<10;i++)
                            BGEUrec[i-1]=BGEUrec[i];
                        BGEUrec[9]=1;
                    }
                }else{
                    if(BGEUrec.size()<10)BGEUrec.push_back(-1);
                    else{
                        for(int i=1;i<10;i++)
                            BGEUrec[i-1]=BGEUrec[i];
                        BGEUrec[9]=-1;
                    }
                }
                break;
        }
        if(suc)++success;
        ++total;
    }
    void print(){
        std::cout<<"success"<<success<<" "<<"total"<<total<<std::endl;
        std::cout<<"rate="<<(double)(success/total)<<std::endl;
    }
};
#endif //RISC_V_PREDICTION_HPP
