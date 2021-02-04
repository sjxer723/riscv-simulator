# ifndef _INSTRUCTIONFETCH_
# define _INSTRUCTIONFETCH_

#include<iostream>
# include "Decode.hpp"
# include "../register.hpp"
# include "../instruction.hpp"

class Fetch {
		friend class RISCV;
	private:
		Register *regist;

	public:
		ins instruction;
        bool notrun;

		Fetch(Register *r):regist(r),notrun(0){}

		void perform() {
		    if(regist->usedpc)notrun=true;
		    else{
		        notrun=false;
		        instruction.instr=regist->getinst();
		        //std::cout<<instruction.instr<<std::endl;
		    }
		}
		void pass(Decode &next) {
			next.instruction=instruction;
			if(notrun){next.instruction.type=LOCK;}
		}
};
# endif
