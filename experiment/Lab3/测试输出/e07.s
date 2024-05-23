.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global print3
.text
print3:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax
   mov eax, DWORD PTR [ebp+12]
   mov DWORD PTR [ebp-8], eax
   mov eax, DWORD PTR [ebp+16]
   mov DWORD PTR [ebp-12], eax

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


   mov eax, DWORD PTR [ebp-12]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov esp, ebp
   pop ebp
   ret

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
   mov eax, DWORD PTR [ebp+16]
   mov DWORD PTR [ebp-12], eax
   mov eax, DWORD PTR [ebp+20]
   mov DWORD PTR [ebp-16], eax

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

   mov eax, 114
   push eax

   pop eax
   neg eax
   push eax
   pop eax
   mov DWORD PTR [ebp-8], eax

   mov eax, 514
   push eax
   pop eax
   mov DWORD PTR [ebp-12], eax

   mov eax, 514
   push eax

   pop eax
   neg eax
   push eax
   pop eax
   mov DWORD PTR [ebp-16], eax

   mov eax, DWORD PTR [ebp-16]
   push eax

   mov eax, DWORD PTR [ebp-12]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-16]
   push eax

   pop eax
   neg eax
   push eax

   mov eax, DWORD PTR [ebp-12]
   push eax

   pop eax
   neg eax
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop eax
   neg eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop eax
   neg eax
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-16]
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, DWORD PTR [ebp-12]
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop eax
   neg eax
   dec eax
   push eax
   call print4
   add esp, 16


   mov eax, 1
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax


   mov eax, 0
   push eax
   pop eax
   mov DWORD PTR [ebp-8], eax


   mov eax, 1
   push eax

   pop eax
   neg eax
   push eax
   pop eax
   mov DWORD PTR [ebp-12], eax

   mov eax, DWORD PTR [ebp-12]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   call print3
   add esp, 12

   mov eax, DWORD PTR [ebp-12]
   push eax

   pop eax
   neg eax
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop eax
   neg eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop eax
   neg eax
   push eax
   call print3
   add esp, 12

   mov eax, DWORD PTR [ebp-12]
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop eax
   neg eax
   dec eax
   push eax
   call print3
   add esp, 12


   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
