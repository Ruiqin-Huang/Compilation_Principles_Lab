.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global test
.data
test_return_value:
    .int 0
.text
test:
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

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   imul eax, ebx
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cdq
   idiv ebx
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   and eax, ebx
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

   mov eax, 114
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax

   mov eax, 514
   push eax
   pop eax
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
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   imul eax, ebx
   push eax
   pop eax
   push eax
   call test
   add esp, 8
   mov test_return_value, eax

   mov eax, 1
   push eax

   mov eax, test_return_value
   push eax

   pop ebx
   pop eax
   add eax, ebx
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
