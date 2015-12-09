#include <map>
#include <cstdio>
#include "Stack.h"
#include "Code_Define.h"
class VM_Function:public VM_STACK
{
	typedef struct _VMDATA
	{
		//DWORD ESP;
		DWORD EAX;
		DWORD EBX;
		//DWORD ECX;
		//DWORD EDX;
		//DWORD ESI;
		//DWORD EDI;
		//DWORD EIP;
		DWORD OEP;
		PDWORD CODE;
		PDWORD DATA;
		//PBYTE PARAM;
		//PBYTE PARAM1;
		BOOL  SFLAG;		//���ű�־
		BOOL  ZFLAG;		//���־

	} VMDATA, *PVMDATA;

	typedef void(VM_Function::*ProcessFuncPtr)(PVMDATA);

	//typedef void(VM_Function::*ProcessTest)();
	//ProcessTest calltest;

	std::map<int, ProcessFuncPtr> ControlTable;
	ProcessFuncPtr callname;
	
public:
	VM_Function(int datax) ;
	BOOL StartVM(PDWORD vmCode);

private:
	virtual void CODE_X00_START();
	void CODE_PUSH(PVMDATA vm_data);
	void CODE_POP(PVMDATA vm_data);

	
	void CODE_ADD(PVMDATA vm_data);
	void CODE_SUB(PVMDATA vm_data);
	void CODE_XOR(PVMDATA vm_data);
	void CODE_JMP(PVMDATA vm_data);
	void CODE_JZ(PVMDATA vm_data);
	void CODE_CMP(PVMDATA vm_data);

	//CALLָ��
	void CODE_STRLEN_CALL(PVMDATA vm_data);
	void CODE_FAKE_CALL(PVMDATA vm_data);
	//���⻷���仯ָ��
	void CODE_EXIT(PVMDATA vm_data);

	//�Ӻ�������ֵ
	DWORD VM_RET;
};