section .rodata
msg_noword: db "No such word!", 0

section .text

%include "colon.inc"
%include "words.inc"

extern read_word
extern find_word
extern print_newline
extern print_string
extern string_length
extern exit

global _start

_start:
	push rbp	;save it
	mov rbp, rsp	;save rsp
	sub rsp, 256	;max 255 chars + 0
	mov rdi, rsp		
	call read_word
	mov rdi, rax
	mov rsi, lw
	call find_word
	test rax, rax
	jz .bad

	add rax, 8
	push rax
	mov rax, [rsp]
	mov rdi, rax
	call string_length
	pop rdi
	add rdi, rax
	inc rdi
	call print_string
	mov rsp, rbp
	pop rbp
	mov rdi, 0
	call exit

.bad:
	mov rdi, msg_noword
	call print_string
	
	mov rsp, rbp
	pop rbp
	xor rdi, rdi
	call exit

