.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global opplus
.data
opplus_return_value:
    .int 0
.text
opplus:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret

.global opminus
.data
opminus_return_value:
    .int 0
.text
opminus:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   sub eax, ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret

.global opmul
.data
opmul_return_value:
    .int 0
.text
opmul:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
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

.global opdiv
.data
opdiv_return_value:
    .int 0
.text
opdiv:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cdq
   idiv ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret

.global opmod
.data
opmod_return_value:
    .int 0
.text
opmod:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


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
   mov esp, ebp
   pop ebp
   ret

.global opand
.data
opand_return_value:
    .int 0
.text
opand:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   and eax, ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret

.global opor
.data
opor_return_value:
    .int 0
.text
opor:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   or eax, ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret

.global opxor
.data
opxor_return_value:
    .int 0
.text
opxor:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   xor eax, ebx
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret

.global opplus_114514
.data
opplus_114514_return_value:
    .int 0
.text
opplus_114514:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax
   mov eax, DWORD PTR [ebp+16]
   mov DWORD PTR [ebp-12], eax
   mov eax, DWORD PTR [ebp+20]
   mov DWORD PTR [ebp-16], eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   mov DWORD PTR [ebp-20], eax

   mov eax, DWORD PTR [ebp-12]
   push eax
   pop eax
   mov DWORD PTR [ebp-24], eax

   mov eax, DWORD PTR [ebp-16]
   push eax
   pop eax
   mov DWORD PTR [ebp-28], eax


   mov eax, DWORD PTR [ebp-8]
   push eax

   mov eax, 114514
   push eax

   pop ebx
   pop eax
   add eax, ebx
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
   sub esp, 0x200
   mov DWORD PTR [ebp-4], 0
   mov DWORD PTR [ebp-8], 0
   mov DWORD PTR [ebp-12], 0
   mov DWORD PTR [ebp-16], 0
   mov DWORD PTR [ebp-20], 0
   mov DWORD PTR [ebp-24], 0
   mov DWORD PTR [ebp-28], 0
   mov DWORD PTR [ebp-32], 0
   mov DWORD PTR [ebp-36], 0
   mov DWORD PTR [ebp-40], 0


   mov eax, 114
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax


   mov eax, 514
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
   call opplus
   add esp, 8
   mov opplus_return_value, eax

   mov eax, opplus_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-20], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opminus
   add esp, 8
   mov opminus_return_value, eax

   mov eax, opminus_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-12], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opmul
   add esp, 8
   mov opmul_return_value, eax

   mov eax, opmul_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-16], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opdiv
   add esp, 8
   mov opdiv_return_value, eax

   mov eax, opdiv_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-24], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opmod
   add esp, 8
   mov opmod_return_value, eax

   mov eax, opmod_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-28], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opand
   add esp, 8
   mov opand_return_value, eax

   mov eax, opand_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-32], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opor
   add esp, 8
   mov opor_return_value, eax

   mov eax, opor_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-36], eax


   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call opxor
   add esp, 8
   mov opxor_return_value, eax

   mov eax, opxor_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-40], eax
   mov DWORD PTR [ebp-44], 0


   mov eax, 4
   push eax
   pop eax
   push eax

   mov eax, 3
   push eax
   pop eax
   push eax

   mov eax, 2
   push eax
   pop eax
   push eax

   mov eax, 1
   push eax
   pop eax
   push eax
   call opplus_114514
   add esp, 16
   mov opplus_114514_return_value, eax

   mov eax, opplus_114514_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-44], eax

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


   mov eax, DWORD PTR [ebp-20]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-12]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-16]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-24]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-28]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-32]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-36]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-40]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, DWORD PTR [ebp-44]
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
