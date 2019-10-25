\ Copyright (c) 2018 Lars Engels
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

2 brandX ! 1 brandY ! \ Initialize brand placement defaults

: brand+ ( x y c-addr/u -- x y' )
  2swap 2dup at-xy 2swap \ position the cursor
  type \ print to the screen
  1+ \ increase y for next time we're called
;

: brand ( x y -- ) \ "NomadBSD" brand in B/W (13 rows x 21 columns)

  s"                                  _ " brand+
  s"                                 | |" brand+
  s"  _ __   ___  _ __ ___   __ _  __| |" brand+
  s" | '_ \ / _ \| '_ ` _ \ / _` |/ _` |" brand+
  s" | | | | (_) | | | | | | (_| | (_| |" brand+
  s" |_| |_|\___/|_| |_| |_|\__,_|\__,_|" brand+
  s"         ____   _____ _____" brand+
  s"        |  _ \ / ____|  __ \" brand+
  s"        | |_) | (___ | |  | |" brand+
  s"        |  _ < \___ \| |  | |" brand+
  s"        | |_) |____) | |__| |" brand+
  s"        |____/|_____/|_____/" brand+

  2drop
;
