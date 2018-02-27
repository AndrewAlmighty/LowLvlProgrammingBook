section .text

string_length:
    	xor rax, rax
.loop:
	cmp byte[rdi + rax], 0
	je .end
	inc rax
	jmp .loop	
.end:	
    	ret

print_string:
	mov rsi, rdi
	call string_length
	mov rdx, rax
	mov rax, 1
	mov rdi, 1
	syscall
    	ret

print_char:
	push rdi	;Here we have char code, we put it on the stack, then we load adress to rdi.
	mov rdi, rsp
	call print_string
	pop rdi
	ret

print_newline:
	mov rdi, 10
	jmp print_char

print_uint:
	mov rax, rdi	;putting number in rax
	mov rdi, rsp	;save adress of rsp in rdi
	mov r8, 10	;our value for div
	push 0		;end of string is 0
	dec rdi		;rdi is pointing to 0 now
	sub rsp, 16	;reserve some place on stack 

.loop:
	xor rdx, rdx	;set remainder to 0
	div r8		;div rax by 10, stored in r8.
	or dl, 0x30	;set the remainder number to ASCII code
	dec rdi		;move the string pointer
	mov [rdi], dl	;save the char		
	
	test rax, rax	;if rax == 0
	jnz .loop		

	call print_string

	add rsp, 24	;16 + 8(push 0)
	ret

print_int:
	test rdi, rdi
	jns print_uint

	push rdi
	mov rdi, '-'
	call print_char
	pop rdi
	neg rdi
	jmp print_uint
	
	ret

read_char:
	push 0
	mov rsi, rsp
	xor rax, rax
	xor rdi, rdi
	mov rdx, 1
	syscall
	pop rax	
	ret 

read_word:
    	push r14
    	push r15
    	xor r14, r14 
    	mov r15, rsi
    	dec r15
.A:
    	push rdi
    	call read_char
    	pop rdi
    	cmp al, ' '
    	je .A
    	cmp al, 10
    	je .A
    	cmp al, 13
    	je .A 
    	cmp al, 9 
    	je .A
    	test al, al
    	jz .C

.B:
    	mov byte [rdi + r14], al
    	inc r14

    	push rdi
    	call read_char
    	pop rdi
    	cmp al, ' '
    	je .C
    	cmp al, 10
    	je .C
    	cmp al, 13
    	je .C 
    	cmp al, 9
    	je .C
    	test al, al
    	jz .C
    	cmp r14, r15
    	je .D

    	jmp .B

.C:
   	mov byte [rdi + r14], 0
    	mov rax, rdi 
   
    	mov rdx, r14 
    	pop r15
    	pop r14
    	ret

.D:
    	xor rax, rax
    	pop r15
    	pop r14
	ret	

	
; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
	mov r8, 10
	xor rcx, rcx
	xor rax, rax
	
.loop:
	movzx r9, byte[rdi + rcx]	;Mov with 0 extend - because later we ad r9 to rax
	cmp r9b, '0'
	jb .end
	cmp r9b, '9'
	ja .end

	mul r8
	and r9b, 0xf			;remove not important things
	
	add rax, r9
	inc rcx
	jmp .loop
	
.end:
	mov rdx, rcx	
	ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
	mov al, byte [rdi]
	cmp al, '-'
	jne parse_uint
	
	inc rdi		;because 1 char was '-'
	call parse_uint
	neg rax
	test rdx, rdx
	jz .error
	inc rdx		;because we got '-'
	ret
.error:
	xor rax, rax    
	ret 

string_equals:
	mov al, byte [rdi]
	cmp al, byte[rsi]
	jne .NE

	inc rdi
	inc rsi
	test al, al
	jnz string_equals
	mov rax, 1
	ret

.NE:
	xor rax, rax	
	ret

string_copy:
	push rdi
	push rsi
	push rdx
	call string_length
	pop rdx
	pop rsi
	pop rdi

	cmp rax, rdx
	jae .error	;jae because null terminator also takes place
	
	push rsi

.loop:	
	mov dl, byte [rdi]
	mov byte[rsi], dl
	inc rsi
	inc rdi
	test dl, dl
	jnz .loop
	pop rax
	ret
	
.error:
	xor rax, rax
	ret
