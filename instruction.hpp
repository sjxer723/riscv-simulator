# ifndef _INSTRUCTION_
# define _INSTRUCTION_

#include "type.hpp"
#include "Memory.hpp"
#include<stdio.h>

enum InsType{
    LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,LOCK
};
class ins {
    friend class Fetch;
    friend class Decode;
    friend class Excute;
    friend class MA;
    friend class WB;
public:
	InsType type;
	uint instr;
	uint rs1,rs2,rd,imm;
	uint src1,src2;
	uint res,pre,resultpc;//pre存放预测结果 
	
	ins(){instr=imm=rd=rs1=rs2=src1=src2=res=pre=resultpc=0;}
	void Type() {
		uint opcode,func3,func7;
		opcode=(instr&127);
		func3=((instr>>12)&7);
		func7=((instr>>25)&127);
		switch (opcode) {
			//U-Type		
			case 55: type=LUI; break;
			case 23: type=AUIPC; break;
			//J-Type		
			case 111: type=JAL; break;
			case 103: type=JALR; break;
			//B-Type		
			case 99: // 1100011
				switch (func3) {
					case 0: type=BEQ; break;		
					case 1: type=BNE; break; 		
					case 4: type=BLT; break;		
					case 5: type=BGE; break;		
					case 6: type=BLTU; break;		
					case 7: type=BGEU; break;		
				}
				break;
			//S-Type		
			case 35:// 0100011
				switch(func3) {
					case 0:	type=SB; break;			
					case 1: type=SH; break;			
					case 2: type=SW; break;			
				}
						break;
			//I-Type
			case 3: // 0000011
				switch(func3) {
					case 0: type=LB; break;			
					case 1: type=LH; break;			
					case 2: type=LW; break;			
					case 4: type=LBU; break;		
					case 5: type=LHU; break;		
				}
				break;		
			case 19:// 0010011
				switch(func3) {
					case 0: type=ADDI; break;		
					case 1:	type=SLLI; break;		
					case 2: type=SLTI; break;		
					case 3: type=SLTIU; break;		
					case 4: type=XORI;	break; 		
					case 5:	
						if(!func7) type=SRLI;	
						else type=SRAI;		
						break;
					case 6: type=ORI; break;
					case 7: type=ANDI; break;
				}
				break;
			//R-Type		
			case 51://0110011
				switch(func3) {
					case 0:	
						if (!func7) type = ADD;	
						else type = SUB;
						break;
					case 1: type = SLL; break;
					case 2: type = SLT;break;
					case 3: type = SLTU; break;
					case 4: type = XOR; break;
					case 5:	
						if(!func7) type = SRL;	
						else type=SRA;
						break;
					case 6: type=OR; break;	
					case 7: type=AND; break;
				}
				break;
			default: break;
		}
	}

	void setarg() {
		uint imm1, imm2, imm3, imm4;
		switch(type) {
			//R-type
			case ADD:case SUB:case SLL:case SLT:case SLTU:
			case XOR:case SRL:case SRA:case OR:case AND:
				rd=((instr>>7)&31);
				rs1=((instr>>15)&31);
				rs2=((instr>>20)&31);
				break;
			//J-type
			case JAL:
				imm1=((instr>> 12)&255),imm2=((instr>>20)&1);
				imm3=((instr>> 21)&1023),imm4=((instr>>31)&1);
				imm=(imm3<<1)+(imm2 <<11)+(imm1<<12)+(imm4<<20);
				imm = sext(imm,20);
				rd = ((instr>>7) & 31);
				break;
			case JALR:
				imm =((instr>>20)&4095);
				imm = sext(imm,11);
				rd = ((instr>>7)&31);
				rs1 = ((instr>>15)&31);
				break;
			//B-type
			case BEQ:case BNE:case BLT:case BGE:case BLTU:case BGEU:
				imm1=((instr>>7)&1), imm2=((instr>>8)&15);
				imm3=((instr>>25) & 63),imm4=((instr>>31)&1);
				imm=(imm2<<1)+(imm3<<5)+(imm1<<11)+(imm4<<12);
				imm=sext(imm,12);
				rs1=((instr>>15)&31);
				rs2=((instr>>20)&31);
				break;
			//S-type
			case SB:case SH:case SW:
				rs1=((instr>>15)&31);
				rs2=((instr>>20)&31);
				imm1=((instr>>7)&31);
				imm2=((instr>>25)&127);
				imm=imm1+(imm2<<5);
				imm=sext(imm,11);
				break;
			//I-type
			//12位立即数
			case ADDI:case SLTI:case SLTIU:
			case XORI:case ORI:case ANDI:
				imm = ((instr>>20)&4095);
				imm = sext(imm,11);
				rs1 = ((instr>>15)&31);
					rd = ((instr>>7)&31);
				break;
			//5位立即数
			case SLLI:case SRLI:case SRAI:
				rd=((instr>>7)&31);
				rs1=((instr>>15)& 31);
				imm=((instr>>20)&31);
				imm=sext(imm,4);
				break;
			case LB:case LH:case LW:case LBU:case LHU:
				imm=((instr>>20)&4095);
				imm=sext(imm,11);
				rd=((instr>>7)&31);
				rs1=((instr>>15)&31);
				break;
			//U-type
			case LUI:case AUIPC:
				imm = (instr>>12<<12);
				rd = ((instr>>7)&31);
				break;
			default:break;			
		}
	}
};

# endif
