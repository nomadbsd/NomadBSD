\ Copyright (c) 2003 Scott Long <scottl@freebsd.org>
\ Copyright (c) 2003 Aleksander Fafula <alex@fafula.com>
\ All rights reserved.
\
\ Redistribution and use in source and binary forms, with or without
\ modification, are permitted provided that the following conditions
\ are met:
\ 1. Redistributions of source code must retain the above copyright
\    notice, this list of conditions and the following disclaimer.
\ 2. Redistributions in binary form must reproduce the above copyright
\    notice, this list of conditions and the following disclaimer in the
\    documentation and/or other materials provided with the distribution.
\
\ THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
\ ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
\ IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
\ ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
\ FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
\ DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
\ OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
\ HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
\ LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
\ OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
\ SUCH DAMAGE.
\
\ $FreeBSD: src/sys/boot/forth/beastie.4th,v 1.10.2.2 2006/04/04 17:03:44 emax Exp $

marker task-beastie.4th

include /boot/screen.4th
include /boot/frames.4th

hide

variable menuidx
variable menubllt
variable menuX
variable menuY
variable promptwidth

variable bootkey
variable bootacpikey
variable bootsafekey
variable bootverbosekey
variable bootsinglekey
variable defaultskey
variable escapekey
variable rebootkey

2variable xy-acpi
2variable xy-safe
2variable xy-single
2variable xy-verbose

variable default-acpi
variable default-safe
variable default-single
variable default-verbose

variable current-acpi
variable current-safe
variable current-single
variable current-verbose

46 constant dot

\ The BSD Daemon.  He is 19 rows high and 34 columns wide
: beastie-logo ( x y -- )
2dup at-xy ."               [1;31m,        ," 1+
2dup at-xy ."              /(        )`" 1+
2dup at-xy ."              \ \___   / |" 1+
2dup at-xy ."              /- [37m_[31m  `-/  '" 1+
2dup at-xy ."             ([37m/\/ \[31m \   /\" 1+
2dup at-xy ."             [37m/ /   |[31m `    \" 1+
2dup at-xy ."             [34mO O   [37m) [31m/    |" 1+
2dup at-xy ."             [37m`-^--'[31m`<     '" 1+
2dup at-xy ."            (_.)  _  )   /" 1+
2dup at-xy ."             `.___/`    /       " 1+
2dup at-xy ."               `-----' /" 1+
2dup at-xy ."  [33m<----.[31m     __ / __   \" 1+
2dup at-xy ."  [33m<----|====[31mO)))[33m==[31m) \) /[33m====|" 1+
2dup at-xy ."  [33m<----'[31m    `--' `.__,' \" 1+
2dup at-xy ."               |        |" 1+
2dup at-xy ."                \       /       /\" 1+
2dup at-xy ."           [36m______[31m( (_  / \______/" 1+
2dup at-xy ."         [36m,'  ,-----'   |" 1+
at-xy ."         `--{__________) [0m"
;

: beastiebw-logo ( x y -- )
	2dup at-xy ."              ,        ," 1+
	2dup at-xy ."             /(        )`" 1+
	2dup at-xy ."             \ \___   / |" 1+
	2dup at-xy ."             /- _  `-/  '" 1+
	2dup at-xy ."            (/\/ \ \   /\" 1+
	2dup at-xy ."            / /   | `    \" 1+
	2dup at-xy ."            O O   ) /    |" 1+
	2dup at-xy ."            `-^--'`<     '" 1+
	2dup at-xy ."           (_.)  _  )   /" 1+
	2dup at-xy ."            `.___/`    /" 1+
	2dup at-xy ."              `-----' /" 1+
	2dup at-xy ." <----.     __ / __   \" 1+
	2dup at-xy ." <----|====O)))==) \) /====" 1+
	2dup at-xy ." <----'    `--' `.__,' \" 1+
	2dup at-xy ."              |        |" 1+
	2dup at-xy ."               \       /       /\" 1+
	2dup at-xy ."          ______( (_  / \______/" 1+
	2dup at-xy ."        ,'  ,-----'   |" 1+
	     at-xy ."        `--{__________)"
;

: fbsdbw-logo ( x y -- )
	2dup at-xy ."      ______" 1+
	2dup at-xy ."     |  ____| __ ___  ___ " 1+
	2dup at-xy ."     | |__ | '__/ _ \/ _ \" 1+
	2dup at-xy ."     |  __|| | |  __/  __/" 1+
	2dup at-xy ."     | |   | | |    |    |" 1+
	2dup at-xy ."     |_|   |_|  \___|\___|" 1+
	2dup at-xy ."      ____   _____ _____" 1+
	2dup at-xy ."     |  _ \ / ____|  __ \" 1+
	2dup at-xy ."     | |_) | (___ | |  | |" 1+
	2dup at-xy ."     |  _ < \___ \| |  | |" 1+
	2dup at-xy ."     | |_) |____) | |__| |" 1+
	2dup at-xy ."     |     |      |      |" 1+
	     at-xy ."     |____/|_____/|_____/"
;

: print-logo ( x y -- )
	s" loader_logo" getenv
	dup -1 = if
		drop
		fbsdbw-logo
		exit
	then
	2dup s" fbsdbw" compare-insensitive 0= if
		2drop
		fbsdbw-logo
		exit
	then
	2dup s" beastiebw" compare-insensitive 0= if
		2drop
		beastiebw-logo
		exit
	then
	2dup s" beastie" compare-insensitive 0= if
		2drop
		beastie-logo
		exit
	then
	2dup s" none" compare-insensitive 0= if
		2drop
		\ no logo
		exit
	then
	2drop
	fbsdbw-logo
;

: qseconds ( -- n )
	-1
	begin 1 while
		seconds
		86400 mod
		swap over = if
			exit
		then
	repeat
;

: acpienabled? ( -- flag )
	s" acpi_load" getenv
	dup -1 = if
		drop false exit
	then
	s" YES" compare-insensitive 0<> if
		false exit
	then
	s" hint.acpi.0.disabled" getenv
	dup -1 <> if
		s" 0" compare 0<> if
			false exit
		then
	else
		drop
	then
	true
;

: printmenuitem ( -- n )
	menuidx @
	1+ dup
	menuidx !
	menuY @ + dup menuX @ swap at-xy
	menuidx @ .
	menuX @ 1+ swap at-xy
	menubllt @ emit
	menuidx @ 48 +
;

: beastie-text-menu ( -- )
	0 menuidx !
	dot menubllt !
	8 menuY !
	5 menuX !
	clear
	46 4 print-logo
	42 20 2 2 box
	13 6 at-xy ." Welcome to FreeBSD!"
	printmenuitem ."  Boot FreeBSD [default]" bootkey !
	s" arch-i386" environment? if
		drop
		printmenuitem ."  Boot FreeBSD with ACPI " bootacpikey !
		acpienabled? if
			." disabled"
		else
			." enabled"
		then
	else
		-2 bootacpikey !
	then
	printmenuitem ."  Boot FreeBSD in Safe Mode" bootsafekey !
	printmenuitem ."  Boot FreeBSD in single user mode" bootsinglekey !
	printmenuitem ."  Boot FreeBSD with verbose logging" bootverbosekey !
	printmenuitem ."  Escape to loader prompt" escapekey !
	printmenuitem ."  Reboot" rebootkey !
	menuX @ 20 at-xy
	." Select option, [Enter] for default"
	menuX @ 21 at-xy
	s" or [Space] to pause timer    " dup 2 - promptwidth !
	type
;

: tkey-text ( delay delay -- delay key )
	qseconds +
	begin 1 while
		over 0<> if
			dup qseconds u< if
				drop
				-1
				exit
			then
			menuX @ promptwidth @ + 21 at-xy dup qseconds - .
		then
		key? if
			drop
			key
			exit
		then
	50 ms
	repeat
;

: beastie-text-start
	beastie-text-menu
	s" autoboot_delay" getenv
	dup -1 = if
		drop
		10
	else
		0 0 2swap >number drop drop drop
	then
	begin
		dup tkey-text
		0 25 at-xy
		dup 32 = if nip 0 swap then
		dup -1 = if 0 boot then
		dup 13 = if 0 boot then
		dup bootkey @ = if 0 boot then
		dup bootacpikey @ = if
			acpienabled? if
				s" acpi_load" unsetenv
				s" 1" s" hint.acpi.0.disabled" setenv
				s" 1" s" loader.acpi_disabled_by_user" setenv
			else
				s" YES" s" acpi_load" setenv
				s" 0" s" hint.acpi.0.disabled" setenv
			then
			0 boot
		then
		dup bootsafekey @ = if
			s" arch-i386" environment? if
				drop
				s" acpi_load" unsetenv
				s" 1" s" hint.acpi.0.disabled" setenv
				s" 1" s" loader.acpi_disabled_by_user" setenv
				s" 1" s" hint.apic.0.disabled" setenv
			then
			s" 0" s" hw.ata.ata_dma" setenv
			s" 0" s" hw.ata.atapi_dma" setenv
			s" 0" s" hw.ata.wc" setenv
			s" 0" s" hw.eisa_slots" setenv
			s" 1" s" hint.kbdmux.0.disabled" setenv
			0 boot
		then
		dup bootverbosekey @ = if
			s" YES" s" boot_verbose" setenv
			0 boot
		then
		dup bootsinglekey @ = if
			s" YES" s" boot_single" setenv
			0 boot
		then
		dup escapekey @ = if
			2drop
			s" NO" s" autoboot_delay" setenv
			exit
		then
		rebootkey @ = if 0 reboot then
	again
;

vcheck? [if]

: rgb-variable ( -- ) ( -- addr )
	create 3 cells allot
;

rgb-variable fgcolor
rgb-variable bgcolor
rgb-variable litcolor
rgb-variable dimcolor

: use-color ( addr -- )
	dup @ swap
	1 cells +
	dup @ swap
	1 cells +
	@
	vrgbcolor
;

: store-color ( r g b addr -- )
	3 roll over !
	1 cells + rot over !
	1 cells + !
;

: refresh-option ( y x n -- )
	bgcolor use-color
	128 2over rot vemit 2drop
	if
		litcolor use-color
		128 vemit
	else
		dimcolor use-color
		129 vemit
	then
	2drop
;

: refresh-all-options ( -- )
	xy-acpi 2@    current-acpi @    refresh-option
	xy-safe 2@    current-safe @    refresh-option
	xy-single 2@  current-single @  refresh-option
	xy-verbose 2@ current-verbose @ refresh-option
;

: nl ( y x inc -- y' x y' x )	\ next line
	rot + swap 2dup
;

: itab ( y x -- x y x )		\ record current x position
	swap over
;

: tab ( x y x' -- y x'' )	\ advance to next tab position
	drop swap 24 +
;

: string++ ( addr count -- addr+1 count-1 )
	1 - swap 1 + swap
;

: next-digit ( addr1 count1 -- addr2 count2 )	\ skip to next digit
	begin
		dup 0= if
			exit
		then

		over c@
		dup [char] 0 <
		swap [char] 9 >
		or
	while
		string++
	repeat
;

: get-xy-var ( defy defx addr count -- y x )	\ parse var into xy pair
	getenv
	dup -1 = if
		drop
	else
		0 0 2swap >number rot drop

		next-digit
		dup 0= if
			2drop swap drop
			exit
		then

		0 0 2swap >number 2drop drop
		2swap 2drop
		swap
	then
;

: get-rgb-var ( defr defg defb addr count -- r g b ) \ parse var into rgb tuple
	getenv
	dup -1 = if
		drop
	else
		0 0 2swap >number rot drop
		5 roll drop	\ remove defr
		next-digit
		dup 0= if
			2drop rot rot
			exit
		then
		0 0 2swap >number rot drop
		5 roll drop	\ remove defg
		next-digit
		dup 0= if
			2drop rot
			exit
		then
		0 0 2swap >number 2drop drop
		3 roll drop	\ remove defb
	then
;

: init-colors ( -- )
	255 255 255 s" theme_fgcolor"  get-rgb-var fgcolor  store-color
	0   0   0   s" theme_bgcolor"  get-rgb-var bgcolor  store-color
	255 64  32  s" theme_litcolor" get-rgb-var litcolor store-color
	128 64  32  s" theme_dimcolor" get-rgb-var dimcolor store-color
;

: init-option ( y x addr count - y x )	\ store xy position and emit bullet
	2over 2swap 2! 129 vemit 32 vemit
;

: default-theme s" /boot/themes/default/theme.conf" ;
: default-font  s" /boot/themes/default/stdfont" ;
: default-bg    s" /boot/themes/default/bglogo.pcx" ;

: load-theme ( -- font bg )
	s" beastie_theme" getenv
	dup -1 = if
		drop
		default-theme
	then
	read-conf

	s" theme_font" getenv
	dup -1 = if
		drop
		default-font
	then
	vloadfont
	dup 0= if
		drop
		." Cannot load font!"
		\ XXXXXX
		\ 5000 ms
		key drop
		-1 exit
	then
	dup vusefont

	s" theme_background" getenv
	dup -1 = if
		drop
		default-bg
	then
	vloadpcx
	dup 0= if
		drop
		." Cannot load PCX!"
		\ XXXXXX
		\ 5000 ms
		key drop
		vfreefont
		-1 exit
	then
;

: beastie-gfx-menu ( -- success )

	\ Note:  Load files while still in text mode, for two reasons:
	\ 1. twiddle() (called by I/O) interferes with graphics mode.
	\ 2. If loading fails, we can fall back to beastie-text-menu
	\    without switching back and forth to/from graphics mode.

	load-theme
	dup -1 = if
		drop false exit
	then

	vmode
	dup
	0 0 vshowpcx
	vfreepcx
	drop	\ keep font

	init-colors

	fgcolor use-color
	10 64 s" theme_options_xy" get-xy-var
	v" Boot options:   "
	2dup  xy-acpi    init-option v" 1  Disable ACPI" 2drop
	16 nl xy-safe    init-option v" 2  Enable safe mode" 2drop
	16 nl xy-single  init-option v" 3  Enter single user mode" 2drop
	16 nl xy-verbose init-option v" 4  Enable verbose logging" 2drop
	2drop
	82 64 s" theme_actions_xy" get-xy-var
	v" Actions:   "
	2dup  itab v" B" tab v" Boot FreeBSD with above options" 2drop
	16 nl itab v" D" tab v" Restore default options" 2drop
	16 nl itab v" L" tab v" Escape to loader prompt" 2drop
	16 nl itab v" R" tab v" Reboot" 2drop
	2drop
	\ XXXXXX
	49 bootacpikey !
	50 bootsafekey !
	51 bootsinglekey !
	52 bootverbosekey !
	98 bootkey !
	100 defaultskey !
	108 escapekey !
	114 rebootkey !
	true
;

: tkey-gfx ( delay delay -- delay key )
	qseconds +
	begin 1 while
		over 0<> if
			dup qseconds u< if
				drop
				-1
				exit
			then

			dup qseconds - dup
			bgcolor use-color
			0 0 16 32 2over vrect
			fgcolor use-color
			rot 0 <# #s #> vtext 2drop

			\ 8 * 2 pick /
			\ dup 0< if drop 0 then
			\ 255 swap rshift

			\ 32 1 do
			\ 	i over 80 16 vcirclearc
			\ loop

			drop
		then
		key? if
			drop
			key
			exit
		then
		50 ms
	repeat
;

: toggle ( y x var -- )
	dup @ 0= dup rot !
	refresh-option
;

: beastie-gfx-start ( -- success )
	beastie-gfx-menu 0= if
		false exit
	then

	acpienabled? 0= dup current-acpi ! default-acpi !
	false dup current-safe ! default-safe !
	false dup current-single ! default-single !
	false dup current-verbose ! default-verbose !
	refresh-all-options

	s" autoboot_delay" getenv
	dup -1 = if
		drop
		10
	else
		0 0 2swap >number 2drop drop
	then

	begin
		dup tkey-gfx

		dup -1 =
		over 13 = or
		over bootkey @ = or if
			current-acpi @ if
				s" acpi_load" unsetenv
				s" 1" s" hint.acpi.0.disabled" setenv
				s" 1" s" loader.acpi_disabled_by_user" setenv
			else
				s" YES" s" acpi_load" setenv
				s" 0" s" hint.acpi.0.disabled" setenv
			then
			current-safe @ if
				s" arch-i386" environment? if
					drop
					s" acpi_load" unsetenv
					s" 1" s" hint.acpi.0.disabled" setenv
					s" 1" s" loader.acpi_disabled_by_user" setenv
					s" 1" s" hint.apic.0.disabled" setenv
				then
				s" 0" s" hw.ata.ata_dma" setenv
				s" 0" s" hw.ata.atapi_dma" setenv
				s" 0" s" hw.ata.wc" setenv
				s" 0" s" hw.eisa_slots" setenv
				s" 1" s" hint.kbdmux.0.disabled" setenv
			then
			current-single @ if
				s" YES" s" boot_single" setenv
			then
			current-verbose @ if
				s" YES" s" boot_verbose" setenv
			then
			vreset
			0 boot
		then

		\ For debugging only: display key code
		\ dup
		\ bgcolor use-color
		\ 32 0 16 32 2over vrect
		\ fgcolor use-color
		\ rot 0 <# #s #> vtext 2drop

		dup bootacpikey @ = if
			xy-acpi 2@ current-acpi toggle
		then

		dup bootsafekey @ = if
			xy-safe 2@ current-safe toggle
		then

		dup bootsinglekey @ = if
			xy-single 2@ current-single toggle
		then

		dup bootverbosekey @ = if
			xy-verbose 2@ current-verbose toggle
		then

		dup defaultskey @ = if
			default-acpi @ current-acpi !
			default-safe @ current-safe !
			default-single @ current-single !
			default-verbose @ current-verbose !
			refresh-all-options
		then

		dup escapekey @ = if
			2drop
			s" NO" s" autoboot_delay" setenv
			vreset
			true exit
		then

		rebootkey @ = if
			vreset
			0 reboot
		then

		drop 0
	again
;

[else]

: beastie-gfx-start false ;

[then]

set-current

: beastie-start

	s" beastie_disable" getenv
	dup -1 <> if
		s" YES" compare-insensitive 0= if
			exit
		then
	else
		drop
	then

	s" graphics_enable" getenv
	dup -1 <> if
		s" YES" compare-insensitive 0= if
			beastie-gfx-start if
				exit
			then
		then
	else
		drop
	then
	beastie-text-start
;

previous
