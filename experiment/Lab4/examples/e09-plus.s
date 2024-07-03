.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global gcd
.text
gcd:
   push ebp
   mov ebp, esp
   sub esp, 0x400
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



   mov eax, DWORD PTR [ebp-8]
   push eax

   mov eax, 0
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   sete al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_else_0



   mov eax, DWORD PTR [ebp-4]
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
   jmp .L_else_end_0
.L_else_0:



   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cdq
   idiv ebx
   push edx
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax
   call gcd
   add esp, 8
   mov DWORD PTR [ebp-12], eax

   mov eax, DWORD PTR [ebp-12]
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

   mov eax, 7
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax

   mov eax, 13
   push eax
   pop eax
   mov DWORD PTR [ebp-8], eax

   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call gcd
   add esp, 8
   mov DWORD PTR [ebp-16], eax

   mov eax, DWORD PTR [ebp-16]
   push eax
   pop eax
   mov DWORD PTR [ebp-12], eax

   mov eax, DWORD PTR [ebp-12]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8



   mov eax, DWORD PTR [ebp-12]
   push eax

   mov eax, 5
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setl al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_else_1


   mov eax, 500
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8

   jmp .L_else_end_1
.L_else_1:


   mov eax, 600
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8



   mov eax, DWORD PTR [ebp-12]
   push eax

   mov eax, 10
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setg al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_else_2


   mov eax, 700
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8

   jmp .L_else_end_2
.L_else_2:


   mov eax, 800
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8

.L_else_end_2:


   mov eax, DWORD PTR [ebp-12]
   push eax

   mov eax, 13
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   sete al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_else_3


   mov eax, 900
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8

.L_else_3:
.L_else_end_1:


   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
