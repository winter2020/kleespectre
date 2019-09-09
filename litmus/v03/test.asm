
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

0000000000400440 <printf@plt-0x10>:
  400440:	ff 35 c2 0b 20 00    	pushq  0x200bc2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400446:	ff 25 c4 0b 20 00    	jmpq   *0x200bc4(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40044c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400450 <printf@plt>:
  400450:	ff 25 c2 0b 20 00    	jmpq   *0x200bc2(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400456:	68 00 00 00 00       	pushq  $0x0
  40045b:	e9 e0 ff ff ff       	jmpq   400440 <_init+0x28>

0000000000400460 <fgetc@plt>:
  400460:	ff 25 ba 0b 20 00    	jmpq   *0x200bba(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400466:	68 01 00 00 00       	pushq  $0x1
  40046b:	e9 d0 ff ff ff       	jmpq   400440 <_init+0x28>

0000000000400470 <__libc_start_main@plt>:
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
  4004af:	49 c7 c0 00 07 40 00 	mov    $0x400700,%r8
  4004b6:	48 c7 c1 90 06 40 00 	mov    $0x400690,%rcx
  4004bd:	48 c7 c7 00 06 40 00 	mov    $0x400600,%rdi
  4004c4:	e8 a7 ff ff ff       	callq  400470 <__libc_start_main@plt>
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

static __attribute__ ((noinline)) void leakByteNoinlineFunction(uint8_t k) { 
    temp &= array2[k* 512]; 
}

void victim_fun(size_t x) {
  400580:	55                   	push   %rbp
  400581:	48 89 e5             	mov    %rsp,%rbp
  400584:	48 83 ec 10          	sub    $0x10,%rsp
  400588:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
         if (x < array1_size)
  40058c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  400590:	8b 04 25 48 10 60 00 	mov    0x601048,%eax
  400597:	89 c1                	mov    %eax,%ecx
  400599:	48 39 cf             	cmp    %rcx,%rdi
  40059c:	0f 83 11 00 00 00    	jae    4005b3 <victim_fun+0x33>
                leakByteNoinlineFunction(array1[x]);
  4005a2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4005a6:	0f b6 3c 05 60 10 60 	movzbl 0x601060(,%rax,1),%edi
  4005ad:	00 
  4005ae:	e8 0d 00 00 00       	callq  4005c0 <leakByteNoinlineFunction>
}
  4005b3:	48 83 c4 10          	add    $0x10,%rsp
  4005b7:	5d                   	pop    %rbp
  4005b8:	c3                   	retq   
  4005b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004005c0 <leakByteNoinlineFunction>:
struct timespec time_start, time_end;
size_t time_diff;



static __attribute__ ((noinline)) void leakByteNoinlineFunction(uint8_t k) { 
  4005c0:	55                   	push   %rbp
  4005c1:	48 89 e5             	mov    %rsp,%rbp
  4005c4:	40 88 f8             	mov    %dil,%al
  4005c7:	88 45 ff             	mov    %al,-0x1(%rbp)
    temp &= array2[k* 512]; 
  4005ca:	0f b6 7d ff          	movzbl -0x1(%rbp),%edi
  4005ce:	c1 e7 09             	shl    $0x9,%edi
  4005d1:	48 63 cf             	movslq %edi,%rcx
  4005d4:	0f b6 3c 0d 90 10 60 	movzbl 0x601090(,%rcx,1),%edi
  4005db:	00 
  4005dc:	0f b6 14 25 51 10 60 	movzbl 0x601051,%edx
  4005e3:	00 
  4005e4:	21 fa                	and    %edi,%edx
  4005e6:	88 d0                	mov    %dl,%al
  4005e8:	88 04 25 51 10 60 00 	mov    %al,0x601051
}
  4005ef:	5d                   	pop    %rbp
  4005f0:	c3                   	retq   
  4005f1:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4005f8:	00 00 00 
  4005fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400600 <main>:
void victim_fun(size_t x) {
         if (x < array1_size)
                leakByteNoinlineFunction(array1[x]);
}

int main(int argn, char* args[]) {
  400600:	55                   	push   %rbp
  400601:	48 89 e5             	mov    %rsp,%rbp
  400604:	48 83 ec 30          	sub    $0x30,%rsp
  400608:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  40060f:	89 7d f8             	mov    %edi,-0x8(%rbp)
  400612:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    int source;

    FILE *file = fopen("temp.txt", "r");
  400616:	48 bf 14 07 40 00 00 	movabs $0x400714,%rdi
  40061d:	00 00 00 
  400620:	48 be 1d 07 40 00 00 	movabs $0x40071d,%rsi
  400627:	00 00 00 
  40062a:	e8 51 fe ff ff       	callq  400480 <fopen@plt>
  40062f:	48 89 45 e0          	mov    %rax,-0x20(%rbp)

    if (file == NULL) {
  400633:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  400638:	0f 85 20 00 00 00    	jne    40065e <main+0x5e>
        printf("No file!");
  40063e:	48 bf 1f 07 40 00 00 	movabs $0x40071f,%rdi
  400645:	00 00 00 
  400648:	b0 00                	mov    $0x0,%al
  40064a:	e8 01 fe ff ff       	callq  400450 <printf@plt>
        return 0;
  40064f:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  400656:	89 45 dc             	mov    %eax,-0x24(%rbp)
  400659:	e9 1c 00 00 00       	jmpq   40067a <main+0x7a>
    }
    source = fgetc(file);
  40065e:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  400662:	e8 f9 fd ff ff       	callq  400460 <fgetc@plt>
  400667:	89 45 ec             	mov    %eax,-0x14(%rbp)
    victim_fun(source);
  40066a:	48 63 7d ec          	movslq -0x14(%rbp),%rdi
  40066e:	e8 0d ff ff ff       	callq  400580 <victim_fun>
    return 0;
  400673:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
}
  40067a:	8b 45 fc             	mov    -0x4(%rbp),%eax
  40067d:	48 83 c4 30          	add    $0x30,%rsp
  400681:	5d                   	pop    %rbp
  400682:	c3                   	retq   
  400683:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40068a:	00 00 00 
  40068d:	0f 1f 00             	nopl   (%rax)

0000000000400690 <__libc_csu_init>:
  400690:	41 57                	push   %r15
  400692:	41 56                	push   %r14
  400694:	41 89 ff             	mov    %edi,%r15d
  400697:	41 55                	push   %r13
  400699:	41 54                	push   %r12
  40069b:	4c 8d 25 76 07 20 00 	lea    0x200776(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  4006a2:	55                   	push   %rbp
  4006a3:	48 8d 2d 76 07 20 00 	lea    0x200776(%rip),%rbp        # 600e20 <__init_array_end>
  4006aa:	53                   	push   %rbx
  4006ab:	49 89 f6             	mov    %rsi,%r14
  4006ae:	49 89 d5             	mov    %rdx,%r13
  4006b1:	4c 29 e5             	sub    %r12,%rbp
  4006b4:	48 83 ec 08          	sub    $0x8,%rsp
  4006b8:	48 c1 fd 03          	sar    $0x3,%rbp
  4006bc:	e8 57 fd ff ff       	callq  400418 <_init>
  4006c1:	48 85 ed             	test   %rbp,%rbp
  4006c4:	74 20                	je     4006e6 <__libc_csu_init+0x56>
  4006c6:	31 db                	xor    %ebx,%ebx
  4006c8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4006cf:	00 
  4006d0:	4c 89 ea             	mov    %r13,%rdx
  4006d3:	4c 89 f6             	mov    %r14,%rsi
  4006d6:	44 89 ff             	mov    %r15d,%edi
  4006d9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006dd:	48 83 c3 01          	add    $0x1,%rbx
  4006e1:	48 39 eb             	cmp    %rbp,%rbx
  4006e4:	75 ea                	jne    4006d0 <__libc_csu_init+0x40>
  4006e6:	48 83 c4 08          	add    $0x8,%rsp
  4006ea:	5b                   	pop    %rbx
  4006eb:	5d                   	pop    %rbp
  4006ec:	41 5c                	pop    %r12
  4006ee:	41 5d                	pop    %r13
  4006f0:	41 5e                	pop    %r14
  4006f2:	41 5f                	pop    %r15
  4006f4:	c3                   	retq   
  4006f5:	90                   	nop
  4006f6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006fd:	00 00 00 

0000000000400700 <__libc_csu_fini>:
  400700:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000400704 <_fini>:
  400704:	48 83 ec 08          	sub    $0x8,%rsp
  400708:	48 83 c4 08          	add    $0x8,%rsp
  40070c:	c3                   	retq   
