`timescale 1ns / 1ps

module stackMachine
#(
	parameter N=8, //bits
	parameter S=8 //stack size
)
(
	clk,
	rst,
	x,
	opcode,
	o
);
	input						clk;
	input						rst;
	input signed		[N-1:0]	x;
	input				[2:0] 	opcode;
	output signed		[N-1:0]	o;

	reg signed			[N-1:0]	alu;
	reg signed			[N-1:0]	stack[S-1:0];
	reg 						push;
	reg 						op1;
	reg 						op2;
	
	integer j;
	
	assign o = stack[0];

	always@(*)
	begin
		push <= 0;
		op1 <= 0;
		op2 <= 0;
		alu <= stack[0];
		case(opcode)
		3'd0://nop
		begin
		 	alu <= stack[0];
		end
		3'd1://add
		begin
		 	alu <= stack[0] + stack[1];
		 	op2 <= 1'b1;		
		end
		3'd2://sub
		begin
		 	alu <= stack[0] - stack[1];	
		 	op2 <= 1'b1;
		end
		3'd3://mult
		begin
		 	alu <= stack[0] * stack[1];
		 	op2 <= 1'b1; 	
		end
		3'd4://push
		begin
		 	push <= 1;
		end
		3'd5://neg
		begin
		 	alu <= -1 * stack[0];
		 	op1 <= 1'b1; 
		end
		3'd6://and
		begin
		 	alu <= stack[0] & stack[1];
		 	op2 <= 1'b1; 
		end
		3'd7://or
		begin
		 	alu <= stack[0] | stack[1];
		 	op2 <= 1'b1; 
		end
		3'd8://xor
		begin
		 	alu <= stack[0] ^ stack[1];
		 	op2 <= 1'b1; 
		end
		endcase
	end


	always@(posedge clk or posedge rst)
	begin
		if(rst)
		begin
			for(j=0;j<S;j=j+1)
			begin
				stack[j] <= 0;
			end
		end
		else
		begin
			if(push)
			begin
				stack[0] <= x; 
				for(j=1;j<S;j=j+1)
				begin
					stack[j] <= stack[j-1];
				end
			end
			else if(op1)
			begin
				stack[0] <= alu; 
			end
			else if(op2)
			begin
				stack[0] <= alu; 
				for(j=1;j<S-1;j=j+1)
				begin
					stack[j] <= stack[j+1];
				end
			end
		end
	end
	
endmodule

