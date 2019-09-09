
test:     file format elf64-x86-64


Disassembly of section .init:

0000000000400418 <_init>:
  400418:	48 83 ec 08          	sub    $0x8,%rsp
  40041c:	48 8b 05 d5 0b 20 00 	mov    0x200bd5(%rip),%rax        # 600ff8 <_DYNAMIC+0x1d0>
  400423:	48 85 c0             	test   %rax,%rax
  400426:	74 05                	je     40042d <_init+0x15>
  400428:	e8 63 00 00 00       	callq  400490 <fopen@plt+0x10>
  40042d:	48 83 c4 08          	add    $0x8,%rsp
  400431:	c3                   	retq   

Disassembly of section .plt:

0000000000400440 <fgetc@plt-0x10>:
  400440:	ff 35 c2 0b 20 00    	pushq  0x200bc2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400446:	ff 25 c4 0b 20 00    	jmpq   *0x200bc4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40044c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400450 <fgetc@plt>:
  400450:	ff 25 c2 0b 20 00    	jmpq   *0x200bc2(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400456:	68 00 00 00 00       	pushq  $0x0
  40045b:	e9 e0 ff ff ff       	jmpq   400440 <_init+0x28>

0000000000400460 <__libc_start_main@plt>:
  400460:	ff 25 ba 0b 20 00    	jmpq   *0x200bba(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400466:	68 01 00 00 00       	pushq  $0x1
  40046b:	e9 d0 ff ff ff       	jmpq   400440 <_init+0x28>

0000000000400470 <memcmp@plt>:
  400470:	ff 25 b2 0b 20 00    	jmpq   *0x200bb2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400476:	68 02 00 00 00       	pushq  $0x2
  40047b:	e9 c0 ff ff ff       	jmpq   400440 <_init+0x28>

0000000000400480 <fopen@plt>:
  400480:	ff 25 aa 0b 20 00    	jmpq   *0x200baa(%rip)        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  400486:	68 03 00 00 00       	pushq  $0x3
  40048b:	e9 b0 ff ff ff       	jmpq   400440 <_init+0x28>

Disassembly of section .plt.got:

0000000000400490 <.plt.got>:
  400490:	ff 25 62 0b 20 00    	jmpq   *0x200b62(%rip)        # 600ff8 <_DYNAMIC+0x1d0>
  400496:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000004004a0 <_start>:
  4004a0:	31 ed                	xor    %ebp,%ebp
  4004a2:	49 89 d1             	mov    %rdx,%r9
  4004a5:	5e                   	pop    %rsi
  4004a6:	48 89 e2             	mov    %rsp,%rdx
  4004a9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4004ad:	50                   	push   %rax
  4004ae:	54                   	push   %rsp
  4004af:	49 c7 c0 c0 06 40 00 	mov    $0x4006c0,%r8
  4004b6:	48 c7 c1 50 06 40 00 	mov    $0x400650,%rcx
  4004bd:	48 c7 c7 e0 05 40 00 	mov    $0x4005e0,%rdi
  4004c4:	e8 97 ff ff ff       	callq  400460 <__libc_start_main@plt>
  4004c9:	f4                   	hlt    
  4004ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004004d0 <deregister_tm_clones>:
  4004d0:	b8 50 10 60 00       	mov    $0x601050,%eax
  4004d5:	48 3d 50 10 60 00    	cmp    $0x601050,%rax
  4004db:	74 13                	je     4004f0 <deregister_tm_clones+0x20>
  4004dd:	b8 00 00 00 00       	mov    $0x0,%eax
  4004e2:	48 85 c0             	test   %rax,%rax
  4004e5:	74 09                	je     4004f0 <deregister_tm_clones+0x20>
  4004e7:	bf 50 10 60 00       	mov    $0x601050,%edi
  4004ec:	ff e0                	jmpq   *%rax
  4004ee:	66 90                	xchg   %ax,%ax
  4004f0:	c3                   	retq   
  4004f1:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4004f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4004fd:	00 00 00 

0000000000400500 <register_tm_clones>:
  400500:	be 50 10 60 00       	mov    $0x601050,%esi
  400505:	48 81 ee 50 10 60 00 	sub    $0x601050,%rsi
  40050c:	48 c1 fe 03          	sar    $0x3,%rsi
  400510:	48 89 f0             	mov    %rsi,%rax
  400513:	48 c1 e8 3f          	shr    $0x3f,%rax
  400517:	48 01 c6             	add    %rax,%rsi
  40051a:	48 d1 fe             	sar    %rsi
  40051d:	74 11                	je     400530 <register_tm_clones+0x30>
  40051f:	b8 00 00 00 00       	mov    $0x0,%eax
  400524:	48 85 c0             	test   %rax,%rax
  400527:	74 07                	je     400530 <register_tm_clones+0x30>
  400529:	bf 50 10 60 00       	mov    $0x601050,%edi
  40052e:	ff e0                	jmpq   *%rax
  400530:	c3                   	retq   
  400531:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400536:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40053d:	00 00 00 

0000000000400540 <__do_global_dtors_aux>:
  400540:	80 3d 09 0b 20 00 00 	cmpb   $0x0,0x200b09(%rip)        # 601050 <__TMC_END__>
  400547:	75 17                	jne    400560 <__do_global_dtors_aux+0x20>
  400549:	55                   	push   %rbp
  40054a:	48 89 e5             	mov    %rsp,%rbp
  40054d:	e8 7e ff ff ff       	callq  4004d0 <deregister_tm_clones>
  400552:	c6 05 f7 0a 20 00 01 	movb   $0x1,0x200af7(%rip)        # 601050 <__TMC_END__>
  400559:	5d                   	pop    %rbp
  40055a:	c3                   	retq   
  40055b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400560:	c3                   	retq   
  400561:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400566:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40056d:	00 00 00 

0000000000400570 <frame_dummy>:
  400570:	eb 8e                	jmp    400500 <register_tm_clones>
  400572:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400579:	00 00 00 
  40057c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400580 <victim_fun>:
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;


void victim_fun(int idx) {
  400580:	55                   	push   %rbp
  400581:	48 89 e5             	mov    %rsp,%rbp
  400584:	48 83 ec 10          	sub    $0x10,%rsp
  400588:	89 7d fc             	mov    %edi,-0x4(%rbp)
    if (idx < array1_size) {                  
  40058b:	8b 7d fc             	mov    -0x4(%rbp),%edi
  40058e:	3b 3c 25 48 10 60 00 	cmp    0x601048,%edi
  400595:	0f 83 3f 00 00 00    	jae    4005da <victim_fun+0x5a>
        temp = memcmp(&temp, array2 + (array1[idx] * 512), 1);
  40059b:	48 63 45 fc          	movslq -0x4(%rbp),%rax
  40059f:	0f b6 0c 05 60 10 60 	movzbl 0x601060(,%rax,1),%ecx
  4005a6:	00 
  4005a7:	c1 e1 09             	shl    $0x9,%ecx
  4005aa:	48 63 c1             	movslq %ecx,%rax
  4005ad:	48 ba 70 10 60 00 00 	movabs $0x601070,%rdx
  4005b4:	00 00 00 
  4005b7:	48 01 c2             	add    %rax,%rdx
  4005ba:	bf 51 10 60 00       	mov    $0x601051,%edi
  4005bf:	b8 01 00 00 00       	mov    $0x1,%eax
  4005c4:	48 89 d6             	mov    %rdx,%rsi
  4005c7:	48 89 c2             	mov    %rax,%rdx
  4005ca:	e8 a1 fe ff ff       	callq  400470 <memcmp@plt>
  4005cf:	41 88 c0             	mov    %al,%r8b
  4005d2:	44 88 04 25 51 10 60 	mov    %r8b,0x601051
  4005d9:	00 
    }
}
  4005da:	48 83 c4 10          	add    $0x10,%rsp
  4005de:	5d                   	pop    %rbp
  4005df:	c3                   	retq   

00000000004005e0 <main>:

int main(int argn, char* args[]) {
  4005e0:	55                   	push   %rbp
  4005e1:	48 89 e5             	mov    %rsp,%rbp
  4005e4:	48 83 ec 20          	sub    $0x20,%rsp
  4005e8:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  4005ef:	89 7d f8             	mov    %edi,-0x8(%rbp)
  4005f2:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    int source;

    FILE *file = fopen("temp.txt", "r");
  4005f6:	48 bf d4 06 40 00 00 	movabs $0x4006d4,%rdi
  4005fd:	00 00 00 
  400600:	48 be dd 06 40 00 00 	movabs $0x4006dd,%rsi
  400607:	00 00 00 
  40060a:	e8 71 fe ff ff       	callq  400480 <fopen@plt>
  40060f:	48 89 45 e0          	mov    %rax,-0x20(%rbp)

    if (file == NULL)
  400613:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  400618:	0f 85 0c 00 00 00    	jne    40062a <main+0x4a>
        return 1;
  40061e:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  400625:	e9 1b 00 00 00       	jmpq   400645 <main+0x65>

    source = fgetc(file);
  40062a:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  40062e:	e8 1d fe ff ff       	callq  400450 <fgetc@plt>
  400633:	89 45 ec             	mov    %eax,-0x14(%rbp)
    victim_fun(source);
  400636:	8b 7d ec             	mov    -0x14(%rbp),%edi
  400639:	e8 42 ff ff ff       	callq  400580 <victim_fun>
    return 0;
  40063e:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
}
  400645:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400648:	48 83 c4 20          	add    $0x20,%rsp
  40064c:	5d                   	pop    %rbp
  40064d:	c3                   	retq   
  40064e:	66 90                	xchg   %ax,%ax

0000000000400650 <__libc_csu_init>:
  400650:	41 57                	push   %r15
  400652:	41 56                	push   %r14
  400654:	41 89 ff             	mov    %edi,%r15d
  400657:	41 55                	push   %r13
  400659:	41 54                	push   %r12
  40065b:	4c 8d 25 b6 07 20 00 	lea    0x2007b6(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400662:	55                   	push   %rbp
  400663:	48 8d 2d b6 07 20 00 	lea    0x2007b6(%rip),%rbp        # 600e20 <__init_array_end>
  40066a:	53                   	push   %rbx
  40066b:	49 89 f6             	mov    %rsi,%r14
  40066e:	49 89 d5             	mov    %rdx,%r13
  400671:	4c 29 e5             	sub    %r12,%rbp
  400674:	48 83 ec 08          	sub    $0x8,%rsp
  400678:	48 c1 fd 03          	sar    $0x3,%rbp
  40067c:	e8 97 fd ff ff       	callq  400418 <_init>
  400681:	48 85 ed             	test   %rbp,%rbp
  400684:	74 20                	je     4006a6 <__libc_csu_init+0x56>
  400686:	31 db                	xor    %ebx,%ebx
  400688:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40068f:	00 
  400690:	4c 89 ea             	mov    %r13,%rdx
  400693:	4c 89 f6             	mov    %r14,%rsi
  400696:	44 89 ff             	mov    %r15d,%edi
  400699:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40069d:	48 83 c3 01          	add    $0x1,%rbx
  4006a1:	48 39 eb             	cmp    %rbp,%rbx
  4006a4:	75 ea                	jne    400690 <__libc_csu_init+0x40>
  4006a6:	48 83 c4 08          	add    $0x8,%rsp
  4006aa:	5b                   	pop    %rbx
  4006ab:	5d                   	pop    %rbp
  4006ac:	41 5c                	pop    %r12
  4006ae:	41 5d                	pop    %r13
  4006b0:	41 5e                	pop    %r14
  4006b2:	41 5f                	pop    %r15
  4006b4:	c3                   	retq   
  4006b5:	90                   	nop
  4006b6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006bd:	00 00 00 

00000000004006c0 <__libc_csu_fini>:
  4006c0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004006c4 <_fini>:
  4006c4:	48 83 ec 08          	sub    $0x8,%rsp
  4006c8:	48 83 c4 08          	add    $0x8,%rsp
  4006cc:	c3                   	retq   
