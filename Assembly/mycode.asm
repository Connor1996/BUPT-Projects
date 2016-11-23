STUDENT STRUC
    xNAME       DB 20 DUP('$')     ;���� 
    xCLASS      DB 20 DUP('$')     ;�༶
    xID         DB 20 DUP('$')     ;ѧ��
    xGRADE      DB 20 DUP('$')     ;�ɼ�
STUDENT ENDS

ENTER MACRO
    MOV     AH, 2
    MOV     DL, 0DH
    INT     21H
    MOV     DL, 0AH
    INT     21H
ENDM

ADDITEM MACRO ITEM
    LEA     AX, STR_&ITEM
    PUSH    AX
    CALL    PRINTSTR                              ;�����ʾ�ַ���       
    LEA     AX, STUDENTS[BX].x&ITEM
    PUSH    AX
    CALL    GETSTRING                          ;���������ַ���
ENDM

DATA SEGMENT
    STUDENTS    STUDENT 100 DUP(<>) 
    PTR_STUDENTS DW     100 DUP(?)
    COUNT       DB      0
    STRING      DB      20               ;�������ĵ�һ���ֽ�ָ�����ɵ�����ַ����������û�����
                DB      ?                ;�ڶ����ֽڴ��ʵ�ʵ�����ַ���������ϵͳ�������
                DB      20 DUP(?)        ;�ӵ������ֽڿ�ʼ��ŴӼ��̽��ܵ��ַ���ֱ��ENTER������
    AMOUNT      DW      0
        
    STR_COMMAND DB      'Commad list: ', 0DH, 0AH 
                DB      '1. Enter students grade', 0DH, 0AH
                DB      '2. List student number in sort', 0DH, 0AH
                DB      '3. List student grade in sort', 0DH, 0AH
                DB      '4. Count average grade', 0DH, 0AH
                DB      '5. Count nunmber of student in every score section', 0DH, 0AH
                DB      '0. Exit', 0DH, 0AH, '$'   
    STR_INPUT   DB      'Please input the command number: ', '$'
    STR_ERROR   DB      'Illegal command number', 0DH, 0AH, '$' 
    STR_AVERAGE DB      'Average grade is: ', '$'
    
    COUNT_FAIL      DB     0
    COUNT_60TO70    DB     0
    COUNT_70TO80    DB     0
    COUNT_80TO90    DB     0
    COUNT_90TO100   DB     0 
    
    STR_FAIL    DB      '0~59:   ', '$'
    STR_60TO70  DB      '60~69:  ', '$'
    STR_70TO80  DB      '70~79:  ', '$'
    STR_80TO90  DB      '80~89:  ', '$'
    STR_90TO100 DB      '90~100: ', '$'
    
    STR_NAME    DB      'student name: $'
    STR_CLASS   DB      'student class: $'
    STR_ID      DB      'student number: $'
    STR_GRADE   DB      'student grade: $'
          
    TABLE       DW      CASE0, CASE1, CASE2, CASE3, CASE4, CASE5, DEFAULT
   
DATA ENDS

STACK SEGMENT STACK
    DW 100H DUP(?)
STACK ENDS

CODE SEGMENT 
    ASSUME CS:CODE, DS:DATA, SS:STACK
START:
    MOV     AX, DATA
    MOV     DS, AX
    
    ;��������б�
    MOV     AX, OFFSET STR_COMMAND
    PUSH    AX
    CALL    PRINTSTR
    
    ;ѭ����ȡ����
INPUT_LOOP:
    MOV     AX, OFFSET STR_INPUT  
    PUSH    AX
    CALL    PRINTSTR
    
    MOV     AH, 1       ;����ַ�����AL��
    INT     21H
    XOR     BX, BX      ;����BX������swtich��ֵ
    MOV     BL, AL  
    
    ;����             
    ENTER
    
    SUB     BX, '0'     
    CMP     BX, 5       ;��P��������ַ��Ƿ���5����
    JBE     CASE0TO5                                                                                                                  
    MOV     BX, 6       ;����������ת��default��֧
       
CASE0TO5:
    SHL     BX, 1       ;��ת���������ͣ��±��2
    JMP     TABLE[BX]
    
CASE0:
    JMP     EXIT
        
CASE1:
    CALL    ADDSTUDENT
    MOV     AH, 2
    MOV     DL, COUNT
    ADD     DL, '0'
    INT     21H
    ENTER
    JMP     CASEEND  
    
CASE2:
    CALL    LISTBYNUMBER
    JMP     CASEEND
    
CASE3:
    CALL    LISTBYGRADE
    JMP     CASEEND 
    
CASE4:         
    LEA     AX, STR_AVERAGE
    PUSH    AX
    CALL    PRINTSTR
    
    MOV     AX, AMOUNT  
    XOR     CX, CX
    MOV     CL, COUNT
    XOR     DX, DX
    DIV     CX             ;��ƽ���ɼ�
    PUSH    AX
    CALL    PRINTDECIMAL
    ENTER
    JMP     CASEEND    
    
CASE5:
    LEA     AX, STR_FAIL
    PUSH    AX
    CALL    PRINTSTR     
    XOR     AX, AX
    MOV     AL, COUNT_FAIL
    PUSH    AX
    CALL    PRINTNUM
    ENTER
    LEA     AX, STR_60TO70
    PUSH    AX
    CALL    PRINTSTR 
    XOR     AX, AX
    MOV     AL, COUNT_60TO70
    PUSH    AX
    CALL    PRINTNUM   
    ENTER
    LEA     AX, STR_70TO80
    PUSH    AX
    CALL    PRINTSTR     
    XOR     AX, AX
    MOV     AL, COUNT_70TO80
    PUSH    AX
    CALL    PRINTNUM     
    ENTER
    LEA     AX, STR_80TO90
    PUSH    AX
    CALL    PRINTSTR 
    XOR     AX, AX
    MOV     AL, COUNT_80TO90
    PUSH    AX
    CALL    PRINTNUM
    ENTER
    LEA     AX, STR_90TO100
    PUSH    AX
    CALL    PRINTSTR  
    XOR     AX, AX
    MOV     AL, COUNT_90TO100
    PUSH    AX
    CALL    PRINTNUM
    ENTER
    JMP     CASEEND      
    
DEFAULT:
    LEA     AX, STR_ERROR
    PUSH    AX  
    CALL    PRINTSTR    
    
CASEEND:
    JMP     INPUT_LOOP
      
EXIT:
    MOV     AX, 4C00H
    INT     21H

ADDSTUDENT PROC NEAR
    PUSH    AX
    PUSH    BX
    PUSH    DX
    
    MOV     AL, COUNT                          ;ѧ����Ϣ��Ŀ����         
    MOV     DL, 80
    MUL     DL                                 ;(AL) * (DL) -> (AX)
    MOV     BX, AX      
    
    ADDITEM NAME           
    ENTER
    ADDITEM CLASS  
    ENTER
    ADDITEM ID
    ENTER
    ADDITEM GRADE        
    ENTER
    
    INC     COUNT
    LEA     AX, STUDENTS[BX].xGRADE
    PUSH    AX
    CALL    ADDAMOUNT  
    
    POP     DX
    POP     BX
    POP     AX
    RET
ADDSTUDENT ENDP        

;����Ϊ��ʾ���ֵ��ַ����׵�ַ 
;���ַ���ת�������ּӵ�AMOUNT��
;��ʮ���Ƶ�˼·���㣬ÿ�γ�10�ڼ���ĩβ��
;����һλ��С�����൱�ڽ����10�������������ʱ����Ҫ��10��ȡ������
ADDAMOUNT PROC NEAR
    PUSH    BP
    MOV     BP, SP
    PUSH    SI
    PUSH    AX
    PUSH    BX
    PUSH    CX
    PUSH    DX
    
    MOV     CX, 10
    MOV     SI, [BP + 4] 
    XOR     DX, DX 
    XOR     AX, AX
LL1:                     
    CMP     BYTE PTR[SI], '.'   ;�ж��Ƿ����С����
    JE      LAST
    CMP     BYTE PTR[SI], '$'   ;�ж��Ƿ��β����ʱ��û�ж���С���㣬������Ҫ��һλС����λ��
    JE      ADDZERO
    MUL     CX                   ;��10�����Կ���ʮ���������һλ
    ADD     AL, BYTE PTR[SI] 
    ADC     AH, 0
    SUB     AX, '0'
    INC     SI
    JMP     LL1  
LAST:                            ;����С�����ֻ�����ٶ�һλ����ȷС���㵽1λ��
    INC     SI
    CMP     BYTE PTR[SI], '$'    ;���ж��Ƿ�Ϊ������
    JE      ADDZERO
    MUL     CX
    ADD     AL, BYTE PTR[SI]
    ADC     AH, 0
    SUB     AX, '0'
    JMP     REC                  
    
ADDZERO:                            
    MOV     BYTE PTR[SI], '.'
    MOV     BYTE PTR[SI + 1], '0'
    MOV     BYTE PTR[SI + 2], '$'
    MUL     CL                  ;����Ϊ��������Ϊ�˷�����㣬���λ���һ��С��λ
    
REC:   
    CMP     AX, 600
    JNB     R60_70 
    INC     COUNT_FAIL
    JMP     OVER
R60_70:
    CMP     AX, 700
    JNB     R70_80 
    INC     COUNT_60TO70
    JMP     OVER
R70_80:
    CMP     AX, 800
    JNB     R80_90 
    INC     COUNT_70TO80
    JMP     OVER  
R80_90:
    CMP     AX, 900
    JNB     R90_100 
    INC     COUNT_80TO90
    JMP     OVER  
R90_100:
    CMP     AX, 1000
    JNB     OVER
    INC     COUNT_90TO100
  
    
OVER:         
    LEA     DI, AMOUNT
    ADD     [DI], AX
        
    POP     DX
    POP     CX
    POP     BX
    POP     AX
    POP     SI
    POP     BP
    RET     2
ADDAMOUNT ENDP

;�������л�ȡ�ַ���
;����ΪĿ���ַ�������ƫ�Ƶ�ַ
GETSTRING PROC NEAR
    PUSH    BP
    MOV     BP, SP
    PUSH    DX  
    PUSH    AX 
    PUSH    CX
    PUSH    SI
    PUSH    DI
    
    LEA     DX, STRING            ;STRINGΪ��ǰ���úõĻ�����
    MOV     AH, 0AH               ;0AH�ж��ṩ��ȡ�ַ������������Ĺ���
    INT     21H  
    
    ;���ƻ��������ݵ���Ӧ���ַ�����
    MOV     AX, DS
    MOV     ES, AX                ;(DS)->(ES)
    XOR     CX, CX
    MOV     CL, STRING[1]         ;�ַ������ȷ���CX����ΪΪ8λ���Խ�����չ
    MOV     SI, OFFSET STRING[2]  ;Դ�ַ�������������
    MOV     DI, [BP + 4]          ;Ŀ���ַ������������ĵ�һ������
    CLD
    REP     MOVSB                 ;ѭ�������ַ���
    MOV     BYTE PTR[DI], '$'
    
    POP     DI
    POP     SI
    POP     CX       
    POP     AX
    POP     DX  
    POP     BP
    RET     2
GETSTRING ENDP

PRINTDECIMAL PROC NEAR
    PUSH    BP
    MOV     BP, SP
    PUSH    AX
    PUSH    BX    
    PUSH    DX
    
    MOV     AX, [BP + 4] 
    XOR     DX, DX
    MOV     BX, 10   
    MOV     CX, 0
LLD:      
    INC     CX
    DIV     BX     
    ADD     DL, '0'    
    PUSH    DX          ;����ջ�У���Ҫ�������   
    CMP     CX, 1
    JNE     NOPOINT 
    MOV     DX, '.'     ;����С���㡯 
    PUSH    DX
NOPOINT:
    XOR     DX, DX
    CMP     AX, 0  
    JNE     LLD

    INC     CX          ;��Ϊ����˸�С���㣬��������ĸ�����һ
OUTPUTD:
    POP     DX          ;��ջ�е����������������
    MOV     AH, 2
    INT     21H  
    LOOP    OUTPUTD
    
    POP     DX
    POP     BX
    POP     AX
    POP     BP
    RET     2
PRINTDECIMAL ENDP

PRINTNUM PROC NEAR
    PUSH    BP
    MOV     BP, SP
    PUSH    AX
    PUSH    BX    
    PUSH    DX
    
    MOV     AX, [BP + 4] 
    XOR     DX, DX
    MOV     BX, 10   
    MOV     CX, 0
LLN:      
    INC     CX
    DIV     BX     
    ADD     DL, '0'    
    PUSH    DX          ;����ջ�У���Ҫ�������   
    CMP     CX, 1
    XOR     DX, DX
    CMP     AX, 0  
    JNE     LLN

OUTPUTN:
    POP     DX          ;��ջ�е����������������
    MOV     AH, 2
    INT     21H  
    LOOP    OUTPUTN
    
    POP     DX
    POP     BX
    POP     AX
    POP     BP
    RET     2
PRINTNUM ENDP


PRINTSTR PROC NEAR
    PUSH    BP
    MOV     BP, SP    
    PUSH    AX
    PUSH    BX    
    PUSH    DX
    PUSH    CX
    
    MOV     AH, 9
    MOV     DX, [BP + 4]        ;��һ������������ַ������׵�ַ
    INT     21H
    
    POP     CX
    POP     DX 
    POP     BX
    POP     AX
    POP     BP
    RET     2
PRINTSTR ENDP
        
LISTBYNUMBER PROC NEAR
    PUSH    AX
    PUSH    BX
    PUSH    CX
             
    XOR     CX, CX
    MOV     CL, COUNT 
    DEC     CL     
    CMP     CL, 0
    JE      OUTPUT
LOOP1:
    MOV     DI, CX             ;�������ѭ���������ⱻ�ڲ�ѭ���ƻ�
    MOV     BX, 0              ;�ڲ�ѭ���ĳ�ʼ״̬����ͷ��ʼ
    
LOOP2:
    LEA     AX, STUDENTS[BX].xID
    PUSH    AX
    LEA     AX, STUDENTS[BX + 80].xID
    PUSH    AX
    CALL    CMPSTR
    JA      CONT1    
    
    MOV     SI, 0
LOOP3:                                              
    MOV     AX, WORD PTR STUDENTS[BX + SI]
    XCHG    AX, WORD PTR STUDENTS[BX + SI + 80]   ;���������ṹ��
    MOV     WORD PTR STUDENTS[BX + SI], AX  
    ADD     SI, 2
    CMP     SI, 80
    JNE     LOOP3
    
CONT1:
    ADD     BX, 80
    LOOP    LOOP2
    MOV     CX, DI
    LOOP    LOOP1
    
OUTPUT:
    XOR     CX, CX
    MOV     CL, COUNT
    MOV     BX, 0
    
OUTPUT_LOOP: 
    LEA     AX, STR_NAME
    PUSH    AX
    CALL    PRINTSTR    
    LEA     AX, STUDENTS[BX].xNAME
    PUSH    AX
    CALL    PRINTSTR
    ENTER    
    
    LEA     AX, STR_CLASS
    PUSH    AX
    CALL    PRINTSTR 
    LEA     AX, STUDENTS[BX].xCLASS
    PUSH    AX
    CALL    PRINTSTR
    ENTER           
    
    LEA     AX, STR_ID
    PUSH    AX
    CALL    PRINTSTR
    LEA     AX, STUDENTS[BX].xID
    PUSH    AX
    CALL    PRINTSTR
    ENTER           
    
    LEA     AX, STR_GRADE
    PUSH    AX
    CALL    PRINTSTR
    LEA     AX, STUDENTS[BX].xGRADE
    PUSH    AX
    CALL    PRINTSTR 
    ENTER       
    ADD     BX, 80
    
    MOV     AH, 8
    INT     21H
    LOOP    OUTPUT_LOOP
    
    POP     CX
    POP     BX
    POP     AX 
    RET
LISTBYNUMBER ENDP

LISTBYGRADE PROC NEAR
  PUSH    AX
    PUSH    BX
    PUSH    CX
             
    XOR     CX, CX
    MOV     CL, COUNT 
    DEC     CL  
    CMP     CL, 0
    JE      GOUTPUT
GLOOP1:
    MOV     DI, CX             ;�������ѭ���������ⱻ�ڲ�ѭ���ƻ�
    MOV     BX, 0              ;�ڲ�ѭ���ĳ�ʼ״̬����ͷ��ʼ
    
GLOOP2:
    LEA     AX, STUDENTS[BX].xGRADE
    PUSH    AX
    LEA     AX, STUDENTS[BX + 80].xGRADE
    PUSH    AX
    CALL    CMPSTR
    JA      GCONT1    
    
    MOV     SI, 0
GLOOP3:                                              
    MOV     AX, WORD PTR STUDENTS[BX + SI]
    XCHG    AX, WORD PTR STUDENTS[BX + SI + 80]   ;���������ṹ��
    MOV     WORD PTR STUDENTS[BX + SI], AX  
    ADD     SI, 2
    CMP     SI, 80
    JNE     GLOOP3
    
GCONT1:
    ADD     BX, 80
    LOOP    GLOOP2
    MOV     CX, DI
    LOOP    GLOOP1
    
GOUTPUT:
    XOR     CX, CX
    MOV     CL, COUNT
    MOV     BX, 0
    
GOUTPUT_LOOP: 
    LEA     AX, STR_NAME
    PUSH    AX
    CALL    PRINTSTR    
    LEA     AX, STUDENTS[BX].xNAME
    PUSH    AX
    CALL    PRINTSTR
    ENTER    
    
    LEA     AX, STR_CLASS
    PUSH    AX
    CALL    PRINTSTR 
    LEA     AX, STUDENTS[BX].xCLASS
    PUSH    AX
    CALL    PRINTSTR
    ENTER           
    
    LEA     AX, STR_ID
    PUSH    AX
    CALL    PRINTSTR
    LEA     AX, STUDENTS[BX].xID
    PUSH    AX
    CALL    PRINTSTR
    ENTER           
    
    LEA     AX, STR_GRADE
    PUSH    AX
    CALL    PRINTSTR
    LEA     AX, STUDENTS[BX].xGRADE
    PUSH    AX
    CALL    PRINTSTR 
    ENTER       
    ADD     BX, 80
    
    MOV     AH, 8
    INT     21H
    LOOP    GOUTPUT_LOOP
    
    POP     CX
    POP     BX
    POP     AX 
    RET    
LISTBYGRADE ENDP

CMPSTR PROC NEAR
    PUSH    BP
    MOV     BP, SP 
    PUSH    AX
    PUSH    BX
    PUSH    CX
    PUSH    DX
    PUSH    DI
    PUSH    SI
    
    XOR     CX, CX
    MOV     SI, [BP + 4]
    MOV     DI, [BP + 6]
    DEC     SI
    DEC     DI
L1:  
    INC     CH 
    INC     SI
    CMP     BYTE PTR[SI], '$'
    JNE     L1
L2:
    INC     CL
    INC     DI
    CMP     BYTE PTR[DI], '$'
    JNE     L2
    
    CMP     CH, CL
    JNE     STOP
    
    MOV     SI, [BP + 4]
    MOV     DI, [BP + 6]
    DEC     SI
    DEC     DI
L3:         
    INC     SI
    INC     DI
    MOV     DH, [SI]
    MOV     DL, [DI] 
    CMP     DH, '$'
    JE      STOP
    CMP     DH, DL
    JE      L3
STOP:    
    
    POP     SI
    POP     DI
    POP     DX
    POP     CX
    POP     BX
    POP     AX
    POP     BP
    RET     4    
CMPSTR ENDP

CODE ENDS
    END START
                                                    