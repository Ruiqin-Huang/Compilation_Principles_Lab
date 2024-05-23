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

   mov eax, 1
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax

   mov eax, 2
   push eax
   pop eax
   mov DWORD PTR [ebp-8], eax
   mov DWORD PTR [ebp-12], 0

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



   mov eax, 114514
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
