
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
  40045f:	49 c7 c0 b0 06 40 00 	mov    $0x4006b0,%r8
  400466:	48 c7 c1 40 06 40 00 	mov    $0x400640,%rcx
  40046d:	48 c7 c7 d0 05 40 00 	mov    $0x4005d0,%rdi
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
    if (x < array1_size) 
        return 1;
    return 0;
}

void victim_fun(int idx) {
  400530:	55                   	push   %rbp
  400531:	48 89 e5             	mov    %rsp,%rbp
  400534:	48 83 ec 10          	sub    $0x10,%rsp
  400538:	89 7d fc             	mov    %edi,-0x4(%rbp)
    if (is_x_safe(idx)) {                  
  40053b:	48 63 7d fc          	movslq -0x4(%rbp),%rdi
  40053f:	e8 4c 00 00 00       	callq  400590 <is_x_safe>
  400544:	83 f8 00             	cmp    $0x0,%eax
  400547:	0f 84 2f 00 00 00    	je     40057c <victim_fun+0x4c>
        temp &= array2[array1[idx] * 512];
  40054d:	48 63 45 fc          	movslq -0x4(%rbp),%rax
  400551:	0f b6 0c 05 60 10 60 	movzbl 0x601060(,%rax,1),%ecx
  400558:	00 
  400559:	c1 e1 09             	shl    $0x9,%ecx
  40055c:	48 63 c1             	movslq %ecx,%rax
  40055f:	0f b6 0c 05 70 10 60 	movzbl 0x601070(,%rax,1),%ecx
  400566:	00 
  400567:	0f b6 14 25 51 10 60 	movzbl 0x601051,%edx
  40056e:	00 
  40056f:	21 ca                	and    %ecx,%edx
  400571:	40 88 d6             	mov    %dl,%sil
  400574:	40 88 34 25 51 10 60 	mov    %sil,0x601051
  40057b:	00 
    }
}
  40057c:	48 83 c4 10          	add    $0x10,%rsp
  400580:	5d                   	pop    %rbp
  400581:	c3                   	retq   
  400582:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400589:	00 00 00 
  40058c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400590 <is_x_safe>:
unsigned int array1_size = 16;
uint8_t array1[16];
uint8_t array2[256 * 512];
uint8_t temp = 0;

inline static int is_x_safe(size_t x) {
  400590:	55                   	push   %rbp
  400591:	48 89 e5             	mov    %rsp,%rbp
  400594:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
    if (x < array1_size) 
  400598:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  40059c:	8b 04 25 40 10 60 00 	mov    0x601040,%eax
  4005a3:	89 c1                	mov    %eax,%ecx
  4005a5:	48 39 cf             	cmp    %rcx,%rdi
  4005a8:	0f 83 0c 00 00 00    	jae    4005ba <is_x_safe+0x2a>
        return 1;
  4005ae:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  4005b5:	e9 07 00 00 00       	jmpq   4005c1 <is_x_safe+0x31>
    return 0;
  4005ba:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
}
  4005c1:	8b 45 fc             	mov    -0x4(%rbp),%eax
  4005c4:	5d                   	pop    %rbp
  4005c5:	c3                   	retq   
  4005c6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4005cd:	00 00 00 

00000000004005d0 <main>:
    if (is_x_safe(idx)) {                  
        temp &= array2[array1[idx] * 512];
    }
}

int main(int argn, char* args[]) {
  4005d0:	55                   	push   %rbp
  4005d1:	48 89 e5             	mov    %rsp,%rbp
  4005d4:	48 83 ec 20          	sub    $0x20,%rsp
  4005d8:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  4005df:	89 7d f8             	mov    %edi,-0x8(%rbp)
  4005e2:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    int source;

    FILE *file = fopen("temp.txt", "r");
  4005e6:	48 bf c4 06 40 00 00 	movabs $0x4006c4,%rdi
  4005ed:	00 00 00 
  4005f0:	48 be cd 06 40 00 00 	movabs $0x4006cd,%rsi
  4005f7:	00 00 00 
  4005fa:	e8 31 fe ff ff       	callq  400430 <fopen@plt>
  4005ff:	48 89 45 e0          	mov    %rax,-0x20(%rbp)

    if (file == NULL)
  400603:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  400608:	0f 85 0c 00 00 00    	jne    40061a <main+0x4a>
        return 1;
  40060e:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  400615:	e9 1b 00 00 00       	jmpq   400635 <main+0x65>

    source = fgetc(file);
  40061a:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  40061e:	e8 ed fd ff ff       	callq  400410 <fgetc@plt>
  400623:	89 45 ec             	mov    %eax,-0x14(%rbp)
    victim_fun(source);
  400626:	8b 7d ec             	mov    -0x14(%rbp),%edi
  400629:	e8 02 ff ff ff       	callq  400530 <victim_fun>
    return 0;
  40062e:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
}
  400635:	8b 45 fc             	mov    -0x4(%rbp),%eax
  400638:	48 83 c4 20          	add    $0x20,%rsp
  40063c:	5d                   	pop    %rbp
  40063d:	c3                   	retq   
  40063e:	66 90                	xchg   %ax,%ax

0000000000400640 <__libc_csu_init>:
  400640:	41 57                	push   %r15
  400642:	41 56                	push   %r14
  400644:	41 89 ff             	mov    %edi,%r15d
  400647:	41 55                	push   %r13
  400649:	41 54                	push   %r12
  40064b:	4c 8d 25 c6 07 20 00 	lea    0x2007c6(%rip),%r12        # 600e18 <__frame_dummy_init_array_entry>
  400652:	55                   	push   %rbp
  400653:	48 8d 2d c6 07 20 00 	lea    0x2007c6(%rip),%rbp        # 600e20 <__init_array_end>
  40065a:	53                   	push   %rbx
  40065b:	49 89 f6             	mov    %rsi,%r14
  40065e:	49 89 d5             	mov    %rdx,%r13
  400661:	4c 29 e5             	sub    %r12,%rbp
  400664:	48 83 ec 08          	sub    $0x8,%rsp
  400668:	48 c1 fd 03          	sar    $0x3,%rbp
  40066c:	e8 6f fd ff ff       	callq  4003e0 <_init>
  400671:	48 85 ed             	test   %rbp,%rbp
  400674:	74 20                	je     400696 <__libc_csu_init+0x56>
  400676:	31 db                	xor    %ebx,%ebx
  400678:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40067f:	00 
  400680:	4c 89 ea             	mov    %r13,%rdx
  400683:	4c 89 f6             	mov    %r14,%rsi
  400686:	44 89 ff             	mov    %r15d,%edi
  400689:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40068d:	48 83 c3 01          	add    $0x1,%rbx
  400691:	48 39 eb             	cmp    %rbp,%rbx
  400694:	75 ea                	jne    400680 <__libc_csu_init+0x40>
  400696:	48 83 c4 08          	add    $0x8,%rsp
  40069a:	5b                   	pop    %rbx
  40069b:	5d                   	pop    %rbp
  40069c:	41 5c                	pop    %r12
  40069e:	41 5d                	pop    %r13
  4006a0:	41 5e                	pop    %r14
  4006a2:	41 5f                	pop    %r15
  4006a4:	c3                   	retq   
  4006a5:	90                   	nop
  4006a6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4006ad:	00 00 00 

00000000004006b0 <__libc_csu_fini>:
  4006b0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000004006b4 <_fini>:
  4006b4:	48 83 ec 08          	sub    $0x8,%rsp
  4006b8:	48 83 c4 08          	add    $0x8,%rsp
  4006bc:	c3                   	retq   
