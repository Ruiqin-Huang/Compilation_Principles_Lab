.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

.global fibonacci
.data
fibonacci_return_value:
    .int 0
.text
fibonacci:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov eax, DWORD PTR [ebp+8]
   mov DWORD PTR [ebp-4], eax


   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 0
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setle al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_if_end_0



   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
.L_if_end_0:



   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   sete al
   movzx eax, al
   push eax
   pop eax
   cmp eax, 0
   je .L_if_end_1



   mov eax, 1
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret
.L_if_end_1:


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
   call fibonacci
   add esp, 4
   mov fibonacci_return_value, eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, 2
   push eax

   pop ebx
   pop eax
   sub eax, ebx
   push eax
   pop eax
   push eax
   call fibonacci
   add esp, 4
   mov fibonacci_return_value, eax

   mov eax, fibonacci_return_value
   push eax

   mov eax, fibonacci_return_value
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax
   pop eax
   mov DWORD PTR [ebp-8], eax

   mov eax, DWORD PTR [ebp-8]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8



   mov eax, DWORD PTR [ebp-8]
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

   mov eax, 5
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax

   mov eax, DWORD PTR [ebp-4]
   push eax
   pop eax
   push eax
   call fibonacci
   add esp, 4
   mov fibonacci_return_value, eax

   mov eax, fibonacci_return_value
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