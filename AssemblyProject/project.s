;-----------------------------------------
; Student Name : Kim Hyeon Ji
; Student ID : 2013722058	
; Date : 2015.11.22
;-----------------------------------------
; Register Description:
; R0  :	Random data's first address
; R1  : 	Search data's first address
; R2  : 	
; R3  :	
; R4  : 
; R5  : 
; R6  :
; R7  : 
; R8  : 
; R9  :
; R10 : Result address
; R11 : Result address copy
; R12 :  
;-----------------------------------------

;-----------------------------------------
;CODE AREA
;-----------------------------------------
	AREA	ARMex, CODE, READWRITE		
		ENTRY
		
Start
	LDR r0, =Random_data
	LDR r1, = Search_data
	LDR r10, Result_address
	MOV r11, r10	;60000000¹øÁö
	LDR sp, =0x1000

;-----------------------------------------
; Register Description:
; R0  :	temporary address
; R1  : 	Search data's first address
; R2  :	original string (including #) 	
; R3  :	original string (including #)
; R4  : 	original string (including #)
; R5  : 	original string (including #)
; R6  :	original string (including #)
; R7  : 
; R8  : 
; R9  :
; R10 : Result address after storing
; R11 : Result address copy
; R12 :  
;-----------------------------------------

;deleting "#" and store in 0x50000000
Load
	LDMFD r0!, {r2-r6}		;load strings into r2- r6

	;delete #
	MOV r3, r3, LSR #8		;r3 : delete last 2 integer
	MOV r7, r4, LSL #24		;r7 : r4's last 2 integer
	ADD r3, r3, r7				; r3 = r3 + r7
	
	MOV r4, r4, LSR #16		;r4 :delete last 4 integers
	MOV r7, r5, LSL #16		;r7 : r5's last 2 integers
	ADD r4, r4, r7				; r4 = r4 + r7
	
	MOV r5, r5, LSR #24		;r5 : delete last 6 integers
	MOV r7, r6, LSL #8		;r7 : r6's last 6 integers
	ADD r5, r5, r7				;r5 =r5+r7
	
	STMEA r10!, {r2-r5}		;store new string into r10
	
	;if address is same with Search_data
	CMP r0, r1				
	STMEAGE sp!, {r11}	;start point push in stack
	STMEAGE sp!, {r10}	;end point push in stack
	BEQ Setting					;go Setting
	
	B Load	;Loop
	
;-----------------------------------------
; Register Description:
; R0  : sorting start point
; R1  : sorting end point
; R2  : pivot's address
; R3  : i
; R4  : j
; R5  : start value
; R6  : end value
; R7  : pivot's value
; R8  : 
; R9  :
; R10 : pivot's shifted value
; R11 :
; R12 :   0x1000
;-----------------------------------------
Setting	
	
	;Search checker2
	CMP sp, #0x2000		
	LDRGE r4, =0x2000	;if sp >=2000, r4 = 0x2000-4, sp = 0x1000, r0=0 , go Search
	SUBGE r4, r4, #4
	LDRGE sp, =0x1000
	MOVGE r0, #0
	BGE Search
	
	LDMEA sp!, {R1}; end point pop in stack
	LDMEA sp!, {R0};	 start point pop in stack
	
	CMP r0, r1		;if start and end is same, pop again
	BEQ Setting
	
 	CMP r0,r1			;if r0>r1, change r0 and r1
	LDMEAGT sp!, {r1}
	LDMEAGT sp!, {r0}
	MOVGT r3, r1
	MOVGT r1, r0
	MOVGT r0,r3
	
	;Search checker1
	MOV r12, #0x1000	;r12 = 0x1000 
	CMP sp, r12				;sp <=0x1000 -> delete Search data
	LDRLT r0, =Search_data
	ADDLT r1, r0, #0x104
	MOVLT r10, #0x2000
	LDRLT sp, =0x2500
	BLT Load
	
 	;pivot setting
	ADD r2, r0, r1			;pivot = (start+end)/2
	MOV r2, r2, LSR#1
	MOV r3, r2, LSL#30	;if this is 2, pivot-2.
	MOV r3, r3, LSR#30
	CMP r3, #2
	SUBEQ r2, r2, #2
	
	;pivot swap
	LDR r5, [r0]	; start : r5 in r0, pivot : r7 in r2
	LDR r7, [r2]
	STR r7, [r0]	; swap r7 in r0, r5 in r2
	STR r5, [r2]
	
	;i, j setting
	MOV r3, r0	;first i is start point
	MOV r4, r1	;first j is end point
	
	;shift pivot's value
	MOV r10, r7
	MOV r5, r10, LSL #24	;r4 = r10's last 2 integer
	MOV r10, r10, LSR #8	;delete r10's last 2 integer
	
	MOV r6, r10, LSL #24	;r6 = r10's last 2 integer
	MOV r6, r6, LSR #8		;shift 2 integers
	MOV r10, r10, LSR #8	;delete r10's last 2 integer
	
	ADD r5, r5, r6			;r5 = r5+r6
	
	MOV r6, r10, LSL #24	;r6 = r10's last 2 integer
	MOV r10, r10, LSR #8	;delete r10's last 2 integer
	MOV r6, r6, LSR #16		;shift 4integers
	
	ADD r5, r5, r6	;add
	ADD r10, r10, r5
	
	
	B Compare_i	; go to compare arr[i]
	
;-----------------------------------------
; Register Description:
; R0  : sorting start point
; R1  : sorting end point
; R2  : pivot's address
; R3  : i
; R4  : j
; R5  : start value
; R6  : end value
; R7  : pivot's value
; R8  : arr[i]'s value
; R9  :
; R10 : pivot's shifted value
; R11 : arr[i]'s shifted value
; R12 :   
;-----------------------------------------
Compare_i
	ADD r3, r3, #4	;from the next address
	LDR r8, [r3]		;load into r8
	
	;shift arr[i]
	MOV r11, r8
	MOV r5, r11, LSL #24
	MOV r11, r11, LSR #8
	MOV r6, r11, LSL #24
	MOV r6, r6, LSR #8
	MOV r11, r11, LSR #8
	ADD r5, r5, r6
	
	MOV r6, r11, LSL #24
	MOV r11, r11, LSR #8
	MOV r6, r6, LSR #16	
	ADD r5, r5, r6
	ADD r11, r11, r5

	;piv vs i
	CMP r10, r11		;if pivot <= arr[i]
	BLE Compare_j	;go compare_j
	CMPGT r3, r1		;if pivot > arr[i], r3 vs r1(if address is end?)
	BLE Compare_i	;if address is not same with end, go loop
	BGT Compare_j	;if same or larger, go compare_j
	
;-----------------------------------------
; Register Description:
; R0  : sorting start point
; R1  : sorting end point
; R2  : pivot's address
; R3  : i
; R4  : j
; R5  : start value
; R6  : end value
; R7  : pivot's value
; R8  : arr[i]'s value
; R9  : arr[j]'s value
; R10 : pivot's shifted value
; R11 : arr[i]'s shifted value
; R12 : arr[j]'s shifted value 
;-----------------------------------------
Compare_j
	SUB r4,r4,#4	;from the front address
	LDR r9,[r4]		;load into r9
	
	;shift arr[j]
	MOV r12, r9
	MOV r5, r12, LSL #24
	MOV r12, r12, LSR #8
	MOV r6, r12, LSL #24
	MOV r6, r6, LSR #8
	MOV r12, r12, LSR #8
	ADD r5, r5, r6
	
	MOV r6, r12, LSL #24
	MOV r12, r12, LSR #8
	MOV r6, r6, LSR #16
	ADD r5, r5, r6
	ADD r12, r12, r5

 	;piv vs j
	CMP r10, r12		;piv <arr[j], go loop
	BLT Compare_j
	CMPGE r3, r4		; piv>arr[j] && if r3 vsr4
	STRLE r9, [r3]		;swap arr[i] & arr[j] and go compare_i
	STRLE r8,[r4]
	BLE Compare_i
	STRGT r7, [r4]	;piv's addrerss > j, swap arr[j] and piv
	STRGT r9, [r0]
	ADDGT r11, r4, #4 ;make r11=j+4
	MOVGT r10, r4
	STMEAGT sp!, {r0}	;start address
	STMEAGT sp!, {r10-r11}	;j address, j+4 address
	STMEAGT sp!, {r1}		;end address
	BGT Setting		;go Setting
	
;-----------------------------------------
; Register Description:
; R0  : length of find string
; R1  : 
; R2  : 
; R3  : 
; R4  : Search_data's address
; R5  : Result_address
; R6  : Result_address+2000
; R7  : 
; R8  : search data's value
; R9  : 
; R10 :
; R11 :search data's shifted value
; R12 : 
;-----------------------------------------
Search
	ADD r4, r4, #4	;from the next address
	LDR r8,[r4]		;load into r8
	
	CMP r8, #0x0	;if load data is 0, end Search!
	LDREQ r1, Result_address	
	LDREQ sp,  Result_address1
	MOVEQ r11, #0x23
	LDMFDEQ r1!, {r8-r11}
	BEQ Store
	
	;shift r8
	MOV r11, r8
	MOV r5, r11, LSL #24
	MOV r11, r11, LSR #8
	MOV r6, r11, LSL #24
	MOV r6, r6, LSR #8
	MOV r11, r11, LSR #8
	ADD r5, r5, r6
	
	MOV r6, r11, LSL #24
	MOV r11, r11, LSR #8
	MOV r6, r6, LSR #16
	ADD r5, r5, r6
	ADD r11, r11, r5
	
	LDR r5, Result_address	;the start point
	ADD r6, r5, #2000				;the end point
	STMEA sp!, {r5}				;push in stack {start, end}
	STMEA sp!, {r6}
	
	B Compare_Binary		;go Comparing
	
;-----------------------------------------
; Register Description:
; R0  : length of find string
; R1  : start address
; R2  : end address
; R3  : pivot address
; R4  : Search_data's address
; R5  : Result_address
; R6  : Result_address+2000
; R7  : pivot's value
; R8  : search data's value
; R9  : 
; R10 :pivot's shifted value
; R11 :search data's shifted value
; R12 : 
;-----------------------------------------
Compare_Binary;Binary Search
	LDMEA sp!, {r2}	; pop 2 pointer {Start, end} 
	LDMEA sp!, {r1}
	
	CMP r2,r1			;if start and end is same, go to Search
	BEQ Search
	
	;pivot setting
	ADD r3, r1, r2			;pivot = (start+end)/2
	MOV r3, r3, LSR#1
	MOV r5, r3, LSL#30
	MOV r5, r5, LSR#30
	CMP r5, #2
	SUBEQ r3, r3, #2
	
	;piv shift
	LDR r7, [r3]
	
	MOV r10, r7
	MOV r5, r10, LSL #24
	MOV r10, r10, LSR #8
	MOV r6, r10, LSL #24
	MOV r6, r6, LSR #8
	MOV r10, r10, LSR #8
	ADD r5, r5, r6
	
	MOV r6, r10, LSL #24
	MOV r10, r10, LSR #8
	MOV r6, r6, LSR #16
	ADD r5, r5, r6
	ADD r10, r10, r5
	
	;Compare
	CMP r10, r11			;piv vs key
	STMEAGT sp!, {r1}	;if piv> key, go to {start~piv}
	STMEAGT sp!, {r3}
	ADDLT r3, r3, #4		;piv +=4
 	STMEALT	sp!, {r3}	;if piv < key, go to { piv ~ end}
	STMEALT sp!, {r2}
	MOVEQ r12, r3			;if same, go Find
	BEQ Find					;to count how many same strings exist
	
	B Compare_Binary	;go Loop

;-----------------------------------------
; Register Description:
; R0  : length of find string
; R1  : start address
; R2  : end address
; R3  : pivot address
; R4  : Search_data's address
; R5  : Result_address
; R6  : Result_address+2000
; R7  : pivot's value
; R8  : search data's value
; R9  : r12's data
; R10 :pivot's shifted value
; R11 :search data's shifted value
; R12 : same data's first appear address
;-----------------------------------------
Find	;to find when the same string starts!
	SUB r12, r12, #4	;go backward
	
	LDR r9, [r12]	;load data
	
	CMP r9, r7	;same string?
	BEQ Find		;if same, go loop
	BNE Find2	;if not same, go Find2 to find the last string

Find2	;to find when the same string ends!
	ADD r12, r12, #4	;go forward
	
	LDR r9, [r12]	;load data
	
	CMP r9, r7		;same string?
	ADDEQ r0, #4	;if same, r0+=4, go loop
	BEQ Find2		
	BNE Search		;if not, go Search

;-----------------------------------------
; Register Description:
; R0  : 
; R1  : 0x50000000
; R2  : new string(including #)
; R3  : new string(including #)
; R4  : new string(including #)
; R5  : new string(including #)
; R6  : new string(including #)
; R7  : 
; R8  : load string 
; R9  : load string
; R10 :load string
; R11 :load string
; R12 : 
;-----------------------------------------
Store	;r11 : #
	;move into r2-r11 from r8-r11
	MOV r2, r8
	MOV r3, r9
	MOV r4, r10
	MOV r5, r11
	
	;r11 = #
	MOV r11, #0x23
	
	;first
	MOV r8, r2, LSR #24
	MOV r2, r2, LSL #8
	ADD r2, r11, r2
	
	;second
	MOV r9, r3, LSR#16
	MOV r3, r3, LSL #16
	MOV r11, r11, LSL#8
	
	ADD r3, r11, r3
	ADD r3, r3, r8
	
	;third
	MOV r10, r4, LSR #8
	
	MOV r4, r4, LSL #24
	MOV r11, r11, LSL #8
	
	ADD r4, r4,r9
	ADD r4, r4, r11

	;fifth
	MOV r6,r5
	
	;fourth
	MOV r11, r11, LSL#8
	ADD r5, r10, r11

	;load in r8~r11
	LDMFD r1!, {r8-r11}

	;store made string
	STMEA sp!, {r2-r6}
	
	;if load data is 0, end program
	CMP r8, #0x0
	BEQ END_PROGRAM
	BNE Store

END_PROGRAM
	;Save result to r0 register

	MOV pc, #0	; end program

Result_address1 & &60000000
Result_address	& &50000000

;-----------------------------------------
;DATA AREA
;-----------------------------------------
	AREA	data, DATA
Random_data
	DCB 109,101,115,115,35
	DCB 108,101,110,100,35
	DCB 109,111,115,116,35
	DCB 109,117,99,104,35
	DCB 116,111,117,114,35
	DCB 109,101,110,117,35
	DCB 112,97,105,110,35
	DCB 114,97,116,101,35
	DCB 108,97,116,101,35
	DCB 115,117,99,104,35
	DCB 114,117,105,110,35
	DCB 108,111,110,103,35
	DCB 115,105,122,101,35
	DCB 118,111,105,100,35
	DCB 116,111,108,108,35
	DCB 112,101,97,107,35
	DCB 108,97,110,100,35
	DCB 115,104,111,116,35
	DCB 119,97,110,101,35
	DCB 112,97,115,116,35
	DCB 119,97,103,101,35
	DCB 109,101,101,116,35
	DCB 117,114,103,101,35
	DCB 116,97,115,107,35
	DCB 114,105,115,101,35
	DCB 112,97,114,107,35
	DCB 114,111,111,102,35
	DCB 119,111,114,107,35
	DCB 114,101,97,108,35
	DCB 114,117,115,104,35
	DCB 115,116,105,114,35
	DCB 112,97,115,115,35
	DCB 115,101,97,116,35
	DCB 117,103,108,121,35
	DCB 108,101,97,100,35
	DCB 115,111,97,114,35
	DCB 106,111,105,110,35
	DCB 108,101,97,100,35
	DCB 115,104,111,119,35
	DCB 109,105,110,101,35
	DCB 115,105,116,101,35
	DCB 115,116,101,112,35
	DCB 119,97,103,101,35
	DCB 109,101,97,108,35
	DCB 109,111,118,101,35
	DCB 110,105,99,101,35
	DCB 109,105,115,115,35
	DCB 108,101,115,115,35
	DCB 108,101,115,115,35
	DCB 116,97,107,101,35
	DCB 114,101,110,116,35
	DCB 109,111,118,101,35
	DCB 115,104,105,112,35
	DCB 114,117,110,103,35
	DCB 87,101,108,108,35
	DCB 110,101,115,116,35
	DCB 119,101,101,100,35
	DCB 119,101,97,114,35
	DCB 112,108,97,110,35
	DCB 110,101,101,100,35
	DCB 110,111,114,109,35
	DCB 115,111,97,114,35
	DCB 113,117,105,116,35
	DCB 116,101,114,109,35
	DCB 114,117,115,104,35
	DCB 115,111,109,101,35
	DCB 115,105,110,107,35
	DCB 114,105,99,101,35
	DCB 115,101,101,109,35
	DCB 116,111,111,108,35
	DCB 115,117,114,101,35
	DCB 115,119,97,112,35
	DCB 114,101,97,114,35
	DCB 118,105,101,119,35
	DCB 108,105,118,101,35
	DCB 116,114,105,112,35
	DCB 108,111,97,110,35
	DCB 115,97,108,101,35
	DCB 110,97,109,101,35
	DCB 114,105,115,107,35
	DCB 109,105,110,100,35
	DCB 108,97,119,110,35
	DCB 116,105,108,101,35
	DCB 115,104,111,101,35
	DCB 116,104,101,110,35
	DCB 112,97,103,101,35
	DCB 116,97,112,101,35
	DCB 112,108,97,121,35
	DCB 115,105,103,110,35
	DCB 114,97,99,107,35
	DCB 109,97,116,104,35
	DCB 106,117,115,116,35
	DCB 115,116,101,112,35
	DCB 116,101,114,109,35
	DCB 112,111,115,101,35
	DCB 116,114,105,109,35
	DCB 118,105,115,97,35
	DCB 110,101,97,114,35
	DCB 110,97,105,108,35
	DCB 112,111,115,116,35
	DCB 115,104,117,116,35
	DCB 118,101,115,116,35
	DCB 115,116,97,121,35
	DCB 112,108,117,103,35
	DCB 115,111,114,116,35
	DCB 115,101,108,108,35
	DCB 112,117,108,108,35
	DCB 116,117,114,110,35
	DCB 108,101,110,100,35
	DCB 109,97,107,101,35
	DCB 116,121,112,101,35
	DCB 119,105,115,104,35
	DCB 109,101,97,110,35
	DCB 116,111,111,108,35
	DCB 110,101,101,100,35
	DCB 106,111,105,110,35
	DCB 116,101,110,100,35
	DCB 108,111,99,107,35
	DCB 116,104,97,110,35
	DCB 115,107,105,112,35
	DCB 114,97,116,101,35
	DCB 110,111,116,101,35
	DCB 115,108,117,109,35
	DCB 109,101,115,115,35
	DCB 108,101,110,100,35
	DCB 109,111,115,116,35
	DCB 109,117,99,104,35
	DCB 116,111,117,114,35
	DCB 109,101,110,117,35
	DCB 112,97,105,110,35
	DCB 114,97,116,101,35
	DCB 108,97,116,101,35
	DCB 115,117,99,104,35
	DCB 114,117,105,110,35
	DCB 108,111,110,103,35
	DCB 115,105,122,101,35
	DCB 118,111,105,100,35
	DCB 116,111,108,108,35
	DCB 112,101,97,107,35
	DCB 108,97,110,100,35
	DCB 115,104,111,116,35
	DCB 119,97,110,101,35
	DCB 112,97,115,116,35
	DCB 119,97,103,101,35
	DCB 109,101,101,116,35
	DCB 117,114,103,101,35
	DCB 116,97,115,107,35
	DCB 114,105,115,101,35
	DCB 112,97,114,107,35
	DCB 114,111,111,102,35
	DCB 119,111,114,107,35
	DCB 114,101,97,108,35
	DCB 114,117,115,104,35
	DCB 115,116,105,114,35
	DCB 112,97,115,115,35
	DCB 115,101,97,116,35
	DCB 117,103,108,121,35
	DCB 108,101,97,100,35
	DCB 115,111,97,114,35
	DCB 106,111,105,110,35
	DCB 108,101,97,100,35
	DCB 115,104,111,119,35
	DCB 109,105,110,101,35
	DCB 115,105,116,101,35
	DCB 115,116,101,112,35
	DCB 119,97,103,101,35
	DCB 109,101,97,108,35
	DCB 109,111,118,101,35
	DCB 110,105,99,101,35
	DCB 109,105,115,115,35
	DCB 108,101,115,115,35
	DCB 108,101,115,115,35
	DCB 116,97,107,101,35
	DCB 114,101,110,116,35
	DCB 109,111,118,101,35
	DCB 115,104,105,112,35
	DCB 114,117,110,103,35
	DCB 87,101,108,108,35
	DCB 110,101,115,116,35
	DCB 119,101,101,100,35
	DCB 119,101,97,114,35
	DCB 112,108,97,110,35
	DCB 110,101,101,100,35
	DCB 110,111,114,109,35
	DCB 115,111,97,114,35
	DCB 113,117,105,116,35
	DCB 116,101,114,109,35
	DCB 114,117,115,104,35
	DCB 115,111,109,101,35
	DCB 115,105,110,107,35
	DCB 114,105,99,101,35
	DCB 115,101,101,109,35
	DCB 116,111,111,108,35
	DCB 115,117,114,101,35
	DCB 115,119,97,112,35
	DCB 114,101,97,114,35
	DCB 118,105,101,119,35
	DCB 108,105,118,101,35
	DCB 116,114,105,112,35
	DCB 108,111,97,110,35
	DCB 115,97,108,101,35
	DCB 110,97,109,101,35
	DCB 114,105,115,107,35
	DCB 109,105,110,100,35
	DCB 108,97,119,110,35
	DCB 116,105,108,101,35
	DCB 115,104,111,101,35
	DCB 116,104,101,110,35
	DCB 112,97,103,101,35
	DCB 116,97,112,101,35
	DCB 112,108,97,121,35
	DCB 115,105,103,110,35
	DCB 114,97,99,107,35
	DCB 109,97,116,104,35
	DCB 106,117,115,116,35
	DCB 115,116,101,112,35
	DCB 116,101,114,109,35
	DCB 112,111,115,101,35
	DCB 116,114,105,109,35
	DCB 118,105,115,97,35
	DCB 110,101,97,114,35
	DCB 110,97,105,108,35
	DCB 112,111,115,116,35
	DCB 115,104,117,116,35
	DCB 118,101,115,116,35
	DCB 115,116,97,121,35
	DCB 112,108,117,103,35
	DCB 115,111,114,116,35
	DCB 115,101,108,108,35
	DCB 112,117,108,108,35
	DCB 116,117,114,110,35
	DCB 108,101,110,100,35
	DCB 109,97,107,101,35
	DCB 116,121,112,101,35
	DCB 119,105,115,104,35
	DCB 109,101,97,110,35
	DCB 116,111,111,108,35
	DCB 110,101,101,100,35
	DCB 106,111,105,110,35
	DCB 116,101,110,100,35
	DCB 108,111,99,107,35
	DCB 116,104,97,110,35
	DCB 115,107,105,112,35
	DCB 114,97,116,101,35
	DCB 110,111,116,101,35
	DCB 115,108,117,109,35
	DCB 101,97,114,110,35
	DCB 100,111,115,101,35
	DCB 103,105,118,101,35
	DCB 98,105,108,108,35
	DCB 104,111,108,100,35
	DCB 98,101,97,114,35
	DCB 102,105,108,108,35
	DCB 102,111,108,100,35
	DCB 97,98,108,101,35
	DCB 102,97,108,108,35
	DCB 104,97,118,101,35
	DCB 100,101,101,109,35
	DCB 101,118,101,110,35
	DCB 104,111,115,116,35
	DCB 104,105,114,101,35
	DCB 98,101,97,114,35
	DCB 100,117,116,121,35
	DCB 102,97,114,101,35
	DCB 104,111,108,101,35
	DCB 99,111,100,101,35
	DCB 98,111,119,108,35
	DCB 100,114,97,119,35
	DCB 103,108,97,100,35
	DCB 102,105,114,109,35
	DCB 102,108,97,103,35
	DCB 100,101,101,112,35
	DCB 104,97,117,108,35
	DCB 104,97,108,108,35
	DCB 98,97,114,101,35
	DCB 99,114,111,112,35
	DCB 102,101,101,108,35
	DCB 100,105,118,101,35
	DCB 104,117,114,116,35
	DCB 98,117,108,107,35
	DCB 98,117,108,107,35
	DCB 104,105,107,101,35
	DCB 97,119,97,121,35
	DCB 97,119,97,121,35
	DCB 100,114,105,112,35
	DCB 100,114,117,103,35
	DCB 99,97,114,101,35
	DCB 104,101,97,100,35
	DCB 100,105,114,116,35
	DCB 103,97,116,101,35
	DCB 98,105,116,101,35
	DCB 104,111,112,101,35
	DCB 101,97,114,110,35
	DCB 102,105,110,101,35
	DCB 98,105,108,108,35
	DCB 98,101,108,108,35
	DCB 99,111,112,121,35
	DCB 101,110,118,121,35
	DCB 99,111,115,116,35
	DCB 102,105,108,101,35
	DCB 101,97,115,121,35
	DCB 101,97,115,121,35
	DCB 100,97,109,112,35
	DCB 104,111,117,114,35
	DCB 102,97,105,108,35
	DCB 99,111,122,121,35
	DCB 99,117,114,98,35
	DCB 99,117,114,98,35
	DCB 99,105,116,101,35
	DCB 103,97,105,110,35
	DCB 102,97,99,101,35
	DCB 102,117,101,108,35
	DCB 102,117,101,108,35
	DCB 104,101,97,116,35
	DCB 104,111,108,100,35
	DCB 99,111,114,110,35
	DCB 101,97,115,101,35
	DCB 102,97,114,101,35
	DCB 99,104,101,102,35
	DCB 102,101,97,116,35
	DCB 102,111,114,109,35
	DCB 102,117,110,100,35
	DCB 102,117,110,100,35
	DCB 100,101,102,121,35
	DCB 99,104,101,102,35
	DCB 104,111,115,116,35
	DCB 104,97,108,116,35
	DCB 97,114,101,97,35
	DCB 102,97,99,101,35
	DCB 99,108,97,121,35
	DCB 102,105,110,100,35
	DCB 98,111,110,100,35
	DCB 102,105,108,108,35
	DCB 98,111,111,107,35
	DCB 100,101,97,108,35
	DCB 99,111,108,100,35
	DCB 97,105,100,101,35
	DCB 99,97,102,101,35
	DCB 99,104,105,110,35
	DCB 102,97,108,108,35
	DCB 99,97,115,104,35
	DCB 99,97,115,104,35
	DCB 102,111,114,109,35
	DCB 109,101,115,115,35
	DCB 108,101,110,100,35
	DCB 109,111,115,116,35
	DCB 109,117,99,104,35
	DCB 116,111,117,114,35
	DCB 109,101,110,117,35
	DCB 112,97,105,110,35
	DCB 114,97,116,101,35
	DCB 108,97,116,101,35
	DCB 115,117,99,104,35
	DCB 114,117,105,110,35
	DCB 108,111,110,103,35
	DCB 115,105,122,101,35
	DCB 118,111,105,100,35
	DCB 116,111,108,108,35
	DCB 112,101,97,107,35
	DCB 108,97,110,100,35
	DCB 115,104,111,116,35
	DCB 119,97,110,101,35
	DCB 112,97,115,116,35
	DCB 119,97,103,101,35
	DCB 109,101,101,116,35
	DCB 117,114,103,101,35
	DCB 116,97,115,107,35
	DCB 114,105,115,101,35
	DCB 112,97,114,107,35
	DCB 114,111,111,102,35
	DCB 119,111,114,107,35
	DCB 114,101,97,108,35
	DCB 114,117,115,104,35
	DCB 115,116,105,114,35
	DCB 112,97,115,115,35
	DCB 115,101,97,116,35
	DCB 117,103,108,121,35
	DCB 108,101,97,100,35
	DCB 115,111,97,114,35
	DCB 106,111,105,110,35
	DCB 108,101,97,100,35
	DCB 115,104,111,119,35
	DCB 109,105,110,101,35
	DCB 115,105,116,101,35
	DCB 115,116,101,112,35
	DCB 119,97,103,101,35
	DCB 109,101,97,108,35
	DCB 109,111,118,101,35
	DCB 110,105,99,101,35
	DCB 109,105,115,115,35
	DCB 108,101,115,115,35
	DCB 108,101,115,115,35
	DCB 116,97,107,101,35
	DCB 114,101,110,116,35
	DCB 109,111,118,101,35
	DCB 115,104,105,112,35
	DCB 114,117,110,103,35
	DCB 87,101,108,108,35
	DCB 110,101,115,116,35
	DCB 119,101,101,100,35
	DCB 119,101,97,114,35
	DCB 112,108,97,110,35
	DCB 110,101,101,100,35
	DCB 110,111,114,109,35
	DCB 115,111,97,114,35
	DCB 113,117,105,116,35
	DCB 116,101,114,109,35
	DCB 114,117,115,104,35
	DCB 115,111,109,101,35
	DCB 115,105,110,107,35
	DCB 114,105,99,101,35
	DCB 115,101,101,109,35
	DCB 116,111,111,108,35
	DCB 115,117,114,101,35
	DCB 115,119,97,112,35
	DCB 114,101,97,114,35
	DCB 118,105,101,119,35
	DCB 108,105,118,101,35
	DCB 116,114,105,112,35
	DCB 108,111,97,110,35
	DCB 115,97,108,101,35
	DCB 110,97,109,101,35
	DCB 114,105,115,107,35
	DCB 109,105,110,100,35
	DCB 108,97,119,110,35
	DCB 116,105,108,101,35
	DCB 115,104,111,101,35
	DCB 116,104,101,110,35
	DCB 112,97,103,101,35
	DCB 116,97,112,101,35
	DCB 112,108,97,121,35
	DCB 115,105,103,110,35
	DCB 114,97,99,107,35
	DCB 109,97,116,104,35
	DCB 106,117,115,116,35
	DCB 115,116,101,112,35
	DCB 116,101,114,109,35
	DCB 112,111,115,101,35
	DCB 116,114,105,109,35
	DCB 118,105,115,97,35
	DCB 110,101,97,114,35
	DCB 110,97,105,108,35
	DCB 112,111,115,116,35
	DCB 115,104,117,116,35
	DCB 118,101,115,116,35
	DCB 115,116,97,121,35
	DCB 112,108,117,103,35
	DCB 115,111,114,116,35
	DCB 115,101,108,108,35
	DCB 112,117,108,108,35
	DCB 116,117,114,110,35
	DCB 108,101,110,100,35
	DCB 109,97,107,101,35
	DCB 116,121,112,101,35
	DCB 119,105,115,104,35
	DCB 109,101,97,110,35
	DCB 116,111,111,108,35
	DCB 110,101,101,100,35
	DCB 106,111,105,110,35
	DCB 116,101,110,100,35
	DCB 108,111,99,107,35
	DCB 116,104,97,110,35
	DCB 115,107,105,112,35
	DCB 114,97,116,101,35
	DCB 110,111,116,101,35
	DCB 115,108,117,109,35
	DCB 99,117,114,98,35
	DCB 102,105,110,101,35
	DCB 114,101,105,110,35
	DCB 99,114,97,109,35
	DCB 104,105,100,101,35
	DCB 115,105,110,107,35
	DCB 98,117,114,121,35
	DCB 101,100,103,101,35
	DCB 119,97,110,101,35
	DCB 112,97,99,101,35
	DCB 118,105,101,119,35
	DCB 102,108,97,119,35
	DCB 116,105,100,101,35
	DCB 115,105,122,101,35
	DCB 102,101,101,100,35
	DCB 100,114,97,119,35
	DCB 98,97,114,101,35
	DCB 102,117,115,101,35
	DCB 106,101,115,116,35
	DCB 115,111,97,114,35
	DCB 109,101,114,101,35
	DCB 116,111,111,108,35
	DCB 97,108,108,121,35
	DCB 114,97,114,101,35
	DCB 116,104,117,115,35
	DCB 108,97,115,116,35
	DCB 111,97,116,104,35
	DCB 115,116,97,121,35
	DCB 110,111,116,101,35
	DCB 112,105,108,101,35
	DCB 109,117,116,101,35
	DCB 108,97,115,104,35
	DCB 98,97,110,107,35
	DCB 108,111,110,103,35

 
Search_data
	DCB 101,109,105,116,35
	DCB 103,117,115,104,35
	DCB 98,97,114,101,35
	DCB 103,108,111,119,35
	DCB 118,105,108,101,35
	DCB 115,108,97,121,35
	DCB 104,111,108,100,35
	DCB 115,101,101,112,35
	DCB 97,99,105,100,35
	DCB 118,111,105,100,35
	DCB 97,99,104,101,35
	DCB 115,105,110,107,35
	DCB 115,97,102,101,35
	DCB 119,101,97,107,35
	DCB 102,97,100,101,35
	DCB 109,111,100,101,35
	DCB 102,101,97,116,35
	DCB 114,116,108,108,35
	DCB 116,117,114,110,35	
	DCB 115,116,105,114,35
	DCB 116,105,110,121,35
	DCB 115,111,97,107,35
	DCB 118,101,105,110,35
	DCB 114,117,110,103,35	   
	DCB 115,108,97,98,35
	DCB 109,111,99,107,35
	DCB 106,101,101,114,35
	DCB 106,101,115,116,35
	DCB 119,97,114,121,35
	DCB 104,101,101,100,35
	DCB 100,117,108,108,35
	DCB 115,117,114,101,35
	DCB 98,111,100,101,35
	DCB 115,116,97,98,35
	DCB 115,101,101,107,35
	DCB 108,98,101,100,35
	DCB 106,111,108,116,35
	DCB 107,105,110,100,35
	DCB 116,111,117,116,35
	DCB 115,104,101,100,35
	DCB 98,105,97,115,35
	DCB 108,111,110,103,35
	DCB 114,105,111,116,35
	DCB 102,108,101,101,35
	DCB 102,114,101,101,35
	DCB 99,111,114,101,35
	DCB 119,97,114,112,35
	DCB 115,116,101,112,35
	DCB 100,97,117,98,35
	DCB 108,111,99,107,35


	END