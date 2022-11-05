GLOBAL sys_write
GLOBAL sys_read
GLOBAL sys_printMem
GLOBAL sys_clear
GLOBAL sys_date
GLOBAL sys_sleep
GLOBAL sys_inforeg
GLOBAL divzero
GLOBAL opcode
GLOBAL sys_getLast
GLOBAL sys_snapshotRegs
GLOBAL sys_malloc
GLOBAL sys_free
GLOBAL sys_memStatus
GLOBAL sys_createProcess
GLOBAL sys_exit
GLOBAL sys_getpid
GLOBAL sys_ps
GLOBAL sys_kill
GLOBAL sys_changepriority
GLOBAL sys_changestate
GLOBAL sys_yield
GLOBAL sys_semOpen
GLOBAL sys_semClose
GLOBAL sys_semPost
GLOBAL sys_semWait
GLOBAL sys_getAllSems
GLOBAL sys_createPipe
GLOBAL sys_getAllPipes
GLOBAL sys_openPipe
GLOBAL sys_closeFd
GLOBAL sys_pipeRead
GLOBAL sys_pipeWrite

section .text

sys_write:          ; Los registros de rdi, rsi y rdx ya están cargados por los parámetros de C
    mov rax,2
    int 80h
    ret

sys_read:
    mov rax,1
    int 80h
    ret

sys_printMem:
    mov rax,4
    int 80h
    ret

sys_clear:
    mov rax,3
    int 80h
    ret

sys_date:
    mov rax, 6
    int 80h
    ret

sys_sleep:
    mov rax, 7
    int 80h
    ret

sys_inforeg:
    mov rax, 5
    int 80h
    ret

sys_getLast:
    mov rax, 8
    int 80h
    ret

sys_snapshotRegs:
    mov rax, 9
    int 80h
    ret

sys_malloc:
    mov rax, 10
    int 80h
    ret

sys_free:
    mov rax, 11
    int 80h
    ret

sys_memStatus:
    mov rax, 12
    int 80h
    ret

sys_createProcess:
    mov rax, 13
    int 80h
    ret

sys_exit:
    mov rax, 14
    int 80h
    ret

sys_getpid:
    mov rax, 15
    int 80h
    ret

sys_ps:
  mov rax, 16
  int 80h
  ret

sys_kill:
  mov rax, 17
  int 80h
  ret

sys_changepriority:
  mov rax, 18
  int 80h
  ret

sys_changestate:
  mov rax, 19
  int 80h
  ret

sys_yield:
  mov rax, 20
  int 80h
  ret

sys_semOpen:
  mov rax, 21
  int 80h
  ret

sys_semClose:
  mov rax, 22
  int 80h
  ret

sys_semPost:
  mov rax, 23
  int 80h
  ret

sys_semWait:
  mov rax, 24
  int 80h
  ret

sys_getAllSems:
  mov rax, 25
  int 80h
  ret

sys_createPipe:
  mov rax, 26
  int 80h
  ret

sys_getAllPipes:
  mov rax, 27
  int 80h
  ret

sys_openPipe:
  mov rax, 28
  int 80h
  ret

sys_pipeRead:
  mov rax, 29
  int 80h
  ret

sys_pipeWrite:
  mov rax, 30
  int 80h
  ret

sys_closeFd:
  mov rax, 31
  int 80h
  ret

divzero:
  mov rax, 4
  xor rbx, rbx
  div rbx
  ret

opcode:
  ud2   ;undefined instruction, para tirar el opcode exception.
  ret
