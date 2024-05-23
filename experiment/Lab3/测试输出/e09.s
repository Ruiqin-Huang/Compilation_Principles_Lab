.intel_syntax noprefix
.extern printf

.data
format_str:
   .asciz "%d\n"

.text

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
   cmp eax, ebx
   sete al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-12], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   sete al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-16], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setne al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-20], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setne al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-24], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setl al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-28], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setl al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-32], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setle al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-36], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setle al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-40], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setg al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-44], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setg al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-48], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-8]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setge al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-52], eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   mov eax, DWORD PTR [ebp-4]
   push eax

   pop ebx
   pop eax
   cmp eax, ebx
   setge al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-56], eax

   mov eax, DWORD PTR [ebp-24]
   push eax

   mov eax, DWORD PTR [ebp-20]
   push eax

   mov eax, DWORD PTR [ebp-16]
   push eax

   mov eax, DWORD PTR [ebp-12]
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-40]
   push eax

   mov eax, DWORD PTR [ebp-36]
   push eax

   mov eax, DWORD PTR [ebp-32]
   push eax

   mov eax, DWORD PTR [ebp-28]
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-56]
   push eax

   mov eax, DWORD PTR [ebp-52]
   push eax

   mov eax, DWORD PTR [ebp-48]
   push eax

   mov eax, DWORD PTR [ebp-44]
   push eax
   call print4
   add esp, 16

   mov eax, 114
   push eax

   mov eax, 514
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse0
   cmp ebx, 0
   je .Lfalse0
   mov eax, 1
   jmp .Lend0
.Lfalse0:
   mov eax, 0
.Lend0:
   push eax
   pop eax
   mov DWORD PTR [ebp-60], eax

   mov eax, 114
   push eax

   mov eax, 0
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse1
   cmp ebx, 0
   je .Lfalse1
   mov eax, 1
   jmp .Lend1
.Lfalse1:
   mov eax, 0
.Lend1:
   push eax
   pop eax
   mov DWORD PTR [ebp-64], eax

   mov eax, 0
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse2
   cmp ebx, 0
   je .Lfalse2
   mov eax, 1
   jmp .Lend2
.Lfalse2:
   mov eax, 0
.Lend2:
   push eax
   pop eax
   mov DWORD PTR [ebp-68], eax

   mov eax, 0
   push eax

   mov eax, 0
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse3
   cmp ebx, 0
   je .Lfalse3
   mov eax, 1
   jmp .Lend3
.Lfalse3:
   mov eax, 0
.Lend3:
   push eax
   pop eax
   mov DWORD PTR [ebp-72], eax

   mov eax, 1
   push eax

   mov eax, 514
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue4
   cmp ebx, 0
   jne .Ltrue4
   mov eax, 0
   jmp .Lend4
.Ltrue4:
   mov eax, 1
.Lend4:
   push eax
   pop eax
   mov DWORD PTR [ebp-76], eax

   mov eax, 1
   push eax

   mov eax, 0
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue5
   cmp ebx, 0
   jne .Ltrue5
   mov eax, 0
   jmp .Lend5
.Ltrue5:
   mov eax, 1
.Lend5:
   push eax
   pop eax
   mov DWORD PTR [ebp-80], eax

   mov eax, 0
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue6
   cmp ebx, 0
   jne .Ltrue6
   mov eax, 0
   jmp .Lend6
.Ltrue6:
   mov eax, 1
.Lend6:
   push eax
   pop eax
   mov DWORD PTR [ebp-84], eax

   mov eax, 114
   push eax

   mov eax, 0
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue7
   cmp ebx, 0
   jne .Ltrue7
   mov eax, 0
   jmp .Lend7
.Ltrue7:
   mov eax, 1
.Lend7:
   push eax
   pop eax
   mov DWORD PTR [ebp-88], eax

   mov eax, 114514
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-92], eax

   mov eax, 0
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-96], eax

   mov eax, DWORD PTR [ebp-96]
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax
   pop eax
   mov DWORD PTR [ebp-100], eax

   mov eax, 123
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax

   mov eax, 2
   push eax

   mov eax, 3
   push eax

   pop ebx
   pop eax
   imul eax, ebx
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   sub eax, ebx
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 1
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 43
   push eax

   pop ebx
   pop eax
   imul eax, ebx
   push eax

   pop ebx
   pop eax
   imul eax, ebx
   push eax
   pop eax
   mov DWORD PTR [ebp-104], eax

   mov eax, 3
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, 2
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue8
   cmp ebx, 0
   jne .Ltrue8
   mov eax, 0
   jmp .Lend8
.Ltrue8:
   mov eax, 1
.Lend8:
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse9
   cmp ebx, 0
   je .Lfalse9
   mov eax, 1
   jmp .Lend9
.Lfalse9:
   mov eax, 0
.Lend9:
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 4
   push eax

   mov eax, 5
   push eax

   pop eax
   neg eax
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse10
   cmp ebx, 0
   je .Lfalse10
   mov eax, 1
   jmp .Lend10
.Lfalse10:
   mov eax, 0
.Lend10:
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue11
   cmp ebx, 0
   jne .Ltrue11
   mov eax, 0
   jmp .Lend11
.Ltrue11:
   mov eax, 1
.Lend11:
   push eax
   pop eax
   mov DWORD PTR [ebp-108], eax

   mov eax, DWORD PTR [ebp-72]
   push eax

   mov eax, DWORD PTR [ebp-68]
   push eax

   mov eax, DWORD PTR [ebp-64]
   push eax

   mov eax, DWORD PTR [ebp-60]
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-88]
   push eax

   mov eax, DWORD PTR [ebp-84]
   push eax

   mov eax, DWORD PTR [ebp-80]
   push eax

   mov eax, DWORD PTR [ebp-76]
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-104]
   push eax

   mov eax, DWORD PTR [ebp-100]
   push eax

   mov eax, DWORD PTR [ebp-96]
   push eax

   mov eax, DWORD PTR [ebp-92]
   push eax
   call print4
   add esp, 16

   mov eax, DWORD PTR [ebp-108]
   push eax
   pop eax
   push eax
   push offset format_str
   call printf
   add esp, 8


   mov eax, 3
   push eax

   pop eax
   neg eax
   dec eax
   push eax

   mov eax, 2
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue12
   cmp ebx, 0
   jne .Ltrue12
   mov eax, 0
   jmp .Lend12
.Ltrue12:
   mov eax, 1
.Lend12:
   push eax

   mov eax, 1
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse13
   cmp ebx, 0
   je .Lfalse13
   mov eax, 1
   jmp .Lend13
.Lfalse13:
   mov eax, 0
.Lend13:
   push eax

   pop eax
   cmp eax, 0
   sete al
   movzx eax, al
   push eax

   pop eax
   neg eax
   push eax

   mov eax, 4
   push eax

   mov eax, 5
   push eax

   pop eax
   neg eax
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   je .Lfalse14
   cmp ebx, 0
   je .Lfalse14
   mov eax, 1
   jmp .Lend14
.Lfalse14:
   mov eax, 0
.Lend14:
   push eax

   mov eax, 222
   push eax

   pop ebx
   pop eax
   add eax, ebx
   push eax

   pop ebx
   pop eax
   cmp eax, 0
   jne .Ltrue15
   cmp ebx, 0
   jne .Ltrue15
   mov eax, 0
   jmp .Lend15
.Ltrue15:
   mov eax, 1
.Lend15:
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
