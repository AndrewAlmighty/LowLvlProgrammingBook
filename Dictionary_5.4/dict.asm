global find_word
extern string_equals

section .test:

find_word:
	;rdi - pointer to string
	;rsi - pointer to last word in dic

	xor rax, rax	;rax is 0 now
.loop:
	test rsi, rsi	;if RSI = 0 end
	jz .end
	push rsi
	push rdi
	add rsi, 8
	call string_equals
	pop rdi
	pop rsi
	test rax, rax 	;is equal?
	jnz .found
	mov rsi, [rsi]	;load address of next element
	jmp .loop
	
.found:
	mov rax, rsi

.end:
	ret	
