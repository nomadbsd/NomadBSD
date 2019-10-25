45 logoX ! 1 logoY ! \ Initialize logo placement defaults

: logo+ ( x y c-addr/u -- x y' )
  2swap 2dup at-xy 2swap \ position the cursor
  [char] @ escc! \ replace @ with Esc
  type \ print to the screen
  1+ \ increase y for next time we're called
;

: logo ( x y -- ) \ "NomadBSD" logo (12 rows x 21 columns)
  s"          @[34;1m_======__@[m" logo+
  s"      @[34;1m(===============\@[m" logo+
  s"    @[34;1m(===================\@[m" logo+
  s"    @[34;1m_              _---__@[m" logo+
  s"   @[34;1m(=               ====-@[m" logo+
  s"  @[34;1m(=                ======@[m" logo+
  s"  @[34;1m(==                ======@[m" logo+
  s"  @[34;1m(==                ======@[m" logo+
  s"  @[34;1m(==\ \=-_      _=/ /====/@[m" logo+
  s"   @[34;1m(==\ \========/ /====/  /====-_@[m" logo+
  s"    @[34;1m(==\ \=====/ /==/   /===--@[m" logo+
  s" @[34;1m/================/  /===-@[m" logo+
  s" @[34;1m\===========/@[m" logo+

 2drop
;
