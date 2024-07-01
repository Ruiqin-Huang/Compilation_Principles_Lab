.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global gcd
.data
gcd_return_value:
    .int 0
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
   je .L_if_end_0



   mov eax, DWORD PTR [ebp-4]
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
.L_if_end_0:


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
   push eax
   push offset format_str
   call printf
   add esp, 8



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
   mov DWORD PTR [ebp-16], eax

   mov eax, DWORD PTR [ebp-16]
   push eax

   pop eax
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



   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
