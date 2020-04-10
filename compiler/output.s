.globl    main
main: 
    pushq   %rbp
    movq    %rsp, %rbp
    movl    $8, -4(%rbp)
    movl    -4(%rbp), %eax
    movl    %eax, -8(%rbp)
    movl    -8(%rbp), %eax
    movl    %eax, %eax
    popq   %rbp
    ret 
