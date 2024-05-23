.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global print4
.text
print4:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov esp, ebp
   pop ebp
   ret

.global main
.data
main_return_value:
    .int 0
.text
main:
   push ebp
   mov ebp, esp
   sub esp, 0x200

   mov eax, 1
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 55
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, 3
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, 2
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue0
   cmp ebx, 0
   jne .Ltrue0
   mov eax, 0
   jmp .Lend0
.Ltrue0:
   mov eax, 1
.Lend0:
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse1
   cmp ebx, 0
   je .Lfalse1
   mov eax, 1
   jmp .Lend1
.Lfalse1:
   mov eax, 0
.Lend1:
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 4
   push eax

   mov eax, 5
   push eax

   pop eax
   neg eax
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse2
   cmp ebx, 0
   je .Lfalse2
   mov eax, 1
   jmp .Lend2
.Lfalse2:
   mov eax, 0
.Lend2:
   push eax

   mov eax, 222
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue3
   cmp ebx, 0
   jne .Ltrue3
   mov eax, 0
   jmp .Lend3
.Ltrue3:
   mov eax, 1
.Lend3:
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, 0
   push eax

   mov eax, 3
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, 2
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue4
   cmp ebx, 0
   jne .Ltrue4
   mov eax, 0
   jmp .Lend4
.Ltrue4:
   mov eax, 1
.Lend4:
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse5
   cmp ebx, 0
   je .Lfalse5
   mov eax, 1
   jmp .Lend5
.Lfalse5:
   mov eax, 0
.Lend5:
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 4
   push eax

   mov eax, 5
   push eax

   pop eax
   neg eax
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse6
   cmp ebx, 0
   je .Lfalse6
   mov eax, 1
   jmp .Lend6
.Lfalse6:
   mov eax, 0
.Lend6:
   push eax

   mov eax, 222
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue7
   cmp ebx, 0
   jne .Ltrue7
   mov eax, 0
   jmp .Lend7
.Ltrue7:
   mov eax, 1
.Lend7:
   push eax
   call print4
   add esp, 8


   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
