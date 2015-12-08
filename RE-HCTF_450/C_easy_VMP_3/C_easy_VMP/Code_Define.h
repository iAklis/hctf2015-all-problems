#include <Windows.h>
#define General_VM 0x10
enum myVm
{
	VM_X00_START = 0,

	VM_PUSH, //核心代码
	VM_POP,

	VM_ADD,	//计算代码
	VM_SUB,
	VM_XOR,
	VM_CMP,

	VM_JMP, //跳转代码
	VM_JZ,
	VM_EXIT,
	

	VM_STRLEN_CALL,//CALL代码？？
	VM_FAKE_CALL

};
enum Code_Push_Parameter
{
	PUSH_EAX = 0x10,
	PUSH_EBX = 0x20,
	PUSH_MEM = 0x30,
	PUSH_NUM = 0x40,
	PUSH_MEM_BYTE = 0x1,
	PUSH_MEM_WORD = 0x2,
	PUSH_MEM_DWORD= 0x4

};
enum Code_Pop_Parameter
{
	POP_EAX = 0x10,
	POP_EBX = 0x20,
	POP_MEM = 0x30,
	POP_DEL = 0x40,
	POP_MEM_BYTE = 0x1,
	POP_MEM_WORD = 0x2,
	POP_MEM_DWORD= 0x4
};
enum Code_JumpFun
{
	Jump_From_EIP = 0x10,
	Jump_From_OEP = 0X20
};