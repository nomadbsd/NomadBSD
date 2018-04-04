46 logoX ! 9 logoY ! \ Initialize logo placement defaults

: logo+ ( x y c-addr/u -- x y' )
  2swap 2dup at-xy 2swap \ position the cursor
  type \ print to the screen
  1+ \ increase y for next time we're called
;

: logo ( x y -- ) \ "NomadBSD" logo in B/W (13 rows x 21 columns)

  s"  _   _                           _ " logo+
  s" | \ | | ___  _ __ ___   __ _  __| |" logo+
  s" |  \| |/ _ \| '_ ` _ \ / _` |/ _` |" logo+
  s" | |\  | (_) | | | | | | (_| | (_| |" logo+
  s" |_| \_|\___/|_| |_| |_|\__,_|\__,_|" logo+
  s"   ____ ____  ____"  logo+
  s"  | __ ) ___||  _ \"  logo+
  s"  |  _ \___ \| | | |"  logo+
  s"  | |_) |__) | |_| |"  logo+
  s"  |____/____/|____/"  logo+

  2drop
;
