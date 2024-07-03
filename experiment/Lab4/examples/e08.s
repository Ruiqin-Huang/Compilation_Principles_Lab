.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global factorial
.text
factorial:
   push ebp
   mov ebp, esp
   sub esp, 0x400
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setle al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_else_0



   mov eax, 1
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
   jmp .L_else_end_0
.L_else_0:



   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop eax
   push eax
   call factorial
   add esp, 4
   mov DWORD PTR [ebp-8], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   imul eax, ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
.L_else_end_0:

.global main
.text
main:
   push ebp
   mov ebp, esp
   sub esp, 0x400

   mov eax, 1
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax

.L_while_cond_0:

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 5
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setle al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_while_end_0


   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call factorial
   add esp, 4
   mov DWORD PTR [ebp-8], eax

   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8



   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax
   jmp .L_while_cond_0
.L_while_end_0:


   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
