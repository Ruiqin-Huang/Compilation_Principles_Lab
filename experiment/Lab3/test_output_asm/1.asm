.intel_syntax noprefix
.text

.global add10
.data
add10_return_value dd 0
.text
add10:
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov DWORD PTR [ebp-4], DWORD PTR [ebp+8]

   mov eax, 10
   push eax
   pop eax
   mov DWORD PTR [ebp-8], eax


   mov eax, DWORD PTR [ebp-8]
   push eax

   mov eax, DWORD PTR [ebp-4]
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
   mov esp, ebp
   pop ebp
   ret

.global main
.data
main_return_value dd 0
.text
   push ebp
   mov ebp, esp
   sub esp, 0x200
   mov DWORD PTR [ebp-4], 0


   mov eax, 1
   push eax
   pop eax
   push eax
   call add10
   add esp, 4
   mov add10_return_value, eax

   mov eax, add10_return_value
   push eax
   pop eax
   mov DWORD PTR [ebp-4], eax


   mov eax, 0
   push eax

   pop eax
   mov esp, ebp
   pop ebp
   ret