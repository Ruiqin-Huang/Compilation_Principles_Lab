.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global main
.data
main_return_value:
    .int 0
.text
main:
   push ebp
   mov ebp, esp
   sub esp, 0x200

   mov eax, 5
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 2
   push eax

   pop ebx
   pop eax
   cdq
   idiv ebx
   push edx

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
   je .L_if_end_0


   mov eax, 0
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8

.L_if_end_0:


   mov eax, 1
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8



   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
