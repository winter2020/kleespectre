
test:     file format elf64-x86-64


Disassembly of section .init:

00000000004003e0 <_init>:
  4003e0:	48 83 ec 08          	sub    $0x8,%rsp
  4003e4:	48 8b 05 0d 0c 20 00 	mov    0x200c0d(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  4003eb:	48 85 c0             	test   %rax,%rax
  4003ee:	74 05                	je     4003f5 <_init+0x15>
  4003f0:	e8 4b 00 00 00       	callq  400440 <fopen@plt+0x10>
  4003f5:	48 83 c4 08          	add    $0x8,%rsp
  4003f9:	c3                   	retq   

Disassembly of section .plt:

0000000000400400 <fgetc@plt-0x10>:
  400400:	ff 35 02 0c 20 00    	pushq  0x200c02(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400406:	ff 25 04 0c 20 00    	jmpq   *0x200c04(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40040c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400410 <fgetc@plt>:
  400410:	ff 25 02 0c 20 00    	jmpq   *0x200c02(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400416:	68 00 00 00 00       	pushq  $0x0
  40041b:	e9 e0 ff ff ff       	jmpq   400400 <_init+0x20>

0000000000400420 <__libc_start_main@plt>:
  400420:	ff 25 fa 0b 20 00    	jmpq   *0x200bfa(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400426:	68 01 00 00 00       	pushq  $0x1
  40042b:	e9 d0 ff ff ff       	jmpq   400400 <_init+0x20>

0000000000400430 <fopen@plt>:
  400430:	ff 25 f2 0b 20 00    	jmpq   *0x200bf2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400436:	68 02 00 00 00       	pushq  $0x2
  40043b:	e9 c0 ff ff ff       	jmpq   400400 <_init+0x20>

Disassembly of section .plt.got:

0000000000400440 <.plt.got>:
  400440:	ff 25 b2 0b 20 00    	jmpq   *0x200bb2(%rip)        # 600ff8 <_DYNAMIC+0x1d0>
  400446:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400450 <_start>:
  400450:	31 ed                	xor    %ebp,%ebp
  400452:	49 89 d1             	mov    %rdx,%r9
  400455:	5e                   	pop    %rsi
  400456:	48 89 e2             	mov    %rsp,%rdx
  400459:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40045d:	50                   	push   %rax
  40045e:	54                   	push   %rsp
  40045f:	49 c7 c0 90 06 40 00 	mov    $0x400690,%r8
  400466:	48 c7 c1 20 06 40 00 	mov    $0x400620,%rcx
  40046d:	48 c7 c7 b0 05 40 00 	mov    $0x4005b0,%rdi
  400474:	e8 a7 ff ff ff       	callq  400420 <__libc_start_main@plt>
  400479:	f4                   	hlt    
  40047a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400480 <deregister_tm_clones>:
  400480:	b8 48 10 60 00       	mov    $0x601048,%eax
  400485:	48 3d 48 10 60 00    	cmp    $0x601048,%rax
  40048b:	74 13                	je     4004a0 <deregister_tm_clones+0x20>
  40048d:	b8 00 00 00 00       	mov    $0x0,%eax
  400492:	48 85 c0             	test   %rax,%rax
  400495:	74 09                	je     4004a0 <deregister_tm_clones+0x20>
  400497:	bf 48 10 60 00       	mov    $0x601048,%edi
  40049c:	ff e0                	jmpq   *%rax
  40049e:	66 90                	xchg   %ax,%ax
  4004a0:	c3                   	retq   
  4004a1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004a6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004ad:	00 00 00 

00000000004004b0 <register_tm_clones>:
  4004b0:	be 48 10 60 00       	mov    $0x601048,%esi
  4004b5:	48 81 ee 48 10 60 00 	sub    $0x601048,%rsi
  4004bc:	48 c1 fe 03          	sar    $0x3,%rsi
  4004c0:	48 89 f0             	mov    %rsi,%rax
  4004c3:	48 c1 e8 3f          	shr    $0x3f,%rax
  4004c7:	48 01 c6             	add    %rax,%rsi
  4004ca:	48 d1 fe             	sar    %rsi
  4004cd:	74 11                	je     4004e0 <register_tm_clones+0x30>
  4004cf:	b8 00 00 00 00       	mov    $0x0,%eax
  4004d4:	48 85 c0             	test   %rax,%rax
  4004d7:	74 07                	je     4004e0 <register_tm_clones+0x30>
  4004d9:	bf 48 10 60 00       	mov    $0x601048,%edi
  4004de:	ff e0                	jmpq   *%rax
  4004e0:	c3                   	retq   
  4004e1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004e6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004ed:	00 00 00 

00000000004004f0 <__do_global_dtors_aux>:
  4004f0:	80 3d 59 0b 20 00 00 	cmpb   $0x0,0x200b59(%rip)        # 601050 <completed.7931>
  4004f7:	75 17                	jne    400510 <__do_global_dtors_aux+0x20>
  4004f9:	55                   	push   %rbp
  4004fa:	48 89 e5             	mov    %rsp,%rbp
  4004fd:	e8 7e ff ff ff       	callq  400480 <deregister_tm_clones>
  400502:	c6 05 47 0b 20 00 01 	movb   $0x1,0x200b47(%rip)        # 601050 <completed.7931>
  400509:	5d                   	pop    %rbp
  40050a:	c3                   	retq   
  40050b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400510:	c3                   	retq   
  400511:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400516:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40051d:	00 00 00 

0000000000400520 <frame_dummy>:
  400520:	eb 8e                	jmp    4004b0 <register_tm_clones>
  400522:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400529:	00 00 00 
  40052c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400530 <victim_fun>:

inline static void leak_byte_local_function(uint8_t k) {
    temp &= array2[(k)* 512]; 
}

void victim_fun(int idx) {
  400530:	55                   	push   %rbp
  400531:	48 89 e5             	mov    %rsp,%rbp
  400534:	48 83 ec 10          	sub    $0x10,%rsp
  400538:	89 7d fc             	mov    %edi,-0x4(%rbp)
    if (idx < array1_size) {                  
  40053b:	8b 7d fc             	mov    -0x4(%rbp),%edi
  40053e:	3b 3c 25 40 10 60 00 	cmp    0x601040,%edi
  400545:	0f 83 11 00 00 00    	jae    40055c <victim_fun+0x2c>
        leak_byte_local_function(array1[idx]);
  40054b:	48 63 45 fc          	movslq -0x4(%rbp),%rax
  40054f:	0f b6 3c 05 60 10 60 	movzbl 0x601060(,%rax,1),%edi
  400556:	00 
  400557:	e8 14 00 00 00       	callq  400570 <leak_byte_local_function>
    }
}
  40055c:	48 83 c4 10          	add    $0x10,%rsp
  400560:	5d                   	pop    %rbp
  400561:	c3                   	retq   
  400562:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400569:	00 00 00 
  40056c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400570 <leak_byte_local_function>:
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


inline static void leak_byte_local_function(uint8_t k) {
  400570:	55                   	push   %rbp
  400571:	48 89 e5             	mov    %rsp,%rbp
  400574:	40 88 f8             	mov    %dil,%al
  400577:	88 45 ff             	mov    %al,-0x1(%rbp)
    temp &= array2[(k)* 512]; 
  40057a:	0f b6 7d ff          	movzbl -0x1(%rbp),%edi
  40057e:	c1 e7 09             	shl    $0x9,%edi
  400581:	48 63 cf             	movslq %edi,%rcx
  400584:	0f b6 3c 0d 70 10 60 	movzbl 0x601070(,%rcx,1),%edi
  40058b:	00 
  40058c:	0f b6 14 25 51 10 60 	movzbl 0x601051,%edx
  400593:	00 
  400594:	21 fa                	and    %edi,%edx
  400596:	88 d0                	mov    %dl,%al
  400598:	88 04 25 51 10 60 00 	mov    %al,0x601051
}
  40059f:	5d                   	pop    %rbp
  4005a0:	c3                   	retq   
  4005a1:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4005a8:	00 00 00 
  4005ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004005b0 <main>:
    if (idx < array1_size) {                  
        leak_byte_local_function(array1[idx]);
    }
}

int main(int argn, char* args[]) {
  4005b0:	55                   	push   %rbp
  4005b1:	48 89 e5             	mov    %rsp,%rbp
  4005b4:	48 83 ec 20          	sub    $0x20,%rsp
  4005b8:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  4005bf:	89 7d f8             	mov    %edi,-0x8(%rbp)
  4005c2:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    int source;

    FILE *file = fopen("temp.txt", "r");
  4005c6:	48 bf a4 06 40 00 00 	movabs $0x4006a4,%rdi
  4005cd:	00 00 00 
  4005d0:	48 be ad 06 40 00 00 	movabs $0x4006ad,%rsi
  4005d7:	00 00 00 
  4005da:	e8 51 fe ff ff       	callq  400430 <fopen@plt>
  4005df:	48 89 45 e0          	mov    %rax,-0x20(%rbp)

    if (file == NULL)
  4005e3:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  4005e8:	0f 85 0c 00 00 00    	jne    4005fa <main+0x4a>
        return 1;
  4005ee:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  4005f5:	e9 1b 00 00 00       	jmpq   400615 <main+0x65>

    source = fgetc(file);
  4005fa:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  4005fe:	e8 0d fe ff ff       	callq  400410 <fgetc@plt>
  400603:	89 45 ec             	mov    %eax,-0x14(%rbp)
    victim_fun(source);
  400606:	8b 7d ec             	mov    -0x14(%rbp),%edi
  400609:	e8 22 ff ff ff       	callq  400530 <victim_fun>
    return 0;
  40060e:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
}
  400615:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400618:	48 83 c4 20          	add    $0x20,%rsp
  40061c:	5d                   	pop    %rbp
  40061d:	c3                   	retq   
  40061e:	66 90                	xchg   %ax,%ax

0000000000400620 <__libc_csu_init>:
  400620:	41 57                	push   %r15
  400622:	41 56                	push   %r14
  400624:	41 89 ff             	mov    %edi,%r15d
  400627:	41 55                	push   %r13
  400629:	41 54                	push   %r12
  40062b:	4c 8d 25 e6 07 20 00 	lea    0x2007e6(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400632:	55                   	push   %rbp
  400633:	48 8d 2d e6 07 20 00 	lea    0x2007e6(%rip),%rbp        # 600e20 <__init_array_end>
  40063a:	53                   	push   %rbx
  40063b:	49 89 f6             	mov    %rsi,%r14
  40063e:	49 89 d5             	mov    %rdx,%r13
  400641:	4c 29 e5             	sub    %r12,%rbp
  400644:	48 83 ec 08          	sub    $0x8,%rsp
  400648:	48 c1 fd 03          	sar    $0x3,%rbp
  40064c:	e8 8f fd ff ff       	callq  4003e0 <_init>
  400651:	48 85 ed             	test   %rbp,%rbp
  400654:	74 20                	je     400676 <__libc_csu_init+0x56>
  400656:	31 db                	xor    %ebx,%ebx
  400658:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40065f:	00 
  400660:	4c 89 ea             	mov    %r13,%rdx
  400663:	4c 89 f6             	mov    %r14,%rsi
  400666:	44 89 ff             	mov    %r15d,%edi
  400669:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40066d:	48 83 c3 01          	add    $0x1,%rbx
  400671:	48 39 eb             	cmp    %rbp,%rbx
  400674:	75 ea                	jne    400660 <__libc_csu_init+0x40>
  400676:	48 83 c4 08          	add    $0x8,%rsp
  40067a:	5b                   	pop    %rbx
  40067b:	5d                   	pop    %rbp
  40067c:	41 5c                	pop    %r12
  40067e:	41 5d                	pop    %r13
  400680:	41 5e                	pop    %r14
  400682:	41 5f                	pop    %r15
  400684:	c3                   	retq   
  400685:	90                   	nop
  400686:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40068d:	00 00 00 

0000000000400690 <__libc_csu_fini>:
  400690:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400694 <_fini>:
  400694:	48 83 ec 08          	sub    $0x8,%rsp
  400698:	48 83 c4 08          	add    $0x8,%rsp
  40069c:	c3                   	retq   
