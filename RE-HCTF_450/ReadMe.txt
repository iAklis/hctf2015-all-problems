/*��������������������������������������������������������������������������������*/
//��Ŀ���������������˷���û��
//��������:VS2013
/*��������������������������������������������������������������������������������*/
/////////////////////////////////////////////////////////////////////

˵����Ǹ����������û��ô��̬�ģ������Լ������ʱ�򲻶����µ��뷨����������������Գ���6���汾�����������������ǧ�������������ڼ���Сʱ���������

////////////////////////////////////////////////////////////////////
��飺
�߷�������Ŀ��ԭ�������û��ô�ѵģ�����Խ��Խ���Ծ��������Լ����ɡ�
���˼·��Դ��BCTF��RE300�뺣Ѱ�٣��Լ�ά��һ����ջ�����������һ���Լ����ֽ������ָ�
�ο����ϣ������������������ܲ��֡�
////////////////////////////////////////////////////////////////////
�ļ���
C_easy_VMP,ʹ��c���Ա�д�����demon
C_easy_VMP_2,����c++�ˣ���ԭ����switchcase��Ϊһ����ת��
C_easy_VMP_3,�Ż����������������ˣ�ʹ�õ�����ʽ��
C_easy_VMP_4,����˸����ָ����������İ����ɰ���һ���޸ĵ�ʱ��С�ı������ˣ��ͱ��ˡ�
C_easy_VMP_5,ָ����ɣ��ο�x86��
��ɰ棺������Ŀ�ˣ��������callָ����ֻ�������
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


�ֽ���ָ�
��ת��
	ControlTable[VM_X00_START] = 0x00;			
	ControlTable[VM_PUSH]	   = &VM_Function::CODE_PUSH;

	ControlTable[VM_POP]	  = &VM_Function::CODE_POP;
	ControlTable[VM_ADD]	  = &VM_Function::CODE_ADD;
	ControlTable[VM_SUB]	  = &VM_Function::CODE_SUB;
	ControlTable[VM_XOR]	  = &VM_Function::CODE_XOR;
	ControlTable[VM_JMP]	  = &VM_Function::CODE_JMP;
	ControlTable[VM_JZ]		  = &VM_Function::CODE_JZ;
	ControlTable[VM_CMP]	  = &VM_Function::CODE_CMP;

	ControlTable[VM_SHR] = &VM_Function::CODE_SHR;
	ControlTable[VM_SHL] = &VM_Function::CODE_SHL;
	ControlTable[VM_AND] = &VM_Function::CODE_AND;
	ControlTable[VM_OR] = &VM_Function::CODE_OR;

	ControlTable[VM_STRLEN_CALL]  = &VM_Function::CODE_STRLEN_CALL;
	ControlTable[VM_FAKE_CALL] = &VM_Function::CODE_FAKE_CALL;
	ControlTable[VM_EXIT_SUCCESS] = &VM_Function::CODE_EXIT_SUCCESS;
	ControlTable[VM_EXIT_FAIL] = &VM_Function::CODE_EXIT_FAIL;

#ifdef _DEBUG
	ControlTable[VM_DEBUG_BREAK] = &VM_Function::CODE_DBG_BREAK;
#endif



[VM_X00_START] û�õı�־����ʾһ���������ʼ��

[VM_PUSH]	   
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
��ջ��PUSHһ�����ݣ�������Ϊ2Ԫ��3Ԫ��ʾ����
1.VM_PUSH, PUSH_MEM | PUSH_MEM_BYTE,��ջһ����ַ��ȡBYTE��ַ����ջ��
2.VM_PUSH,PUSH_NUM,0x0,��ջ0

[VM_POP]	
enum Code_Pop_Parameter
{
	POP_EAX = 0x10,
	POP_EBX = 0x20,
	POP_MEM = 0x30,
	POP_DEL = 0x40,
	POP_MEM_BYTE = 0x1,
	POP_MEM_WORD = 0x2,
	POP_MEM_DWORD= 0x4
};ͬ�ϡ�

[VM_ADD]	
��ջ2�����ݣ����֮����ջ

	  
[VM_SUB]	  
ͬ��


[VM_XOR]	  
ͬ��

[VM_JMP]	  
��Ԫ����
��ջһ����ת����
enum Code_JumpFun
{
	Jump_From_EIP = 0x10,	//��һ����ַΪ��ת����ַ
	Jump_From_OEP = 0X20	//��ڵ�Ϊ��ת����ַ
};
���磺
VM_PUSH,PUSH_NUM,0x0,
VM_JMP,Jump_From_OEP,
��ʾ������ͷ��

[VM_JZ]		  
ͬ�ϣ�����Ҫ�ж�Z��־λ�Ƿ���ת��


[VM_CMP]	  
�Ƚ�ջ����2��ֵ������Z��S flag��ͬx86


[VM_SHR] 
��Ԫ��������һ������λ�����ٳ�һ����ֵ�����ƺ�Ż�ջ�С�


[VM_SHL] 
ͬ�ϡ�

[VM_AND] 
ͬXOR

[VM_OR] 
ͬXOR

[VM_STRLEN_CALL]  
��װstrlen

[VM_FAKE_CALL] 
����һ���µ������ֽ��룬��ԭ�ֽ���ʹ�ò�ͬ�ļĴ�������ͬ��ջ��


[VM_EXIT_SUCCESS] 
���سɹ���you got it��


[VM_EXIT_FAIL] 
����ʧ�ܣ�Try again��


[VM_DEBUG_BREAK] 
��Debugʱ����debug�ֽ����ָ�����ʾ��ջ��Ĵ�����


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

������ʽ��
1.����ָ�
���磺
		//����ָ��//
		VM_PUSH,0x1000,
		VM_POP,0x1000,
���ᱻ�ֽ��������ִ�л���ִ�к�û���κ������ָ�

2.�ֽ����Խ���
���磺
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

��δ���ȫ�������0x28��������ʱ�Խ���Ȼ�������С�


3.����
����������д�ˡ�

4.ѭ��λ��
���鷳������д�ˡ�

/////////////////////////////////////////////////////////////////////////////////
Դ�붼�������ˡ����������Լ���
/////////////
