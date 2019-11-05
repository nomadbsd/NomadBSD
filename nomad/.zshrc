# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
export PS1="%m:%d%% "
bindkey -e
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '/home/nomad/.zshrc'

autoload -Uz compinit
autoload -U history-search-end
zle -N history-beginning-search-backward-end history-search-end
zle -N history-beginning-search-forward-end history-search-end
compinit

bindkey "\e[A" history-beginning-search-backward-end
bindkey "\e[B" history-beginning-search-forward-end
bindkey "\e[3~" delete-char

case $TERM in
screen*|tmux*)  bindkey "\e[4~" end-of-line ;;
*)		bindkey "\e[F" end-of-line ;;
esac

alias rm="rm -i"
alias ls="ls -G"

