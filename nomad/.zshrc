HISTFILE=~/.histfile
HISTSIZE=10000
SAVEHIST=10000
export PS1="%m:%d%% "
# Emacs keybindings
bindkey -e
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '~/.zshrc'

autoload -Uz compinit
autoload -U history-search-end
autoload -U colors && colors

zle -N history-beginning-search-backward-end history-search-end
zle -N history-beginning-search-forward-end history-search-end

compinit

bindkey "\e[A"  history-beginning-search-backward-end
bindkey "\e[B"  history-beginning-search-forward-end
bindkey "^R"    history-incremental-search-backward
# Activate delete key
bindkey "\e[3~" delete-char
# use [shift]-[tab] for reverse completion
bindkey '^[[Z' reverse-menu-complete

# Ctrl+A / Ctrl+E jumps to beginning / end of line
bindkey "^A" beginning-of-line
bindkey "^E" end-of-line

case $TERM in
screen*|tmux*)  bindkey "\e[4~" end-of-line ;;
*)		bindkey "\e[F" end-of-line ;;
esac

cTIM="%F{cyan}%B"
cPWD="%F{magenta}%B"
cSTD="%b%f"
cSRV="%F{green}"
export PS1="${cTIM}%T${cSTD} ${cSRV}%m${cSTD} ${cUSR}%n${cSTD} ${cPWD}%~${cSTD} ${cPMT}%#${cSTD} "
export PS2="${cTIM}%T${cSTD} ${cUSR}>${cSTD} ${cPWD}"
  #
# no history duplicates
setopt hist_ignore_all_dups
setopt append_history

alias rm="rm -i"
alias ls="ls -G"
alias tmux="tmux -u2"
alias grep='grep --color=auto'
alias egrep='egrep --color=auto'

# FreeBSD ifconfig(8) CIDR NOTATION
export IFCONFIG_FORMAT=inet:cidr,inet6:cidr

export LSCOLORS='exExcxdxcxexhxhxhxbxhx'
export LS_COLORS='no=00:fi=00:di=00;34:ln=00;36:pi=40;33:so=00;35:bd=40;33;01:cd=40;33;01:or=01;05;37;41:mi=01;05;37;41:ex=00;32'

# COLOR MAN PAGES WITH less(1) OR bat(1)
if [ -e /usr/bin/col -a -e /usr/local/bin/bat ]
then
  # USE bat(1) AND col(1) IF AVAILABLE
  export MANPAGER="sh -c 'col -bx | bat -l man -p' "
else
  # USE less(1) AS FALLBACK
  export LESS_TERMCAP_mb=$'\E[5m'
  export LESS_TERMCAP_md=$'\E[01;31m'
  export LESS_TERMCAP_me=$'\E[0m'
  export LESS_TERMCAP_se=$'\E[0m'
  export LESS_TERMCAP_so=$'\E[01;44;33m'
  export LESS_TERMCAP_ue=$'\E[0m'
  export LESS_TERMCAP_us=$'\E[01;32m'
fi
