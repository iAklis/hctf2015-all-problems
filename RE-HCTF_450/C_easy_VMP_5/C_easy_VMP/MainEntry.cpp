#include <cstdio>
#include <Windows.h>
#include "Stack.h"
#include "VM.h"

int main()
{

	char Check_HCTF[] = "\x7b\x70\x6a\x67\x72\x73\x75\x55\x44\x32\x48\x50\x11\x12\x13\x14\x15";
	
	char Select_check_1[] = "0123456789qazwsxedcrtgbyhnujmiolp";
	char Cmp_check_1[] = "\x38\x7a\x34\x72\x6e\x65\x36";
	char Cmp_check_2[] = "\x38\x36\x33\x6e\x74\x36\x65";
#ifdef _DEBUG
	char stringIn[] = "HCTF{123412341234123489}";
	printf("addr1 = %x \n", stringIn);
	printf("addr2 = %d \n", Check_HCTF);
#else
	char stringIn[40] = {0};
	scanf_s("%s", stringIn, 40);
#endif
	/*
	DWORD CODE[] =
	{ 
	VM_X00_START, 
	VM_PUSH, PUSH_NUM, (DWORD)stringIn, //NUM1  push addr of input Str
		
	VM_POP,POP_EBX,
	VM_PUSH,PUSH_EBX,				//EBX = ADDR STR

	VM_STRLEN_CALL, //pop addr, call strlen, push result

	VM_PUSH, PUSH_NUM, 0x0,	//NUNM2 push 0x0 i = 0
	VM_CMP,			//cmp <-----

	VM_PUSH, PUSH_NUM, 0x23,	//push NUM3 is jum to exit
	VM_JZ, Jump_From_EIP,		//pop NUM3 JZ  (18)
	 
	VM_POP,POP_EAX,		//pop eax  ;eax = i

	VM_PUSH,PUSH_EBX,	//EBX: push addr of input Str
	VM_PUSH,PUSH_EAX,	//PUSH i
	
	VM_ADD,				//Pop i ,add i str
	VM_PUSH,PUSH_MEM|PUSH_MEM_BYTE, //POP STR, FIND BYTE STR, PUSH result
	VM_PUSH,PUSH_NUM,0x6,    //num push 6 (6)
	VM_XOR,					 //pop 6,top xor 6

	VM_PUSH,PUSH_EBX,	//EBX: push addr of input Str
	VM_PUSH,PUSH_EAX,	//PUSH i
	VM_ADD,				//Pop i ,add i str
	VM_POP,POP_MEM|POP_MEM_BYTE,//pop addr,pop result, Set That addr      

	VM_PUSH,PUSH_EAX,	//EAX = i
	VM_PUSH,PUSH_NUM,0x1,	//NUM = 1
	VM_ADD,			//I = I+1
	VM_POP,POP_EAX,		//eax = i
	VM_PUSH,PUSH_EAX,	//

	VM_PUSH,PUSH_NUM,-0x29,	//NUM5  jmp code
	VM_JMP, Jump_From_EIP,		//circle jmp
	VM_EXIT };
	*/
	DWORD CALL_END_4[] =
	{
		/////////////////////////Data and function/////////////////////
		VM_EXIT_FAIL,//END
		VM_EXIT_FAIL,
		/////////////////////////Code Start/////////////////////////////
		VM_X00_START,
		////JMP_TO_ENCODE
		VM_PUSH, PUSH_NUM, 78,
		VM_JMP, Jump_From_EIP,
		////��Ҫ���ܵĴ���//////////////
		////////////////////////////////
		VM_X00_START,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x8,
		VM_JMP, Jump_From_EIP,//JMP_TO_CODE
		//���ݶ�
		0x32,
		0x3C,
		0x41,
		0x43,
		0x36,
		0x40,
		0x48,
		0xFF,
		//
		VM_PUSH, PUSH_NUM, (DWORD)CALL_END_4,
		VM_PUSH, PUSH_NUM, 64,//datasec!!
		VM_ADD,//���������ݶ�
		VM_POP, POP_EAX,//EAX = STRIN

		VM_PUSH, PUSH_NUM, 0x0,
		VM_POP, POP_EBX,//EBX = i

		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM_DWORD | PUSH_MEM,
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		//BUG
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,
		//
		VM_PUSH, PUSH_NUM, 0x4,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_NUM, 28,
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,-46,//BACK
		VM_JMP,Jump_From_EIP,
		VM_EXIT_SUCCESS,
		0xAABBCCDD,
		//////////////////////////////
		////////////////////////////////
		VM_PUSH, PUSH_NUM, (DWORD)(CALL_END_4 + 8),
		VM_POP, POP_EAX,   ///EAX = addr need change
		VM_PUSH, PUSH_NUM, 0x0,
		VM_POP, POP_EBX, ///EBX = i

		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_DWORD,	//GET
		VM_PUSH, PUSH_NUM, 0xAABBCCDD,
		VM_CMP,
		VM_POP, POP_DEL,

		VM_PUSH, PUSH_NUM, 24,
		VM_JZ, Jump_From_EIP,

		//������
		//VM_PUSH, PUSH_NUM, 0x31,
		//VM_XOR,
		VM_PUSH,PUSH_NUM,0xFFFFFFFF,
		VM_AND,
		//
		////////
		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_POP, POP_MEM | POP_MEM_DWORD,		//SET
		VM_PUSH, PUSH_EBX,
		VM_PUSH, PUSH_NUM, 0x4,///����������
		VM_ADD,
		VM_POP, POP_EBX,
		VM_PUSH, PUSH_NUM, -42,
		VM_JMP, Jump_From_EIP,
		//ѭ������
		
		//jmp��ȥ
		VM_PUSH, PUSH_NUM, 0x8,
		VM_JMP, Jump_From_OEP,
		///////FUN2////
		VM_POP, POP_DEL,
		VM_EXIT_SUCCESS,
	};
	const DWORD FUNC_CHECK_1[] =
	{
		VM_EXIT_SUCCESS,
		VM_EXIT_SUCCESS,
		/////////////////////////Code Start/////////////////////////////
		VM_X00_START,
		VM_PUSH,PUSH_NUM,15,//JMP TO MAIN
		VM_JMP,Jump_From_EIP,
		//////////FUN1////////////
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_EBX,
		VM_PUSH, PUSH_NUM, (DWORD)Select_check_1,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_PUSH, PUSH_NUM,20, 
		VM_JMP,Jump_From_EIP,
		/////////////////////////
		VM_POP,POP_EAX,	//EAX = IN
		VM_PUSH,PUSH_NUM,0,

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0xF8000000,
		VM_AND,
		
		VM_PUSH,PUSH_NUM,27,
		VM_SHR,

		//JMP TO FUNTION
		VM_PUSH,PUSH_NUM,0x7,
		VM_JMP,Jump_From_OEP,
		//END

		VM_PUSH, PUSH_EAX,
		VM_PUSH,PUSH_NUM, 0x5,
		VM_SHL,
		VM_PUSH,PUSH_NUM,0,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,-39,
		VM_JMP,Jump_From_EIP,
		VM_EXIT_SUCCESS,
	};
	DWORD FUNC_CHECK_2[]
	{
		VM_EXIT_SUCCESS,
		VM_EXIT_SUCCESS,
		VM_X00_START,
//////////////////////////////////////////////	

		VM_POP,POP_EAX, //EAX = PARA1 ChangeCode
		VM_POP,POP_EBX, //EBX = PARA2 strin
		
		VM_PUSH,PUSH_NUM,0x0,//ѹջ���ڼ���
		
		VM_PUSH,PUSH_EBX,

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0xF0000000,	//ȡǰ������
		VM_AND,
		
		VM_PUSH,PUSH_NUM,0x1C,
		VM_SHR,//��λ����
		VM_PUSH,PUSH_NUM,0x1,
		VM_SHR,
		VM_PUSH,PUSH_NUM,0x2,
		VM_SHL,

		VM_SHL,//��λ��������
		
		VM_PUSH, PUSH_NUM, 0xF0000000,
		VM_AND,//ȥ������

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x4,
		VM_SHL,
		VM_PUSH,PUSH_NUM,0x0,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,-49,
		VM_JMP,Jump_From_EIP,
		///////
		VM_PUSH,PUSH_NUM,0,
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_NUM,28,
		VM_POP,POP_EAX,

		VM_PUSH, PUSH_EAX,//<---
		VM_SHR,
	
		VM_PUSH,PUSH_EBX,
		VM_OR,
		VM_POP,POP_EBX,
		
		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x4,
		VM_SUB,
		VM_POP,POP_EAX,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_CMP,
		VM_POP, POP_DEL,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,-32,
		VM_JMP,Jump_From_EIP,
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_EBX,
		VM_EXIT_SUCCESS,
		
	};
	DWORD FUN_CHECK_3_FUN_1[] = 
	{
		VM_EXIT_SUCCESS,
		VM_EXIT_SUCCESS,
		VM_X00_START,
//////////////////////////////////////////////
		VM_POP,POP_DEL,
		//һ������
		VM_PUSH, PUSH_NUM, 0xFDB97531,
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_2,
		VM_FAKE_CALL,
		VM_POP, POP_DEL,
		VM_EXIT_SUCCESS,
	};
	DWORD FUN_CHECK_3_FUN_2[] =
	{
		VM_EXIT_SUCCESS,
		VM_EXIT_SUCCESS,
		VM_X00_START,
		//////////////////////////////////////////////
		VM_POP, POP_DEL,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_EAX,
		//һ������
		VM_PUSH, PUSH_NUM, 0xE0000000,
		VM_AND,
		VM_PUSH, PUSH_NUM, 29,
		VM_SHR,
		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_NUM, 3,
		VM_SHL,
		VM_OR,
		VM_EXIT_SUCCESS,
	};
	DWORD FUNC_CHECK_3X1[] =
	{
		/////////////////////////Data and function/////////////////////
		VM_EXIT_SUCCESS,
		VM_EXIT_SUCCESS,
		/////////////////////////Code Start/////////////////////////////
		VM_X00_START,
		////JMP_TO_ENCODE
		VM_PUSH,PUSH_NUM,11,
		VM_JMP,Jump_From_EIP,
		////��Ҫ���ܵĴ���//////////////
		VM_X00_START ^ 0x28,
		VM_PUSH^0x28,
		PUSH_NUM ^ 0x28,
		(DWORD)FUN_CHECK_3_FUN_1 ^ 0x28,
		VM_FAKE_CALL ^ 0x28,
		VM_PUSH ^ 0x28,
		PUSH_NUM ^ 0x28,
		58 ^ 0x28,
		VM_JMP ^ 0x28,
		Jump_From_EIP ^ 0x28,
		0xFFFFAAAA,
		////////////////////////////////
		VM_PUSH, PUSH_NUM, (DWORD)(FUNC_CHECK_3X1 + 8),
		VM_POP,POP_EAX,   ///EAX = addr need change
		VM_PUSH,PUSH_NUM,0x0,
		VM_POP,POP_EBX, ///EBX = i

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_DWORD,	//GET
		VM_PUSH, PUSH_NUM, 0xFFFFAAAA,
		VM_CMP,
		VM_POP,POP_DEL,
	
		VM_PUSH,PUSH_NUM,24,
		VM_JZ,Jump_From_EIP,

		//������
		VM_PUSH,PUSH_NUM,0x28,
		VM_XOR,
		////////
		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_POP,POP_MEM | POP_MEM_DWORD,		//SET
		VM_PUSH,PUSH_EBX,
		VM_PUSH,PUSH_NUM,0x4,///����������
		VM_ADD,
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_NUM, -42,
		VM_JMP,Jump_From_EIP,
		//ѭ������
		
		//jmp��ȥ
		VM_PUSH,PUSH_NUM,0x8,
		VM_JMP,Jump_From_OEP,
		///////FUN2////
		VM_POP,POP_DEL,
		VM_EXIT_SUCCESS,
		
	};
	DWORD FUNC_CHECK_3X2[] = 
	{
		/////////////////////////Data and function/////////////////////
		VM_EXIT_SUCCESS,
		VM_EXIT_SUCCESS,
		/////////////////////////Code Start/////////////////////////////
		VM_X00_START,
		////JMP_TO_ENCODE
		VM_PUSH, PUSH_NUM, 11,
		VM_JMP, Jump_From_EIP,
		////��Ҫ���ܵĴ���//////////////
		VM_X00_START ^ 0x28,
		VM_PUSH ^ 0x28,
		PUSH_NUM ^ 0x28,
		(DWORD)FUN_CHECK_3_FUN_2 ^ 0x28,
		VM_FAKE_CALL ^ 0x28,
		VM_PUSH ^ 0x28,
		PUSH_NUM ^ 0x28,
		58 ^ 0x28,
		VM_JMP ^ 0x28,
		Jump_From_EIP ^ 0x28,
		0xFFFFAAAA,
		////////////////////////////////
		VM_PUSH, PUSH_NUM, (DWORD)(FUNC_CHECK_3X2 + 8),
		VM_POP, POP_EAX,   ///EAX = addr need change
		VM_PUSH, PUSH_NUM, 0x0,
		VM_POP, POP_EBX, ///EBX = i

		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_DWORD,	//GET
		VM_PUSH, PUSH_NUM, 0xFFFFAAAA,
		VM_CMP,
		VM_POP, POP_DEL,

		VM_PUSH, PUSH_NUM, 24,
		VM_JZ, Jump_From_EIP,

		//������
		VM_PUSH, PUSH_NUM, 0x28,
		VM_XOR,
		////////
		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_POP, POP_MEM | POP_MEM_DWORD,		//SET
		VM_PUSH, PUSH_EBX,
		VM_PUSH, PUSH_NUM, 0x4,///����������
		VM_ADD,
		VM_POP, POP_EBX,
		VM_PUSH, PUSH_NUM, -42,
		VM_JMP, Jump_From_EIP,
		//ѭ������

		//jmp��ȥ
		VM_PUSH, PUSH_NUM, 0x8,
		VM_JMP, Jump_From_OEP,
		///////FUN2////
		VM_POP, POP_DEL,
		VM_EXIT_SUCCESS,
	};
	DWORD CODE[] =
	{
		/////////////////////////Data and function/////////////////////
		VM_EXIT_FAIL,
		VM_EXIT_FAIL,
		/////////////////////////Code Start/////////////////////////////
		VM_X00_START,
		/////////////////////////fun1 strlen////////////////////////////////
		VM_PUSH, PUSH_NUM, (DWORD)stringIn, //NUM1  push addr of input Str  *stack 1
		VM_POP, POP_EBX,
		VM_PUSH, PUSH_EBX,					//EBX = ADDR STR
		VM_PUSH, PUSH_EBX,					//����һ�� addr of input str
		VM_STRLEN_CALL,						//pop addr, call strlen, push result *stack1
		VM_PUSH, PUSH_NUM, 0x18,			
		VM_CMP,								//���㳤���Ƿ�Ϊ24  *stack 2

		VM_PUSH, PUSH_NUM, 0x7,			    //push jmp next func(jmpto_fun2)  *stack 3
		VM_JZ, Jump_From_EIP,				//pop and JZ  (18)	*stack 2
		VM_PUSH, PUSH_NUM, 0,				//jmp code to Fail   *stack 3
		VM_JMP, Jump_From_OEP,				//jmp   *stack 2
		///////////////////////fun2 xor HCTF{//////////////////////////////

		VM_POP, POP_DEL,					//ƽ��ջ�ռ䣨����ɾ����*Stack 1 topofStack:length of addr 
		VM_PUSH, PUSH_NUM, 0x5,				//HCTF{ 5��
		VM_PUSH, PUSH_NUM, 0x0,				//push 0x0 i = 0  *Stack 2
		VM_CMP,			//cmp <-----

		VM_PUSH, PUSH_NUM, 0x23,	//push NUM3 is jum to exit
		VM_JZ, Jump_From_EIP,		//pop NUM3 JZ  (18)

		VM_POP, POP_EAX,		//pop eax  ;eax = i
		VM_PUSH, PUSH_EBX,	//EBX: push addr of input Str
		VM_PUSH, PUSH_EAX,	//PUSH i
		VM_ADD,				//Pop i ,add i str
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE, //POP STR, FIND BYTE STR, PUSH result
		VM_PUSH, PUSH_NUM, 0x33,    //num push 0x33 
		VM_XOR,					 //pop 0x33,top xor 0x33

		VM_PUSH, PUSH_EBX,			   //EBX: push addr of input Str
		VM_PUSH, PUSH_EAX,			   //PUSH i
		VM_ADD,						   //Pop i ,add i str
		VM_POP, POP_MEM | POP_MEM_BYTE,//pop addr,pop result, Set That addr     

		VM_PUSH, PUSH_EAX,	//EAX = i
		VM_PUSH, PUSH_NUM, 0x1,	//NUM = 1
		VM_ADD,			//I = I+1
		VM_POP, POP_EAX,		//eax = i
		VM_PUSH, PUSH_EAX,	//

		VM_PUSH, PUSH_NUM, -0x29,	//NUM5  jmp code
		VM_JMP, Jump_From_EIP,		//circle jmp
		////////////////func check last '}'///////////////////////////
		VM_POP, POP_DEL,					//ƽ��ջ�ռ�
		VM_POP, POP_DEL,					//ƽ��ջ�ռ� *Stack 2 topofStack:length of addr X 2
		VM_PUSH, PUSH_EBX,					//EBX: push addr of input Str
		VM_ADD,								 //Pop STR ,add 24  str
		VM_PUSH, PUSH_NUM, 0x1,
		VM_SUB,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
	
		VM_PUSH, PUSH_NUM, 0x33,		//num push 0x33 
		VM_XOR,							//pop 0x33,top xor 0x33
		VM_PUSH, PUSH_NUM, 0x4E,		//num push 0x4e
		VM_CMP,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0,				//jmp code to Fail   *stack 3
		VM_JMP, Jump_From_OEP,
		///////////////////func push HCTF{ xor 0x33////////////////////////////////

		VM_POP, POP_DEL,					//ƽ��ջ�ռ�
		VM_POP, POP_DEL,					//ƽ��ջ�ռ� 
		

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x1,
		VM_SUB,
		VM_POP, POP_EAX,
		VM_PUSH, PUSH_EAX,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH,PUSH_NUM,0x5,		//Jmp to next Fun
		VM_JZ, Jump_From_EIP,
		
		VM_PUSH,PUSH_NUM, -0x23,	//Circle Jmp
		VM_JMP, Jump_From_EIP,
		///////////////////fun check HCTF{/////////////////////////////////////


		VM_PUSH,PUSH_NUM,0,
		VM_POP,POP_EBX,				//EBX = i		
		VM_PUSH, PUSH_NUM, (DWORD)Check_HCTF,
		VM_POP,POP_EAX,				//EAX = ADDR Check_HCTF

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_EAX,			//EAX = EAX+i
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_CMP,
		VM_PUSH,PUSH_NUM,0x5,  // <------ok
		
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,0x0,
		VM_JMP,Jump_From_OEP,  //  <----- Fail

		VM_POP, POP_DEL,					//ƽ��ջ�ռ�
		VM_POP, POP_DEL,					//ƽ��ջ�ռ� 
		
		VM_PUSH,PUSH_EBX,
		VM_PUSH,PUSH_NUM,1,

		VM_ADD,
		VM_POP,POP_EBX,

		VM_PUSH,PUSH_EBX,
		VM_PUSH,PUSH_NUM,0x5,
		VM_CMP,
		VM_POP, POP_DEL,					//ƽ��ջ�ռ�
		VM_POP, POP_DEL,					//ƽ��ջ�ռ� 
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH, PUSH_NUM, -0x36,
		VM_JMP,Jump_From_EIP,

		///////////////////fun ѹ����ջģ��//////////////////////////////

		
		VM_POP,POP_EAX,					//EAX = strlen(Input Str)
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_POP,POP_EBX,					//EBX = ADDR STR IN
		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_EBX,

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_EAX,
		VM_XOR,
		VM_POP,POP_EAX,
		VM_PUSH, PUSH_EAX,					//����ռ������Ǹ����

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x4,
		VM_CMP,
		VM_PUSH,PUSH_NUM,28,//������
		VM_JZ,Jump_From_EIP,
		VM_POP, POP_DEL,					//ƽ��ջ�ռ�
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_NUM,0x3,
		VM_SHL,
		VM_SHL,
		VM_OR,

		
		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x1,
		VM_ADD,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_NUM,-39,//������
		VM_JMP,Jump_From_EIP,
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_NUM,0x0,
		VM_POP,POP_EAX,

		VM_PUSH,PUSH_EBX,
		VM_STRLEN_CALL,

		VM_PUSH,PUSH_NUM,0x3,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_NUM,5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH,PUSH_NUM,-74,
		
		VM_JMP,Jump_From_EIP,
		VM_POP,POP_DEL,

		//////////////////////FUNC_CHECK_1//////////////////////
	
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_1,
		VM_FAKE_CALL,
		VM_POP,POP_DEL,
		
		/////////////�Ƚ�
		VM_PUSH, PUSH_NUM, (DWORD)Cmp_check_1,
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_NUM,0x0,
		VM_POP,POP_EAX,

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_XOR,
		VM_PUSH,PUSH_NUM,0x0,
		VM_CMP,
		VM_POP,POP_DEL,
		+
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,0x0,
		VM_JMP,Jump_From_OEP,
		VM_PUSH,PUSH_NUM,0x0,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_NUM,13,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,0x1,
		VM_PUSH,PUSH_EAX,
		VM_ADD,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_NUM,-50,
		VM_JMP,Jump_From_EIP,

		/////////////////////fun_check_2////////////////////////
		//////һ������
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_NUM,0xFDB97531,
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_2,
		VM_FAKE_CALL,
		VM_POP,POP_DEL,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_EAX,
		////////////////////ѭ��λ��//////
		VM_PUSH,PUSH_NUM,0xE0000000,
		VM_AND,
		VM_PUSH,PUSH_NUM,29,
		VM_SHR,
		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,3,
		VM_SHL,
		VM_OR,

		//////////////////2������/////
		VM_PUSH, PUSH_NUM, 0xFDB97531,
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_2,
		VM_FAKE_CALL,
		VM_POP, POP_DEL,
		VM_POP, POP_EAX,
		VM_PUSH, PUSH_EAX,
		
		//////////һ��ѡ��
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_1,
		VM_FAKE_CALL,
		VM_POP,POP_DEL,
		
		/////////���ձȽ�
		VM_PUSH, PUSH_NUM, (DWORD)Cmp_check_2,
		VM_POP, POP_EBX,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_POP, POP_EAX,

		VM_PUSH, PUSH_EAX,
		VM_PUSH, PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_XOR,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_CMP,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 13,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x1,
		VM_PUSH, PUSH_EAX,
		VM_ADD,
		VM_POP, POP_EAX,
		VM_PUSH, PUSH_NUM, -50,
		VM_JMP, Jump_From_EIP,
		VM_POP,POP_DEL,

		///
		////////////////////////FUN_CHECK_3,HARD////////////////////////////
		/////
		//1������
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_3X1,
		VM_FAKE_CALL,
		VM_POP,POP_DEL,
		//����ָ��//
		VM_PUSH,0x1000,
		VM_POP,0x1000,
		//end//
		//1��ѭ����λ
		VM_PUSH, PUSH_NUM, (DWORD)FUNC_CHECK_3X2,
		VM_FAKE_CALL,
		VM_POP,POP_DEL,
		//1��ѡ��
		VM_POP,POP_EAX,

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x1F,
		VM_AND,
		VM_PUSH,PUSH_NUM,0x30,
		VM_ADD,
		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_NUM,0x5,
		VM_SHR,
		VM_PUSH,PUSH_NUM,0x0,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,-34,
		VM_JMP,Jump_From_EIP,
		/////////�Խ���ѭ���Ƚϴ���//////
		
	
		VM_PUSH, PUSH_NUM, (DWORD)CALL_END_4,
		VM_FAKE_CALL,
		VM_POP,POP_DEL,
		///////////////////���һ�����Ƚϣ������ס�
		VM_PUSH,PUSH_NUM,12,
		VM_ADD,
		VM_POP,POP_EAX,
		VM_PUSH,PUSH_NUM,0,
		VM_POP,POP_EBX,//EBX = i,

		VM_PUSH,PUSH_EAX,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,
		VM_PUSH,PUSH_NUM,0x0,
		VM_CMP,
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_NUM,17,//1
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,0x22,
		VM_XOR,
		VM_PUSH,PUSH_NUM,0x1,
		VM_PUSH,PUSH_EBX,
		VM_ADD,
		VM_POP,POP_EBX,
		VM_PUSH,PUSH_NUM,-35,//1
		VM_JMP,Jump_From_EIP,
		VM_POP,POP_DEL,
		VM_POP,POP_DEL,
		//////
		VM_PUSH,PUSH_NUM,0x1b,//@1
		VM_CMP,
		VM_POP,POP_DEL,
		VM_POP,POP_DEL,
		VM_PUSH,PUSH_NUM,0x5,
		VM_JZ,Jump_From_EIP,
		VM_PUSH,PUSH_NUM,0x0,
		VM_JMP,Jump_From_OEP,
		/////
		VM_PUSH, PUSH_NUM, 0x1A,//@2
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,
		/////
		VM_PUSH, PUSH_NUM, 0x16,//@3
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,
		///
		VM_PUSH, PUSH_NUM, 0x11,//@4
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,
		///
		VM_PUSH, PUSH_NUM, 0x10,//@5
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,
		////
		VM_PUSH, PUSH_NUM, 0x13,//@6
		VM_CMP,
		VM_POP, POP_DEL,
		VM_POP, POP_DEL,
		VM_PUSH, PUSH_NUM, 0x5,
		VM_JZ, Jump_From_EIP,
		VM_PUSH, PUSH_NUM, 0x0,
		VM_JMP, Jump_From_OEP,

		VM_EXIT_SUCCESS,
	};
	
	VM_Function Fun1(64);
	Fun1.StartVM(CODE+2);
	/*printf("VM_2:%x\n", (int*)*(int*)(&Fun1));
	
	if (!strcmp(stringIn, "745230"))
	{
		printf("YOU GOT IT\n");
	}
	else
	{
		printf("SORRY FAIL\n");
	}*/
#ifdef _DEBUG
	printf("%s\n", stringIn);
	for (int i = 0; i < strlen(stringIn); i++)
	{
		printf("%3d  ( %3x ) ( %3c )\n", i, stringIn[i], stringIn[i]);
	}
#endif
	printf("====================================\n");
	printf("============YOU GOT IT!=============\n");
	printf("====================================\n");
	return 0;
}