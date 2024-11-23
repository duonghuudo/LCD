    EXPORT   Dec2String
    EXPORT   Fix2String
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    PRESERVE8

  
;-----------------------Dec2String-----------------------
; Convert a 32-bit number into unsigned decimal format
; String the string into the empty array add null-termination
; Input: R0 (call by value) 32-bit unsigned number
;        R1 pointer to empty array
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
Dec2String
    PUSH {R4, R5, R6, LR}           ; Save registers
	MOV 	R5, R0            		; R0->R5
	MOV 	R6, R1
LoopDec
	MOV     R3, #10					;R3=10
    UDIV    R5, R5, R3        ; R5 = R5 / 10 (quotient)
    MLS     R4, R5, R3, R5    ; R4 = R5 % 10 (remainder)
OutDec
	ADD R4, #48
	STR R4, [R6]
	ADD R6, #1
	CMP R5, #0
	BEQ endDec
	B LoopDec
endDec
	MOV R4, #' '
	STR R4, [R6]
	BL ReverseString
    POP {R4, R5, R6, LR}            ; Restore registers
    BX LR
ReverseString
	MOV R2, R1
	SUB R6, R6, #1	;R6 tro den ki tu cuoi cung truoc null
ReversesLoop
	CMP R2, R6
	BCS ReversesDone
	
	;Reverses
	LDRB R3, [R2]
	LDRB R4, [R6]
	STRB R4, [R2]
	STRB R3, [R6]
	
	;Câp nhât con tro
	ADD R2, #1
	SUB R6, #1
	B ReversesLoop
ReversesDone
	BX LR
;* * * * * * * * End of Dec2String * * * * * * * *


; -----------------------Fix2String----------------------
; Create characters for LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
;          R1 pointer to empty array
; Outputs: none
; E.g., R0=0,    then create "0.000 "
;       R0=3,    then create "0.003"
;       R0=89,   then create "0.089"
;       R0=123,  then create "0.123"
;       R0=9999, then create "9.999"
;       R0>9999, then create "*.***"
; Invariables: This function must not permanently modify registers R4 to R11
Fix2String
    PUSH {R4, R5, R6, LR}               ; Save registers
	MOV R5, R0              ;Save unsigned number
	MOV R4, R1				;Save pointer
	LDR R2, =10000
	CMP R5, R2
	BCS OutOfRange
	LDR R3, =1000
	UDIV R5, R5, R3			;R5 / 1000
	MLS R6, R5, R3, R5      ; R6 = R5 % 1000 (remainder)
StoreFix
	STRB R5, [R4], #1
	LDR R2, ='.'
	STRB R2, [R4], #1
loopStore
	MOV R2, #10
	UDIV R3, R3, R2
	UDIV R2, R6, R3
	MLS R6, R2, R3, R6
	STRB R2, [R4], #1
	CMP R6, #0
	BNE loopStore
	B EndFix2String
OutOfRange
    ; If out of range, store "*.***"
    LDR R2, ='.'                    
    MOV R2, #'*'
    STRB R2, [R4], #1
    MOV R2, #'.'
    STRB R2, [R4], #1
    STRB R2, [R4], #1
    STRB R2, [R4], #1
    MOV R2, #' '
    STRB R2, [R4]                   ; Null-terminate with a space

EndFix2String
    POP {R4, R5, R6, LR}                ; Restore registers
    BX LR

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file